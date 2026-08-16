/**
 * @file claude_face_v2.cpp
 * Claude CLI status faces v2 — 412x412 round LCD (ESP32 + LVGL)
 *
 * This is a full port of the "Claude Status Faces v2" design
 * (designs/Claude Status Faces v2.dc.html): all nine states have real faces
 * -- see claude_face_v2_start.cpp / _attention.cpp / _idle.cpp / _done.cpp /
 * _fail.cpp / _danger.cpp / _ratelimit.cpp / _subagent.cpp / _end.cpp. The
 * architecture is specced in claude_face_v2_PLAN.md; build_stub() is kept
 * below as the fallback a new/unfinished state's BUILDER[] entry should
 * point at while it's being written (correct chrome -- disc tint, hook
 * label, state word, hint line -- with an empty face area).
 */

#include "claude_face_v2.h"

#if CF_FACE_VERSION == 2

#include "claude_face_v2_faces.h"
#include <string.h>
#include <stdio.h>

/*==========================================================================
 * LVGL 8 / 9 compatibility (verbatim from claude_face.cpp)
 *========================================================================*/
#if LVGL_VERSION_MAJOR >= 9
#define CF_ANIM_DEL(v, c) lv_anim_delete((v), (c))
#define CF_OBJ_DEL(o)     lv_obj_delete(o)
#define CF_TIMER_DEL(t)   lv_timer_delete(t)
#define CF_FLAG_CLR(o, f) lv_obj_remove_flag((o), (f))
#define CF_SCR_ACT()      lv_screen_active()
#else
#define CF_ANIM_DEL(v, c) lv_anim_del((v), (c))
#define CF_OBJ_DEL(o)     lv_obj_del(o)
#define CF_TIMER_DEL(t)   lv_timer_del(t)
#define CF_FLAG_CLR(o, f) lv_obj_clear_flag((o), (f))
#define CF_SCR_ACT()      lv_scr_act()
#endif

/*==========================================================================
 * Fonts
 *========================================================================*/
#if CF2_USE_DESIGN_FONTS
LV_FONT_DECLARE(silkscreen_20)
LV_FONT_DECLARE(silkscreen_17)
LV_FONT_DECLARE(ibmplexmono_13)
LV_FONT_DECLARE(ibmplexmono_11)
#define CF2_FONT_WORD_20 (&silkscreen_20)
#define CF2_FONT_WORD_17 (&silkscreen_17)
#define CF2_FONT_HINT    (&ibmplexmono_13)
#define CF2_FONT_HOOK    (&ibmplexmono_11)
#else
/* Fallback so a build can proceed without the vendored bitmap fonts. Sizes
 * won't match the design; verify lv_conf.h actually enables these before
 * relying on it (same caveat v1 carries for CF_USE_SILKSCREEN_FONTS=0). */
#define CF2_FONT_WORD_20 (&lv_font_montserrat_20)
#define CF2_FONT_WORD_17 (&lv_font_montserrat_18)
#define CF2_FONT_HINT    (&lv_font_montserrat_14)
#define CF2_FONT_HOOK    (&lv_font_montserrat_12)
#endif

/*==========================================================================
 * Disc background -- radial gradient (LVGL 9 PC simulator) or flat fallback
 * (LVGL 8.3 firmware, which has no radial gradients -- see
 * claude_face_v2_PLAN.md D3). The design uses
 * radial-gradient(circle at 50% 34%, INNER 0%, OUTER 74%) on every state;
 * CF2_BG_CX/CY is 50%/34% of the 412x412 disc and CF2_BG_R is 74% of the
 * distance from that off-centre point to the disc's farthest corner
 * (~341px) -- past that radius, PAD extend holds flat at OUTER, matching
 * the CSS's unstyled 74-100% tail.
 *========================================================================*/
#if LVGL_VERSION_MAJOR >= 9 && defined(LV_USE_DRAW_SW_COMPLEX_GRADIENTS) && LV_USE_DRAW_SW_COMPLEX_GRADIENTS
#define CF2_USE_RADIAL_BG 1
#else
#define CF2_USE_RADIAL_BG 0
#endif

#if CF2_USE_RADIAL_BG
#define CF2_BG_CX 206
#define CF2_BG_CY 140
#define CF2_BG_R  252
#endif

/*==========================================================================
 * Chrome table -- one row per state.
 *
 * Text/colour/geometry values are taken verbatim from
 * claude_face_v2_PLAN.md's per-state tables and its oklch->hex colour
 * table, cross-checked against designs/Claude Status Faces v2.dc.html.
 * Only CF_STATE_DONE's `accent` is currently read by a face builder; the
 * rest is here so claude_face_label/hint/trigger/color() are correct for
 * every state and so switching to an unimplemented state still shows the
 * right chrome instead of stale text.
 *========================================================================*/
