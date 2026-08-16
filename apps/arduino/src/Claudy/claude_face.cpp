/**
 * @file claude_face.cpp
 * Claude CLI status faces — 412x412 round LCD (ESP32 + LVGL)
 *
 * Geometry, colours, easing and timing are taken verbatim from the design:
 *   screen 412x412  bg #0a0908
 *   pulse ring  inset 26px, 2px border, colour @30% alpha,
 *               pulsering 2.2s ease-out  (scale .82 -> 1.12, opacity .9 -> 0)
 *   spin ring   inset 12px, 3px top border only (90 deg arc),
 *               spinring 3.4s linear
 *   face box    210x150, column, centred, 26px gap between eyes and mouth
 *   label       Silkscreen 34px, letter-spacing .06em, state colour
 *   hint        Silkscreen 13px, letter-spacing .10em, #6f6a60
 *   gaps        face -> label 34px, label -> hint 12px
 */

#include "claude_face.h"

#if CF_FACE_VERSION == 1

#include <string.h>

/*==========================================================================
 * LVGL 8 / 9 compatibility
 *========================================================================*/
#if LVGL_VERSION_MAJOR >= 9
#define CF_ROT(o, v)      lv_obj_set_style_transform_rotation((o), (v), 0)
#define CF_SCALE(o, v)    lv_obj_set_style_transform_scale((o), (v), 0)
#define CF_SCALE_NONE     LV_SCALE_NONE
#define CF_ANIM_DEL(v, c) lv_anim_delete((v), (c))
#define CF_OBJ_DEL(o)     lv_obj_delete(o)
#define CF_TIMER_DEL(t)   lv_timer_delete(t)
#define CF_FLAG_CLR(o, f) lv_obj_remove_flag((o), (f))
#define CF_SCR_ACT()      lv_screen_active()
#else
#define CF_ROT(o, v)      lv_obj_set_style_transform_angle((o), (v), 0)
#define CF_SCALE(o, v)    lv_obj_set_style_transform_zoom((o), (v), 0)
#define CF_SCALE_NONE     LV_IMG_ZOOM_NONE
#define CF_ANIM_DEL(v, c) lv_anim_del((v), (c))
#define CF_OBJ_DEL(o)     lv_obj_del(o)
#define CF_TIMER_DEL(t)   lv_timer_del(t)
#define CF_FLAG_CLR(o, f) lv_obj_clear_flag((o), (f))
#define CF_SCR_ACT()      lv_scr_act()
#endif

/*==========================================================================
 * Fonts
 *========================================================================*/
#if CF_USE_SILKSCREEN_FONTS
LV_FONT_DECLARE(silkscreen_34)
LV_FONT_DECLARE(silkscreen_13)
#define CF_FONT_LABEL (&silkscreen_34)
#define CF_FONT_HINT  (&silkscreen_13)
#else
#define CF_FONT_LABEL (&lv_font_montserrat_28)
#define CF_FONT_HINT  (&lv_font_montserrat_14)
#endif

/*==========================================================================
 * Design tables
 *========================================================================*/

typedef enum {
    F_HAPPY, F_WIDE, F_SLEEPY, F_SAD, F_SHOCK, F_FLAT, F_WINK, F_CLOSED
} cf_face_t;

typedef enum { A_BOUNCE, A_SWAY, A_BREATHE, A_SINK, A_SHAKE } cf_anim_t;

/* One entry of the FACE map in the design. `mouth_bw` == 0 means the mouth is
 * a solid pill/dot; otherwise it is an open arc of that stroke width, opening
 * down (smile) or up (frown). */
typedef struct {
    uint8_t eye_w, eye_h, eye_r, eye_gap;
    uint8_t mouth_w, mouth_h, mouth_bw;
    uint8_t mouth_up;                       /* 1 = frown */
} cf_shape_t;