static const cf2_def_t DEF[CF_STATE_COUNT] = {
    /* START */
    { "start", "SESSIONSTART", "BOOTING", "session open", "SessionStart / startup",
      0x17150f, 0x060606, 0x88E48C, 0x88E48C, CF2_FONT_WORD_20, 314, 107, 77 },
    /* ATTENTION */
    { "attention", "PERMISSION_PROMPT", "YOUR TURN", "TAP TO DISMISS", "Notification / permission_prompt",
      0x241c08, 0x070604, 0xFFB93A, 0xFFC74A, CF2_FONT_WORD_20, 318, 102, 92 },
    /* IDLE */
    { "idle", "IDLE_PROMPT", "IDLE", "quiet for 4m", "Notification / idle_prompt",
      0x101420, 0x060606, 0x7AC3FF, 0x7AC3FF, CF2_FONT_WORD_20, 314, 107, 77 },
    /* DONE */
    { "done", "STOP", "DONE", "task complete", "Stop",
      0x0e1c14, 0x050605, 0x6CE98D, 0x73F094, CF2_FONT_WORD_20, 322, 107, 77 },
    /* FAIL */
    { "fail", "POSTTOOLUSEFAILURE", "FAILED", "tool call bounced", "PostToolUseFailure",
      0x240f10, 0x070505, 0xFF7871, 0xFF857D, CF2_FONT_WORD_20, 322, 107, 77 },
    /* DANGER */
    { "danger", "PRETOOLUSE \xC2\xB7 BASH", "DANGER", "rm \xC2\xB7 git push guarded",
      "PreToolUse / Bash(rm *), Bash(git push *)",
      0x291702, 0x080604, 0xFF9350, 0xFFA664, CF2_FONT_WORD_20, 318, 112, 92 },
    /* RATELIMIT */
    { "ratelimit", "STOPFAILURE", "RATE LIMIT", "backing off \xC2\xB7 retry 60s", "StopFailure / rate_limit",
      0x1c1024, 0x060506, 0xCF9BFF, 0xDCA8FF, CF2_FONT_WORD_17, 314, 107, 77 },
    /* SUBAGENT */
    { "subagent", "SUBAGENTSTOP", "SUBAGENT", "helper reported back", "SubagentStop",
      0x0b1c1f, 0x050606, 0x00DFE8, 0x1BE5EE, CF2_FONT_WORD_20, 318, 107, 77 },
    /* END */
    { "end", "SESSIONEND", "SIGNING OFF", "session closed", "SessionEnd",
      0x16121c, 0x050505, 0xAA9DF1, 0xB6AAFF, CF2_FONT_WORD_17, 318, 92, 71 },
};

/*==========================================================================
 * Easing (verbatim from claude_face.cpp)
 *========================================================================*/
static const uint16_t EASE_IN_OUT[17] = {   /* cubic-bezier(.42,0,.58,1) */
    0, 8, 31, 72, 129, 204, 293, 393, 500, 607, 707, 796, 871, 928, 969, 992, 1000
};

static int32_t ease(const uint16_t *lut, int32_t u)
{
    if(u <= 0)    return 0;
    if(u >= 1000) return 1000;
    int32_t p = u * 16;
    int32_t i = p / 1000;
    int32_t f = p - i * 1000;
    return lut[i] + (int32_t)(lut[i + 1] - lut[i]) * f / 1000;
}

typedef struct { uint16_t t; int16_t v; } cf_kf_t;

static int32_t kf_eval(const cf_kf_t *k, uint8_t n, int32_t t, bool smooth)
{
    if(t <= k[0].t) return k[0].v;
    for(uint8_t i = 1; i < n; i++) {
        if(t <= k[i].t) {
            int32_t span = k[i].t - k[i - 1].t;
            int32_t u = span > 0 ? (t - k[i - 1].t) * 1000 / span : 1000;
            if(smooth) u = ease(EASE_IN_OUT, u);
            return k[i - 1].v + (int32_t)(k[i].v - k[i - 1].v) * u / 1000;
        }
    }
    return k[n - 1].v;
}

/* @keyframes bob { 0%,100%: translateY(0); 50%: translateY(-12px); } */
static const cf_kf_t KF_BOB_Y[] = { {0,0}, {500,-12}, {1000,0} };

/*==========================================================================
 * Small helpers (verbatim from claude_face.cpp)
 *========================================================================*/
static lv_obj_t *plain(lv_obj_t *parent)
{
    lv_obj_t *o = lv_obj_create(parent);
    lv_obj_remove_style_all(o);
    lv_obj_set_style_bg_opa(o, LV_OPA_TRANSP, 0);
    CF_FLAG_CLR(o, LV_OBJ_FLAG_SCROLLABLE);
    CF_FLAG_CLR(o, LV_OBJ_FLAG_CLICKABLE);
    return o;
}

static lv_obj_t *flex_col(lv_obj_t *parent, int32_t gap)
{
    lv_obj_t *o = plain(parent);
    lv_obj_set_size(o, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(o, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(o, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(o, gap, 0);
    return o;
}

static void anim_start(lv_anim_exec_xcb_t cb, uint32_t dur, void *var)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, var);
    lv_anim_set_exec_cb(&a, cb);
    lv_anim_set_values(&a, 0, 1000);
    lv_anim_set_time(&a, dur);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}

/*==========================================================================
 * Primitives (subset of claude_face_v2_PLAN.md's six -- only what "done"
 * and "idle" need: a plain rect, a pitched row of them, and a text label).
 *========================================================================*/
lv_obj_t *cf2_rect(lv_obj_t *p, int x, int y, int w, int h, uint32_t col)
{
    lv_obj_t *o = plain(p);
    lv_obj_set_pos(o, x, y);
    lv_obj_set_size(o, w, h);
    lv_obj_set_style_bg_color(o, lv_color_hex(col), 0);
    lv_obj_set_style_bg_opa(o, LV_OPA_COVER, 0);
    return o;
}

void cf2_rect_row(lv_obj_t *p, int x, int y, int n, int w, int h, int pitch,
                   const int8_t *dy, uint32_t col, lv_obj_t **out)
{
    for(int i = 0; i < n; i++) {
        lv_obj_t *o = cf2_rect(p, x + i * pitch, y + dy[i], w, h, col);
        if(out) out[i] = o;
    }
}

lv_obj_t *cf2_text(lv_obj_t *p, int x, int y, const lv_font_t *f, uint32_t col,
                    const char *s)
{
    lv_obj_t *o = lv_label_create(p);
    lv_obj_set_style_text_font(o, f, 0);
    lv_obj_set_style_text_color(o, lv_color_hex(col), 0);
    lv_label_set_text(o, s);
    lv_obj_set_pos(o, x, y);
    return o;
}

/* A full circular ring, border only (no fill) -- attention's breathing
 * bezel. `inset` px from the 412 edge, matching cf2_arc()'s convention. */
lv_obj_t *cf2_ring(lv_obj_t *p, int inset, int bw, uint32_t col)
{
    lv_obj_t *o = plain(p);
    int d = CF_DISPLAY_SIZE - 2 * inset;
    lv_obj_set_pos(o, inset, inset);
    lv_obj_set_size(o, d, d);
    lv_obj_set_style_radius(o, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_border_width(o, bw, 0);
    lv_obj_set_style_border_color(o, lv_color_hex(col), 0);
    lv_obj_set_style_border_opa(o, LV_OPA_COVER, 0);
    return o;
}

/* A square-cornered rect, border only (no fill) -- ratelimit's eye frames.
 * LVGL borders draw inside the box (border-box sizing), same as the CSS
 * they're ported from, so `w`/`h` is the full visible size including the
 * `bw` stroke. */
lv_obj_t *cf2_frame(lv_obj_t *p, int x, int y, int w, int h, int bw, uint32_t col)
{
    lv_obj_t *o = plain(p);
    lv_obj_set_pos(o, x, y);
    lv_obj_set_size(o, w, h);
    lv_obj_set_style_border_width(o, bw, 0);
    lv_obj_set_style_border_color(o, lv_color_hex(col), 0);
    lv_obj_set_style_border_opa(o, LV_OPA_COVER, 0);
    return o;
}

/* v1's arc trick (claude_face.cpp): an lv_arc with a transparent MAIN part
 * and all its KNOB styling killed, so only the INDICATOR renders -- a bare
 * ring segment with no stray blob at either end. */
lv_obj_t *cf2_arc(lv_obj_t *p, int inset, int bw, uint32_t col, int a0, int a1, lv_opa_t opa)
{
    lv_obj_t *a = lv_arc_create(p);
    lv_obj_remove_style_all(a);
    int d = CF_DISPLAY_SIZE - 2 * inset;
    lv_obj_set_size(a, d, d);
    lv_obj_set_pos(a, inset, inset);
    CF_FLAG_CLR(a, LV_OBJ_FLAG_CLICKABLE);
    CF_FLAG_CLR(a, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(a, 0, LV_PART_MAIN);
    lv_obj_set_style_arc_opa(a, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(a, LV_OPA_TRANSP, LV_PART_KNOB);
    lv_obj_set_style_border_width(a, 0, LV_PART_KNOB);
    lv_obj_set_style_outline_width(a, 0, LV_PART_KNOB);
    lv_obj_set_style_pad_all(a, 0, LV_PART_KNOB);
    lv_obj_set_style_arc_width(a, bw, LV_PART_MAIN);
    lv_obj_set_style_arc_width(a, bw, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(a, lv_color_hex(col), LV_PART_INDICATOR);
    lv_obj_set_style_arc_opa(a, opa, LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(a, false, LV_PART_INDICATOR);
    lv_arc_set_bg_angles(a, a0, a1);
    lv_arc_set_angles(a, a0, a1);
    return a;
}

/*==========================================================================
 * Anim engine -- "bob" only. See claude_face_v2_faces.h for the contract.
 *========================================================================*/
#define CF2_BOB_MAX 12
typedef struct { lv_obj_t *objs[CF2_BOB_MAX]; uint8_t n; } cf2_bob_t;
static cf2_bob_t g_bob;

static void bob_cb(void *var, int32_t t)
{
    cf2_bob_t *b = (cf2_bob_t *)var;
    int32_t ty = kf_eval(KF_BOB_Y, 3, t, true);
    for(uint8_t i = 0; i < b->n; i++)
        lv_obj_set_style_translate_y(b->objs[i], ty, 0);
}

void cf2_bob_start(lv_obj_t **objs, uint8_t n, uint32_t dur_ms)
{
    if(n > CF2_BOB_MAX) n = CF2_BOB_MAX;
    g_bob.n = n;
    for(uint8_t i = 0; i < n; i++) g_bob.objs[i] = objs[i];
    anim_start(bob_cb, dur_ms, &g_bob);
}

static void cf2_bob_stop(void)
{
    CF_ANIM_DEL(&g_bob, bob_cb);
    g_bob.n = 0;
}

/* @keyframes zzz -- 0%: ty 8, opa 0; 40%: opa .9; 100%: ty -20, opa 0.
 * (The design also scales .8 -> 1.1; dropped per claude_face_v2_PLAN.md --
 * LVGL 8.3 can't scale a label, and the two font sizes already carry the
 * size difference.) */
static const cf_kf_t KF_ZZZ_Y[] = { {0,8}, {1000,-20} };
static const cf_kf_t KF_ZZZ_O[] = { {0,0}, {400,230}, {1000,0} };

static void zzz_cb(void *var, int32_t t)
{
    lv_obj_t *o = (lv_obj_t *)var;
    lv_obj_set_style_translate_y(o, kf_eval(KF_ZZZ_Y, 2, t, true), 0);
    lv_obj_set_style_text_opa(o, (lv_opa_t)kf_eval(KF_ZZZ_O, 3, t, true), 0);
}

/* `obj` must be a child of `scene` -- claude_face_v2.cpp doesn't track
 * these anims separately, it relies on LVGL cancelling anims whose `var`
 * is the object being deleted, which lv_obj_clean(scene) triggers per
 * child on every state change (same guarantee claude_face_v2_PLAN.md's
 * anim-engine notes rely on). `delay_ms` gives a persistent phase offset
 * for repeat playback since this anim is always torn down and rebuilt
 * fresh on every state entry (never resumed mid-flight), so
 * lv_anim_set_delay()'s first-iteration-only caveat doesn't apply here. */
void cf2_zzz_start(lv_obj_t *obj, uint32_t dur_ms, uint32_t delay_ms)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_exec_cb(&a, zzz_cb);
    lv_anim_set_values(&a, 0, 1000);
    lv_anim_set_time(&a, dur_ms);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    if(delay_ms) lv_anim_set_delay(&a, delay_ms);
    lv_anim_start(&a);
}

/* @keyframes shake { 0%,100%: translateX(0); 20%: -8px; 40%: +8px;
 *                     60%: -5px; 80%: +5px; } */
static const cf_kf_t KF_SHAKE_X[] = { {0,0}, {200,-8}, {400,8}, {600,-5}, {800,5}, {1000,0} };

#define CF2_SHAKE_MAX 10
typedef struct { lv_obj_t *objs[CF2_SHAKE_MAX]; uint8_t n; } cf2_shake_t;
static cf2_shake_t g_shake;

static void shake_cb(void *var, int32_t t)
{
    cf2_shake_t *s = (cf2_shake_t *)var;
    int32_t tx = kf_eval(KF_SHAKE_X, 6, t, true);
    for(uint8_t i = 0; i < s->n; i++)
        lv_obj_set_style_translate_x(s->objs[i], tx, 0);
}

/* fail's grid-cell shake, see claude_face_v2_faces.h. */
void cf2_shake_start(lv_obj_t **objs, uint8_t n, uint32_t dur_ms)
{
    if(n > CF2_SHAKE_MAX) n = CF2_SHAKE_MAX;
    g_shake.n = n;
    for(uint8_t i = 0; i < n; i++) g_shake.objs[i] = objs[i];
    anim_start(shake_cb, dur_ms, &g_shake);
}

static void cf2_shake_stop(void)
{
    CF_ANIM_DEL(&g_shake, shake_cb);
    g_shake.n = 0;
}

/* @keyframes drift { 0%,100%: translateX(-12px); 50%: translateX(12px); } */
static const cf_kf_t KF_DRIFT_X[] = { {0,-12}, {500,12}, {1000,-12} };

#define CF2_DRIFT_MAX 6
typedef struct { lv_obj_t *objs[CF2_DRIFT_MAX]; uint8_t n; } cf2_drift_t;
static cf2_drift_t g_drift;

static void drift_cb(void *var, int32_t t)
{
    cf2_drift_t *g = (cf2_drift_t *)var;
    int32_t tx = kf_eval(KF_DRIFT_X, 3, t, true);
    for(uint8_t i = 0; i < g->n; i++)
        lv_obj_set_style_translate_x(g->objs[i], tx, 0);
}

/* attention's brow/eye/pupil-hole drift, see claude_face_v2_faces.h. */
void cf2_drift_start(lv_obj_t **objs, uint8_t n, uint32_t dur_ms)
{
    if(n > CF2_DRIFT_MAX) n = CF2_DRIFT_MAX;
    g_drift.n = n;
    for(uint8_t i = 0; i < n; i++) g_drift.objs[i] = objs[i];
    anim_start(drift_cb, dur_ms, &g_drift);
}

static void cf2_drift_stop(void)
{
    CF_ANIM_DEL(&g_drift, drift_cb);
    g_drift.n = 0;
}

/* @keyframes tick { 0%,100%: translateY(0); 50%: translateY(6px); } --
 * ratelimit's three mouth dots, phased 0/167/333 permille of 1200ms
 * (CSS animation-delay .2s/.4s). Per-object phase, same sign convention as
 * cf2_blink2_start(): a delayed object's local clock starts later, so it's
 * *behind* the shared timeline `t` -- subtract phase, don't add it. */
static const cf_kf_t KF_TICK_Y[] = { {0,0}, {500,6}, {1000,0} };

#define CF2_TICK_MAX 4
typedef struct {
    lv_obj_t *objs[CF2_TICK_MAX];
    uint16_t  phase[CF2_TICK_MAX];
    uint8_t   n;
} cf2_tick_t;
static cf2_tick_t g_tick;

static void tick_cb(void *var, int32_t t)
{
    cf2_tick_t *g = (cf2_tick_t *)var;
    for(uint8_t i = 0; i < g->n; i++) {
        int32_t tp = (t - (int32_t)g->phase[i] + 1000) % 1000;
        lv_obj_set_style_translate_y(g->objs[i], kf_eval(KF_TICK_Y, 3, tp, true), 0);
    }
}

/* ratelimit's ticking mouth dots, see claude_face_v2_faces.h. */
void cf2_tick_start(lv_obj_t **objs, const uint16_t *phase, uint8_t n, uint32_t dur_ms)
{
    if(n > CF2_TICK_MAX) n = CF2_TICK_MAX;
    g_tick.n = n;
    for(uint8_t i = 0; i < n; i++) {
        g_tick.objs[i]  = objs[i];
        g_tick.phase[i] = phase[i];
    }
    anim_start(tick_cb, dur_ms, &g_tick);
}

static void cf2_tick_stop(void)
{
    CF_ANIM_DEL(&g_tick, tick_cb);
    g_tick.n = 0;
}

/* @keyframes blink { 0%,92%,100%: scaleY(1); 95%: scaleY(0.06); }
 * (start's eye-half blink). LVGL 8.3 objects can't scale on one axis, so
 * this resizes height directly and re-centres y around the object's
 * original vertical centre -- visually equivalent for a solid rect. */
static const cf_kf_t KF_BLINK_SCALE[] = { {0,1000}, {876,1000}, {920,60}, {950,60}, {994,1000}, {1000,1000} };

#define CF2_BLINK_MAX 4
typedef struct {
    lv_obj_t *objs[CF2_BLINK_MAX];
    int16_t   base_y[CF2_BLINK_MAX];
    int16_t   base_h[CF2_BLINK_MAX];
    uint8_t   n;
} cf2_blink_t;
static cf2_blink_t g_blink;

static void blink_cb(void *var, int32_t t)
{
    cf2_blink_t *b = (cf2_blink_t *)var;
    int32_t scale = kf_eval(KF_BLINK_SCALE, 6, t, false);
    for(uint8_t i = 0; i < b->n; i++) {
        int32_t h = b->base_h[i] * scale / 1000;
        if(h < 1) h = 1;
        lv_obj_set_height(b->objs[i], h);
        lv_obj_set_y(b->objs[i], b->base_y[i] + (b->base_h[i] - h) / 2);
    }
    printf("DBG blink t=%d scale=%d h0=%d y0=%d base_h0=%d base_y0=%d\n",
           (int)t, (int)scale, (int)lv_obj_get_height(b->objs[0]),
           (int)lv_obj_get_y(b->objs[0]), (int)b->base_h[0], (int)b->base_y[0]);
}

/* start's eye-half blink, see claude_face_v2_faces.h. Captures each
 * object's current y/height as its blink-open baseline -- call after the
 * objects are positioned, before any other animation resizes them. */
void cf2_blink_start(lv_obj_t **objs, uint8_t n, uint32_t dur_ms)
{
    if(n > CF2_BLINK_MAX) n = CF2_BLINK_MAX;
    g_blink.n = n;
    /* lv_obj_set_pos/set_size() only schedule a layout update -- the
     * object's real coords (what get_y/get_height read) aren't resolved
     * until the next layout pass. Force it now so the baseline below isn't
     * captured as 0/0, which would collapse the eyes to a 1px sliver on
     * every "blink" instead of a brief flick. */
    if(n > 0) lv_obj_update_layout(objs[0]);
    for(uint8_t i = 0; i < n; i++) {
        g_blink.objs[i]   = objs[i];
        g_blink.base_y[i] = lv_obj_get_y(objs[i]);
        g_blink.base_h[i] = lv_obj_get_height(objs[i]);
    }
    anim_start(blink_cb, dur_ms, &g_blink);
}

static void cf2_blink_stop(void)
{
    CF_ANIM_DEL(&g_blink, blink_cb);
    g_blink.n = 0;
}

/* @keyframes blink2 { 0%,46%,54%,100%: scaleY(1); 50%: scaleY(0.06); }
 * (subagent's 2x2 eye-cell blink), `steps(1,end)`. Unlike `blink`, the two
 * eyes run out of phase, so this takes a per-object phase (per-mille of
 * `dur_ms`) instead of a single group phase -- subagent calls it once with
 * an 8-object array (both eyes), left eye phase 0, right eye phase 62. */
#define CF2_BLINK2_MAX 8
typedef struct {
    lv_obj_t *objs[CF2_BLINK2_MAX];
    int16_t   base_y[CF2_BLINK2_MAX];
    int16_t   base_h[CF2_BLINK2_MAX];
    uint16_t  phase[CF2_BLINK2_MAX];
    uint8_t   n;
} cf2_blink2_t;
static cf2_blink2_t g_blink2;

static void blink2_cb(void *var, int32_t t)
{
    cf2_blink2_t *b = (cf2_blink2_t *)var;
    for(uint8_t i = 0; i < b->n; i++) {
        /* CSS animation-delay pushes an element's local clock *later*, so
         * at any shared time t it's behind, not ahead -- subtract phase,
         * don't add it (a plain `t + phase` would make the delayed eye
         * blink earlier than the undelayed one). */
        int32_t tp = (t - (int32_t)b->phase[i] + 1000) % 1000;
        int32_t h = (tp >= 500 && tp < 540) ? b->base_h[i] * 60 / 1000 : b->base_h[i];
        if(h < 1) h = 1;
        lv_obj_set_height(b->objs[i], h);
        lv_obj_set_y(b->objs[i], b->base_y[i] + (b->base_h[i] - h) / 2);
    }
}

/* subagent's checkerboard-cell blink, see claude_face_v2_faces.h. Same
 * baseline-capture contract as cf2_blink_start(). */
void cf2_blink2_start(lv_obj_t **objs, const uint16_t *phase, uint8_t n, uint32_t dur_ms)
{
    if(n > CF2_BLINK2_MAX) n = CF2_BLINK2_MAX;
    g_blink2.n = n;
    if(n > 0) lv_obj_update_layout(objs[0]);
    for(uint8_t i = 0; i < n; i++) {
        g_blink2.objs[i]   = objs[i];
        g_blink2.base_y[i] = lv_obj_get_y(objs[i]);
        g_blink2.base_h[i] = lv_obj_get_height(objs[i]);
        g_blink2.phase[i]  = phase[i];
    }
    anim_start(blink2_cb, dur_ms, &g_blink2);
}

static void cf2_blink2_stop(void)
{
    CF_ANIM_DEL(&g_blink2, blink2_cb);
    g_blink2.n = 0;
}

/* @keyframes fadeout { 0%: opacity 1; 100%: opacity .2; } -- CSS
 * `alternate` plays it forward then backward every 4000ms, an 8000ms round
 * trip. Modelled as a single 8000ms cycle that already returns to its start
 * value at t=1000, so one infinite-repeat anim reproduces the alternate
 * playback exactly (end's fade). Drives `bg_opa` on each rect individually
 * rather than the parent's `opa`, which inherits differently between LVGL
 * 8.3 and 9. */
static const cf_kf_t KF_FADE_O[] = { {0,255}, {500,51}, {1000,255} };

#define CF2_FADE_MAX 6
typedef struct { lv_obj_t *objs[CF2_FADE_MAX]; uint8_t n; } cf2_fade_t;
static cf2_fade_t g_fade;

static void fade_cb(void *var, int32_t t)
{
    cf2_fade_t *f = (cf2_fade_t *)var;
    lv_opa_t o = (lv_opa_t)kf_eval(KF_FADE_O, 3, t, true);
    for(uint8_t i = 0; i < f->n; i++)
        lv_obj_set_style_bg_opa(f->objs[i], o, 0);
}

/* end's whole-face fade, see claude_face_v2_faces.h. */
void cf2_fadeout_start(lv_obj_t **objs, uint8_t n, uint32_t dur_ms)
{
    if(n > CF2_FADE_MAX) n = CF2_FADE_MAX;
    g_fade.n = n;
    for(uint8_t i = 0; i < n; i++) g_fade.objs[i] = objs[i];
    anim_start(fade_cb, dur_ms, &g_fade);
}

static void cf2_fade_stop(void)
{
    CF_ANIM_DEL(&g_fade, fade_cb);
    g_fade.n = 0;
}

/*==========================================================================
 * Builders
 *========================================================================*/
static void build_stub(lv_obj_t *scene, const cf2_def_t *d)
{
    LV_UNUSED(scene);
    LV_UNUSED(d);
    /* No geometry yet for this state -- chrome (disc tint, hook label,
     * word, hint) is already correct; see claude_face_v2.cpp's header
     * comment and claude_face_v2_PLAN.md for what a real builder needs. */
}

typedef void (*cf2_build_fn)(lv_obj_t *scene, const cf2_def_t *d);

/* Order matches cf_state_t in claude_face_v2.h: START, ATTENTION, IDLE,
 * DONE, FAIL, DANGER, RATELIMIT, SUBAGENT, END. */
static const cf2_build_fn BUILDER[CF_STATE_COUNT] = {
    build_start, build_attention, build_idle,      build_done,
    build_fail,  build_danger,    build_ratelimit, build_subagent, build_end,
};

/*==========================================================================
 * Instance
 *========================================================================*/
typedef struct {
    lv_obj_t   *root;
    lv_obj_t   *scene;   /* face geometry, lv_obj_clean()'d each state change */
    lv_obj_t   *hook;
    lv_obj_t   *textcol; /* word + hint, repositioned to DEF[s].word_y      */
    lv_obj_t   *word;
    lv_obj_t   *hint;
    lv_timer_t *cycle;
    cf_state_t  state;
    bool        hint_on;
    bool        hook_on;
} cf2_ctx_t;

static cf2_ctx_t cf;

/*==========================================================================
 * Public API
 *========================================================================*/
lv_obj_t *claude_face_create(lv_obj_t *parent)
{
    if(cf.root) claude_face_destroy();
    if(parent == NULL) parent = CF_SCR_ACT();

    memset(&cf, 0, sizeof(cf));
    cf.state   = CF_STATE_ATTENTION;   /* overwritten by the first set_state() call */
    cf.hint_on = true;
    cf.hook_on = CF2_SHOW_HOOK_LABELS ? true : false;

    /* the parent screen defaults to a white background; paint it to match
     * so the +5px offset below doesn't expose a white sliver at the edge */
    lv_obj_set_style_bg_color(parent, lv_color_hex(0x08080a), 0);
    lv_obj_set_style_bg_opa(parent, LV_OPA_COVER, 0);

    cf.root = plain(parent);
    lv_obj_set_size(cf.root, CF_DISPLAY_SIZE, CF_DISPLAY_SIZE);
    lv_obj_align(cf.root, LV_ALIGN_CENTER, 5, 0);
    lv_obj_set_style_bg_opa(cf.root, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(cf.root, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(cf.root, true, 0);

    cf.scene = plain(cf.root);
    lv_obj_set_size(cf.scene, CF_DISPLAY_SIZE, CF_DISPLAY_SIZE);
    lv_obj_set_pos(cf.scene, 0, 0);

    cf.hook = lv_label_create(cf.root);
    lv_obj_set_width(cf.hook, CF_DISPLAY_SIZE);
    lv_obj_set_style_text_align(cf.hook, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(cf.hook, CF2_FONT_HOOK, 0);
    lv_obj_set_style_text_letter_space(cf.hook, 3, 0);
    lv_obj_set_style_text_color(cf.hook, lv_color_hex(0xf2ead8), 0);
    lv_obj_set_pos(cf.hook, 0, 40);
    if(!cf.hook_on) lv_obj_add_flag(cf.hook, LV_OBJ_FLAG_HIDDEN);

    cf.textcol = flex_col(cf.root, 10);
    cf.word = lv_label_create(cf.textcol);
    lv_obj_set_style_text_font(cf.word, CF2_FONT_WORD_20, 0);
    lv_obj_set_style_text_letter_space(cf.word, 3, 0);

    cf.hint = lv_label_create(cf.textcol);
    lv_obj_set_style_text_font(cf.hint, CF2_FONT_HINT, 0);
    lv_obj_set_style_text_letter_space(cf.hint, 1, 0);
    lv_obj_set_style_text_color(cf.hint, lv_color_hex(0xf2ead8), 0);

    claude_face_set_state(CF_STATE_DONE);

    return cf.root;
}

void claude_face_destroy(void)
{
    if(!cf.root) return;
    claude_face_cycle(false);
    cf2_bob_stop();
    CF_OBJ_DEL(cf.root);
    memset(&cf, 0, sizeof(cf));
}

void claude_face_set_state(cf_state_t s)
{
    if(!cf.root || s >= CF_STATE_COUNT) return;
    cf.state = s;
    const cf2_def_t *d = &DEF[s];

    cf2_bob_stop();
    cf2_shake_stop();
    cf2_blink_stop();
    cf2_blink2_stop();
    cf2_fade_stop();
    cf2_drift_stop();
    cf2_tick_stop();
    lv_obj_clean(cf.scene);

#if CF2_USE_RADIAL_BG
    {
        static lv_grad_dsc_t bg_grad;
        lv_color_t stops[2] = { lv_color_hex(d->bg), lv_color_hex(d->bg_outer) };
        lv_grad_init_stops(&bg_grad, stops, NULL, NULL, 2);
        lv_grad_radial_init(&bg_grad, CF2_BG_CX, CF2_BG_CY, CF2_BG_CX + CF2_BG_R, CF2_BG_CY,
                             LV_GRAD_EXTEND_PAD);
        lv_obj_set_style_bg_grad(cf.root, &bg_grad, 0);
    }
#else
    lv_obj_set_style_bg_color(cf.root, lv_color_hex(d->bg), 0);
#endif

    lv_label_set_text(cf.hook, d->hook);
    lv_obj_set_style_text_opa(cf.hook, d->hook_opa, 0);

    lv_label_set_text(cf.word, d->word);
    lv_obj_set_style_text_font(cf.word, d->word_font, 0);
    lv_obj_set_style_text_color(cf.word, lv_color_hex(d->word_col), 0);

    lv_label_set_text(cf.hint, d->hint);
    lv_obj_set_style_text_opa(cf.hint, d->hint_opa, 0);
    if(cf.hint_on) CF_FLAG_CLR(cf.hint, LV_OBJ_FLAG_HIDDEN);
    else           lv_obj_add_flag(cf.hint, LV_OBJ_FLAG_HIDDEN);

    lv_obj_align(cf.textcol, LV_ALIGN_TOP_MID, 0, d->word_y);

    BUILDER[s](cf.scene, d);
}

cf_state_t claude_face_get_state(void) { return cf.state; }

void claude_face_next(void)
{
    if(!cf.root) return;
    claude_face_set_state((cf_state_t)((cf.state + 1) % CF_STATE_COUNT));
}

void claude_face_set_hint_visible(bool en)
{
    if(!cf.root) return;
    cf.hint_on = en;
    if(en) CF_FLAG_CLR(cf.hint, LV_OBJ_FLAG_HIDDEN);
    else   lv_obj_add_flag(cf.hint, LV_OBJ_FLAG_HIDDEN);
}

void claude_face_set_hook_label_visible(bool en)
{
    if(!cf.root) return;
    cf.hook_on = en;
    if(en) CF_FLAG_CLR(cf.hook, LV_OBJ_FLAG_HIDDEN);
    else   lv_obj_add_flag(cf.hook, LV_OBJ_FLAG_HIDDEN);
}

static void cycle_cb(lv_timer_t *t)
{
    LV_UNUSED(t);
    claude_face_next();
}

void claude_face_cycle(bool en)
{
    if(en) {
        if(!cf.cycle) cf.cycle = lv_timer_create(cycle_cb, 2200, NULL);
    }
    else if(cf.cycle) {
        CF_TIMER_DEL(cf.cycle);
        cf.cycle = NULL;
    }
}

lv_obj_t   *claude_face_root(void)                 { return cf.root; }
const char *claude_face_key(cf_state_t s)          { return DEF[s % CF_STATE_COUNT].key; }
const char *claude_face_label(cf_state_t s)        { return DEF[s % CF_STATE_COUNT].word; }
const char *claude_face_hint(cf_state_t s)         { return DEF[s % CF_STATE_COUNT].hint; }
const char *claude_face_trigger(cf_state_t s)      { return DEF[s % CF_STATE_COUNT].trigger; }
lv_color_t  claude_face_color(cf_state_t s)        { return lv_color_hex(DEF[s % CF_STATE_COUNT].accent); }

cf_state_t claude_face_from_key(const char *key)
{
    if(key) {
        for(int i = 0; i < CF_STATE_COUNT; i++) {
            if(strcmp(key, DEF[i].key) == 0) return (cf_state_t)i;
        }
    }
    return CF_STATE_IDLE;
}

#endif /* CF_FACE_VERSION == 2 */