static const cf_shape_t SHAPE[] = {
    /* eyeW eyeH eyeR gap   mW  mH  bw  up */
    {  26,  26,  13,  54,   96, 46, 10,  0 },  /* happy  */
    {  36,  36,  18,  48,   44, 44,  0,  0 },  /* wide   */
    {  34,   8,   4,  52,   46,  8,  0,  0 },  /* sleepy */
    {  24,  24,  12,  54,   84, 40, 10,  1 },  /* sad    */
    {  40,  40,  20,  44,   56, 56,  0,  0 },  /* shock  */
    {  26,  26,  13,  54,   76,  8,  0,  0 },  /* flat   */
    {  28,  12,   6,  52,   80, 38,  9,  0 },  /* wink   */
    {  32,   7,   4,  54,   40,  7,  0,  0 },  /* closed */
};

typedef struct {
    const char *key;
    const char *label;
    const char *hint;
    const char *trigger;
    uint32_t    color;
    uint8_t     face;
    uint8_t     anim;
    uint16_t    dur;          /* ms */
} cf_def_t;

static const cf_def_t DEF[CF_STATE_COUNT] = {
    { "start",     "HELLO",     "TAP TO DISMISS",      "SessionStart",
      0xF2B04A, F_HAPPY,  A_BOUNCE,  1800 },
    { "attention", "ALLOW?",    "WAITING FOR YOU",     "Notification / permission",
      0xFF8A4C, F_WIDE,   A_BOUNCE,    1100 },
    { "idle",      "YOUR TURN", "AGENT IS PAUSED",     "idle_prompt",
      0xE8C77A, F_SLEEPY, A_BOUNCE, 3200 },
    { "done",      "DONE",      "TASK FINISHED",       "Stop",
      0xA8C97F, F_HAPPY,  A_BOUNCE, 2400 },
    { "fail",      "TOOL FAIL", "CHECK OUTPUT",        "PostToolUseFailure",
      0xE5533D, F_SAD,    A_BOUNCE,    1600 },
    { "danger",    "DANGER",    "CONFIRM IN TERMINAL", "PreToolUse / rm / push",
      0xFF3B2F, F_SHOCK,  A_BOUNCE,    500 },
    { "ratelimit", "THROTTLED", "COOLING DOWN",        "StopFailure / rate_limit",
      0xC98A5A, F_FLAT,   A_BOUNCE,    2600 },
    { "subagent",  "SUBAGENT",  "HANDED BACK",         "SubagentStop",
      0xD9A3B8, F_WINK,   A_BOUNCE,    1600 },
    { "end",       "BYE",       "SESSION CLOSED",      "SessionEnd",
      0x8A8073, F_CLOSED, A_BOUNCE, 3600 },
};

/*==========================================================================
 * Layout constants (px, at 412x412)
 *========================================================================*/
#define CF_BG              0x0a0908
#define CF_HINT_COLOR      0x6f6a60

#define RING_PULSE_INSET   26
#define RING_PULSE_W       2
#define RING_SPIN_INSET    12
#define RING_SPIN_W        3

#define FACE_BOX_W        210
#define FACE_BOX_H        150
#define GAP_EYE_MOUTH      26
#define GAP_FACE_TEXT      34
#define GAP_LABEL_HINT     12

#define PULSE_BASE   (CF_DISPLAY_SIZE - 2 * RING_PULSE_INSET)   /* 360 */
#define PULSE_MIN    (PULSE_BASE * 82 / 100)                    /* 295  (scale .82) */
#define PULSE_MAX    (PULSE_BASE * 112 / 100)                   /* 403  (scale 1.12) */
#define PULSE_OPA0   ((LV_OPA_COVER * 30 / 100) * 90 / 100)     /* .3 alpha * .9 opacity */

#define SPIN_D       (CF_DISPLAY_SIZE - 2 * RING_SPIN_INSET)    /* 388 */

#define PULSE_MS   2200
#define SPIN_MS    3400
#define BLINK_MS   4400
#define CYCLE_MS   2200

/*==========================================================================
 * CSS easing, sampled at 1/16 steps (0..1000 -> 0..1000)
 *========================================================================*/
static const uint16_t EASE_IN_OUT[17] = {   /* cubic-bezier(.42,0,.58,1) */
    0, 8, 31, 72, 129, 204, 293, 393, 500, 607, 707, 796, 871, 928, 969, 992, 1000
};
static const uint16_t EASE_OUT[17] = {      /* cubic-bezier(0,0,.58,1)   */
    0, 102, 199, 290, 378, 462, 541, 615, 685, 749, 808, 861, 907, 945, 974, 993, 1000
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

/* CSS keyframe: time in per-mille of the iteration, value in the caller's unit */
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

/* @keyframes, straight from the stylesheet -------------------------------*/
static const cf_kf_t KF_BOUNCE_Y[]  = { {0,0}, {400,-16}, {700,4}, {1000,0} };
static const cf_kf_t KF_SWAY_ROT[]  = { {0,-40}, {500,40}, {1000,-40} };        /* 0.1 deg */
static const cf_kf_t KF_BREATHE_S[] = { {0,1000}, {500,1060}, {1000,1000} };    /* per-mille */
static const cf_kf_t KF_SINK_Y[]    = { {0,0}, {500,7}, {1000,0} };
static const cf_kf_t KF_SINK_S[]    = { {0,1000}, {500,970}, {1000,1000} };
static const cf_kf_t KF_SHAKE_X[]   = { {0,0}, {200,-9}, {600,9}, {1000,0} };
static const cf_kf_t KF_SHAKE_ROT[] = { {0,0}, {200,-20}, {600,20}, {1000,0} };
static const cf_kf_t KF_BLINK[]     = { {0,1000}, {920,1000}, {960,100}, {1000,1000} };

/*==========================================================================
 * Instance
 *========================================================================*/
typedef struct {
    lv_obj_t  *root;
    lv_obj_t  *pulse;
    lv_obj_t  *spin;
    lv_obj_t  *col;
    lv_obj_t  *face_box;
    lv_obj_t  *eye_row;
    lv_obj_t  *eye[2];
    lv_obj_t  *mouth;
    lv_obj_t  *label;
    lv_obj_t  *hint;
    lv_timer_t *cycle;
    cf_state_t  state;
    uint8_t     eye_h;
    bool        hint_on;
} cf_ctx_t;

static cf_ctx_t cf;

/*==========================================================================
 * Small helpers
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

/*==========================================================================
 * Animations
 *========================================================================*/
#pragma mark
static void pulse_cb(void *var, int32_t t)
{
    cf_ctx_t *c = (cf_ctx_t *)var;
    int32_t e = ease(EASE_OUT, t);
    int32_t d = PULSE_MIN + (PULSE_MAX - PULSE_MIN) * e / 1000;
    lv_obj_set_size(c->pulse, d, d);
    lv_obj_set_style_border_opa(c->pulse, (lv_opa_t)(PULSE_OPA0 * (1000 - e) / 1000), 0);
}

/* spinring 3.4s linear infinite */
static void spin_cb(void *var, int32_t v)
{
    lv_arc_set_rotation((lv_obj_t *)var, v);
}

/* blink 4.4s linear infinite — squeezes the eyes vertically at 96% */
static void blink_cb(void *var, int32_t t)
{
    cf_ctx_t *c = (cf_ctx_t *)var;
    int32_t h = kf_eval(KF_BLINK, 4, t, false) * c->eye_h / 1000;
    if(h < 1) h = 1;
    lv_obj_set_height(c->eye[0], h);
    lv_obj_set_height(c->eye[1], h);
}

/* the per-state body animation applied to the 210x150 face box */
static void body_cb(void *var, int32_t t)
{
    cf_ctx_t *c = (cf_ctx_t *)var;
    int32_t tx = 0, ty = 0, rot = 0, sc = 1000;

    switch(DEF[c->state].anim) {
        case A_BOUNCE:
            ty = kf_eval(KF_BOUNCE_Y, 4, t, true);
            break;
        case A_SWAY:
            rot = kf_eval(KF_SWAY_ROT, 3, t, true);
            break;
        case A_BREATHE:
            sc = kf_eval(KF_BREATHE_S, 3, t, true);
            break;
        case A_SINK:
            ty = kf_eval(KF_SINK_Y, 3, t, true);
            sc = kf_eval(KF_SINK_S, 3, t, true);
            break;
        case A_SHAKE:
            tx  = kf_eval(KF_SHAKE_X, 4, t, true);
            rot = kf_eval(KF_SHAKE_ROT, 4, t, true);
            break;
        default: break;
    }

    lv_obj_set_style_translate_x(c->face_box, tx, 0);
    lv_obj_set_style_translate_y(c->face_box, ty, 0);
    CF_ROT(c->face_box, rot);
    CF_SCALE(c->face_box, sc * CF_SCALE_NONE / 1000);
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
 * Face construction
 *========================================================================*/
static void build_face(cf_ctx_t *c)
{
    const cf_def_t   *d = &DEF[c->state];
    const cf_shape_t *s = &SHAPE[d->face];
    lv_color_t col = lv_color_hex(d->color);

    /* eyes ---------------------------------------------------------------*/
    lv_obj_set_size(c->eye_row, s->eye_w * 2 + s->eye_gap, s->eye_h);
    lv_obj_set_style_pad_column(c->eye_row, s->eye_gap, 0);
    for(int i = 0; i < 2; i++) {
        lv_obj_set_size(c->eye[i], s->eye_w, s->eye_h);
        lv_obj_set_style_radius(c->eye[i], s->eye_r, 0);
        lv_obj_set_style_bg_color(c->eye[i], col, 0);
        lv_obj_set_style_bg_opa(c->eye[i], LV_OPA_COVER, 0);
    }
    c->eye_h = s->eye_h;

    /* mouth --------------------------------------------------------------*/
    if(c->mouth) CF_OBJ_DEL(c->mouth);
    c->mouth = plain(c->face_box);
    lv_obj_set_size(c->mouth, s->mouth_w, s->mouth_h);

    if(s->mouth_bw == 0) {
        /* solid pill or dot */
        lv_obj_set_style_radius(c->mouth, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_color(c->mouth, col, 0);
        lv_obj_set_style_bg_opa(c->mouth, LV_OPA_COVER, 0);
    }
    else {
        /* open arc: a square arc clipped to the CSS box, so only the
         * bottom (smile) or top (frown) half is visible */
        lv_obj_t *a = lv_arc_create(c->mouth);
        lv_obj_remove_style_all(a);
        lv_obj_set_size(a, s->mouth_w, s->mouth_w);
        lv_obj_align(a, s->mouth_up ? LV_ALIGN_TOP_MID : LV_ALIGN_BOTTOM_MID, 0, 0);
        CF_FLAG_CLR(a, LV_OBJ_FLAG_CLICKABLE);
        CF_FLAG_CLR(a, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_pad_all(a, 0, LV_PART_MAIN);
        lv_obj_set_style_arc_opa(a, LV_OPA_TRANSP, LV_PART_MAIN);
        /* bg_opa alone only hides the knob's fill -- the theme's default
         * border/outline on the knob stay opaque and show up as a stray
         * light arc/blob at the indicator's start/end point, so kill those too */
        lv_obj_set_style_bg_opa(a, LV_OPA_TRANSP, LV_PART_KNOB);
        lv_obj_set_style_border_width(a, 0, LV_PART_KNOB);
        lv_obj_set_style_outline_width(a, 0, LV_PART_KNOB);
        lv_obj_set_style_pad_all(a, 0, LV_PART_KNOB);
        lv_obj_set_style_arc_width(a, s->mouth_bw, LV_PART_MAIN);
        lv_obj_set_style_arc_width(a, s->mouth_bw, LV_PART_INDICATOR);
        lv_obj_set_style_arc_color(a, col, LV_PART_INDICATOR);
        lv_obj_set_style_arc_opa(a, LV_OPA_COVER, LV_PART_INDICATOR);
        lv_obj_set_style_arc_rounded(a, false, LV_PART_INDICATOR);
        /* LVGL angles: 0 deg = 3 o'clock, growing clockwise */
        if(s->mouth_up) { lv_arc_set_bg_angles(a, 180, 360); lv_arc_set_angles(a, 180, 360); }
        else            { lv_arc_set_bg_angles(a, 0, 180);   lv_arc_set_angles(a, 0, 180);   }
    }

    /* rings + text -------------------------------------------------------*/
#if CF_ENABLE_PULSE_HALO
    lv_obj_set_style_border_color(c->pulse, col, 0);
#endif
    lv_obj_set_style_arc_color(c->spin, col, LV_PART_INDICATOR);

    lv_label_set_text(c->label, d->label);
    lv_obj_set_style_text_color(c->label, col, 0);
    lv_label_set_text(c->hint, d->hint);

    if(c->hint_on) CF_FLAG_CLR(c->hint, LV_OBJ_FLAG_HIDDEN);
    else           lv_obj_add_flag(c->hint, LV_OBJ_FLAG_HIDDEN);

    /* restart the shape-dependent animations -----------------------------*/
    CF_ANIM_DEL(c, body_cb);
    CF_ANIM_DEL(c, blink_cb);
    lv_obj_set_style_translate_x(c->face_box, 0, 0);
    lv_obj_set_style_translate_y(c->face_box, 0, 0);
    CF_ROT(c->face_box, 0);
    CF_SCALE(c->face_box, CF_SCALE_NONE);
    anim_start(body_cb, d->dur, c);
    anim_start(blink_cb, BLINK_MS, c);
}

/*==========================================================================
 * Public API
 *========================================================================*/
lv_obj_t *claude_face_create(lv_obj_t *parent)
{
    if(cf.root) claude_face_destroy();
    if(parent == NULL) parent = CF_SCR_ACT();

    memset(&cf, 0, sizeof(cf));
    cf.state   = CF_STATE_ATTENTION;   /* the design opens on "attention" */
    cf.hint_on = true;

    /* round screen ------------------------------------------------------*/
    /* the parent screen defaults to a white background; paint it to match
     * so the 5px offset above doesn't expose a white sliver at the edge */
    lv_obj_set_style_bg_color(parent, lv_color_hex(CF_BG), 0);
    lv_obj_set_style_bg_opa(parent, LV_OPA_COVER, 0);

    cf.root = plain(parent);
    lv_obj_set_size(cf.root, CF_DISPLAY_SIZE, CF_DISPLAY_SIZE);
    lv_obj_align(cf.root, LV_ALIGN_CENTER, 5, 0);   /* shift everything 5px right */
    lv_obj_set_style_bg_color(cf.root, lv_color_hex(CF_BG), 0);
    lv_obj_set_style_bg_opa(cf.root, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(cf.root, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(cf.root, true, 0);

    /* pulsing halo ------------------------------------------------------*/
#if CF_ENABLE_PULSE_HALO
    cf.pulse = plain(cf.root);
    lv_obj_set_size(cf.pulse, PULSE_BASE, PULSE_BASE);
    lv_obj_set_align(cf.pulse, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(cf.pulse, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_border_width(cf.pulse, RING_PULSE_W, 0);
    lv_obj_set_style_border_opa(cf.pulse, PULSE_OPA0, 0);
#endif

    /* spinning 90 deg arc ------------------------------------------------*/
    cf.spin = lv_arc_create(cf.root);
    lv_obj_remove_style_all(cf.spin);
    lv_obj_set_size(cf.spin, SPIN_D, SPIN_D);
    lv_obj_center(cf.spin);
    CF_FLAG_CLR(cf.spin, LV_OBJ_FLAG_CLICKABLE);
    CF_FLAG_CLR(cf.spin, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(cf.spin, 0, LV_PART_MAIN);
    lv_obj_set_style_arc_opa(cf.spin, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cf.spin, LV_OPA_TRANSP, LV_PART_KNOB);
    lv_obj_set_style_border_width(cf.spin, 0, LV_PART_KNOB);
    lv_obj_set_style_outline_width(cf.spin, 0, LV_PART_KNOB);
    lv_obj_set_style_pad_all(cf.spin, 0, LV_PART_KNOB);
    lv_obj_set_style_arc_width(cf.spin, RING_SPIN_W, LV_PART_MAIN);
    lv_obj_set_style_arc_width(cf.spin, RING_SPIN_W, LV_PART_INDICATOR);
    lv_obj_set_style_arc_opa(cf.spin, LV_OPA_COVER, LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(cf.spin, false, LV_PART_INDICATOR);
    lv_arc_set_bg_angles(cf.spin, 225, 315);   /* 90 deg centred on 12 o'clock */
    lv_arc_set_angles(cf.spin, 225, 315);

    /* content column ----------------------------------------------------*/
    cf.col = flex_col(cf.root, GAP_FACE_TEXT);
    lv_obj_center(cf.col);

    cf.face_box = plain(cf.col);
    lv_obj_set_size(cf.face_box, FACE_BOX_W, FACE_BOX_H);
    lv_obj_set_flex_flow(cf.face_box, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cf.face_box, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(cf.face_box, GAP_EYE_MOUTH, 0);
    lv_obj_set_style_transform_pivot_x(cf.face_box, FACE_BOX_W / 2, 0);
    lv_obj_set_style_transform_pivot_y(cf.face_box, FACE_BOX_H / 2, 0);

    cf.eye_row = plain(cf.face_box);
    lv_obj_set_flex_flow(cf.eye_row, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cf.eye_row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_CENTER);
    cf.eye[0] = plain(cf.eye_row);
    cf.eye[1] = plain(cf.eye_row);

    lv_obj_t *text = flex_col(cf.col, GAP_LABEL_HINT);

    cf.label = lv_label_create(text);
    lv_obj_set_style_text_font(cf.label, CF_FONT_LABEL, 0);
    lv_obj_set_style_text_letter_space(cf.label, 2, 0);   /* .06em @ 34px */

    cf.hint = lv_label_create(text);
    lv_obj_set_style_text_font(cf.hint, CF_FONT_HINT, 0);
    lv_obj_set_style_text_letter_space(cf.hint, 1, 0);    /* .10em @ 13px */
    lv_obj_set_style_text_color(cf.hint, lv_color_hex(CF_HINT_COLOR), 0);

    build_face(&cf);
#if CF_ENABLE_PULSE_HALO
    anim_start(pulse_cb, PULSE_MS, &cf);
#endif

    lv_anim_t a;                                   /* spinring */
    lv_anim_init(&a);
    lv_anim_set_var(&a, cf.spin);
    lv_anim_set_exec_cb(&a, spin_cb);
    lv_anim_set_values(&a, 0, 360);
    lv_anim_set_time(&a, SPIN_MS);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);

    return cf.root;
}

void claude_face_destroy(void)
{
    if(!cf.root) return;
    claude_face_cycle(false);
    CF_ANIM_DEL(&cf, NULL);
    CF_OBJ_DEL(cf.root);
    memset(&cf, 0, sizeof(cf));
}

void claude_face_set_state(cf_state_t s)
{
    if(!cf.root || s >= CF_STATE_COUNT || s == cf.state) return;
    cf.state = s;
    build_face(&cf);
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

static void cycle_cb(lv_timer_t *t)
{
    LV_UNUSED(t);
    claude_face_next();
}

void claude_face_cycle(bool en)
{
    if(en) {
        if(!cf.cycle) cf.cycle = lv_timer_create(cycle_cb, CYCLE_MS, NULL);
    }
    else if(cf.cycle) {
        CF_TIMER_DEL(cf.cycle);
        cf.cycle = NULL;
    }
}

lv_obj_t   *claude_face_root(void)                 { return cf.root; }
const char *claude_face_key(cf_state_t s)          { return DEF[s % CF_STATE_COUNT].key; }
const char *claude_face_label(cf_state_t s)        { return DEF[s % CF_STATE_COUNT].label; }
const char *claude_face_hint(cf_state_t s)         { return DEF[s % CF_STATE_COUNT].hint; }
const char *claude_face_trigger(cf_state_t s)      { return DEF[s % CF_STATE_COUNT].trigger; }
lv_color_t  claude_face_color(cf_state_t s)        { return lv_color_hex(DEF[s % CF_STATE_COUNT].color); }

cf_state_t claude_face_from_key(const char *key)
{
    if(key) {
        for(int i = 0; i < CF_STATE_COUNT; i++) {
            if(strcmp(key, DEF[i].key) == 0) return (cf_state_t)i;
        }
    }
    return CF_STATE_IDLE;
}

#endif /* CF_FACE_VERSION == 1 */
