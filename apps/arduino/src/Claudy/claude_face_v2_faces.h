/**
 * @file claude_face_v2_faces.h
 * Shared contract between claude_face_v2.cpp (chrome, lifecycle, primitives)
 * and the per-state face builders (claude_face_v2_<state>.cpp).
 *
 * All nine states are implemented -- see claude_face_v2.cpp's BUILDER[]
 * table. A future design revision that adds a new state is additive: write
 * claude_face_v2_<state>.cpp, declare its build_<state>() below, and point
 * BUILDER[CF_STATE_<STATE>] at it.
 */
#ifndef CLAUDE_FACE_V2_FACES_H
#define CLAUDE_FACE_V2_FACES_H

#include "claude_face_config.h"
#if CF_FACE_VERSION == 2

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Per-state chrome row. claude_face_v2.cpp owns and populates DEF[]; face
 *  builders only read it (mainly `accent`, the state's shape colour). */
typedef struct {
    const char *key;         /* hook script key, e.g. "done" */
    const char *hook;        /* hook-event caption, y=40 */
    const char *word;        /* state word, Silkscreen */
    const char *hint;        /* detail line under the word */
    const char *trigger;     /* metadata only: claude_face_trigger() */
    uint32_t    bg;          /* disc fill -- gradient centre / LVGL 8.3 flat fallback,
                               * see claude_face_v2_PLAN.md D3 */
    uint32_t    bg_outer;    /* disc fill -- gradient edge (LVGL 9 sim only, unused on
                               * the LVGL 8.3 firmware fallback) */
    uint32_t    accent;      /* primary shape colour; also claude_face_color() */
    uint32_t    word_col;    /* state word colour, one notch lighter than accent */
    const lv_font_t *word_font;
    uint16_t    word_y;      /* 314 / 318 / 322 */
    lv_opa_t    hint_opa;
    lv_opa_t    hook_opa;
} cf2_def_t;

/** A single solid rect, absolute px, no radius (v2 is rectangles only). */
lv_obj_t *cf2_rect(lv_obj_t *p, int x, int y, int w, int h, uint32_t col);

/** n rects of w x h, pitch (w+gap), with per-item y offsets `dy`.
 *  Fills `out[0..n-1]` with the created objects if `out` is non-NULL --
 *  callers need this to hand the objects to cf2_bob_start() etc. */
void cf2_rect_row(lv_obj_t *p, int x, int y, int n, int w, int h, int pitch,
                   const int8_t *dy, uint32_t col, lv_obj_t **out);

/** A centred-origin (top-left at x,y) text label -- e.g. idle's "z" glyphs. */
lv_obj_t *cf2_text(lv_obj_t *p, int x, int y, const lv_font_t *f, uint32_t col,
                    const char *s);

/** A bare ring segment styled as an lv_arc (v1's arc trick from
 *  claude_face.cpp: transparent MAIN, coloured INDICATOR only, KNOB parts
 *  killed so no stray blob shows at the segment's ends). `inset` px from
 *  the 412 edge, `bw` stroke width, `a0`/`a1` LVGL angles (0 = 3 o'clock,
 *  growing clockwise), `opa` indicator opacity. Used by danger's dashed
 *  ring and ratelimit's conic gauge. */
lv_obj_t *cf2_arc(lv_obj_t *p, int inset, int bw, uint32_t col,
                   int a0, int a1, lv_opa_t opa);

/** A full circular ring, border only, no fill -- attention's breathing
 *  bezel. `inset` px from the 412 edge, matching cf2_arc()'s convention. */
lv_obj_t *cf2_ring(lv_obj_t *p, int inset, int bw, uint32_t col);

/** A square-cornered rect, border only, no fill -- ratelimit's eye frames.
 *  `w`/`h` is the full visible box including the `bw` stroke (LVGL borders
 *  draw inside the box, same as the CSS this is ported from). */
lv_obj_t *cf2_frame(lv_obj_t *p, int x, int y, int w, int h, int bw, uint32_t col);

/** Starts (or restarts) the "bob" animation: 2.4s-class ease-in-out
 *  translate_y, 0 -> -12 -> 0, applied identically to every object in
 *  `objs`. claude_face_v2.cpp stops it automatically on the next
 *  claude_face_set_state() call, before lv_obj_clean()-ing the scene --
 *  builders never need to stop it themselves. */
void cf2_bob_start(lv_obj_t **objs, uint8_t n, uint32_t dur_ms);

/** Starts the "zzz" animation on a single object: translate_y 8 -> -20
 *  over the full cycle plus a text_opa fade peaking at 40%, matching the
 *  design's `zzz` keyframes. `delay_ms` gives it a persistent phase
 *  offset (e.g. idle's second "z" starts 800ms into a 2400ms loop). `obj`
 *  must be a child of `scene` -- see the implementation comment in
 *  claude_face_v2.cpp for why no separate stop() call is needed. */
void cf2_zzz_start(lv_obj_t *obj, uint32_t dur_ms, uint32_t delay_ms);

/** Starts the "shake" animation: 2.4s-class ease-in-out translate_x,
 *  0 -> -8 -> +8 -> -5 -> +5 -> 0, applied identically to every object in
 *  `objs` (fail's grid cells). Same stop-on-next-state-change contract as
 *  cf2_bob_start(). */
void cf2_shake_start(lv_obj_t **objs, uint8_t n, uint32_t dur_ms);

/** Starts the "drift" animation: 2.6s-class ease-in-out translate_x,
 *  -12 -> +12 -> -12, applied identically to every object in `objs`
 *  (attention's brows, eyes and pupil-hole cut-outs -- since this port
 *  draws the holes as separate sibling rects rather than true children of
 *  the eye, they must be included in this call too so they visually track
 *  the eye's drift instead of staying put). Same stop-on-next-state-change
 *  contract as cf2_bob_start(). */
void cf2_drift_start(lv_obj_t **objs, uint8_t n, uint32_t dur_ms);

/** Starts the "blink" animation on `objs` (start's eye halves): each
 *  object's height eases down to ~6% and back around its own vertical
 *  centre, holding open for most of the cycle -- a resize-based stand-in
 *  for CSS `scaleY`, which LVGL 8.3 objects don't support directly. Same
 *  stop-on-next-state-change contract as cf2_bob_start(); call after the
 *  objects are positioned so their open-state y/height can be captured as
 *  the baseline. */
void cf2_blink_start(lv_obj_t **objs, uint8_t n, uint32_t dur_ms);

/** Starts the "blink2" animation on `objs` (subagent's 2x2 eye-cell grids):
 *  same steps(1,end) height-collapse technique as cf2_blink_start(), but
 *  each object gets its own per-mille `phase[i]` offset into the cycle so
 *  the two eyes can blink out of phase in a single call (left eye phase 0,
 *  right eye phase 62 == ~250ms of a 4000ms cycle). Same
 *  capture-baseline-then-animate contract as cf2_blink_start(). */
void cf2_blink2_start(lv_obj_t **objs, const uint16_t *phase, uint8_t n, uint32_t dur_ms);

/** Starts the "fadeout" animation: `bg_opa` on every object in `objs` eases
 *  255 -> 51 -> 255 over `dur_ms` (one full cycle reproduces the design's
 *  4s-alternate 8s round trip). end's whole face fades as one group. Same
 *  stop-on-next-state-change contract as cf2_bob_start(). */
void cf2_fadeout_start(lv_obj_t **objs, uint8_t n, uint32_t dur_ms);

/** Starts the "tick" animation on `objs` (ratelimit's mouth dots):
 *  translate_y 0 -> 6 -> 0, ease-in-out, over `dur_ms`. Each object gets
 *  its own per-mille `phase[i]` offset (CSS animation-delay semantics --
 *  see cf2_blink2_start()'s comment on the subtract-not-add sign
 *  convention this shares). Same stop-on-next-state-change contract as
 *  cf2_bob_start(). */
void cf2_tick_start(lv_obj_t **objs, const uint16_t *phase, uint8_t n, uint32_t dur_ms);

/** START -- claude_face_v2_start.cpp. `scene` is an empty, full-size,
 *  transparent container; `d` is `&DEF[CF_STATE_START]`. */
void build_start(lv_obj_t *scene, const cf2_def_t *d);

/** ATTENTION -- claude_face_v2_attention.cpp. `scene` is an empty,
 *  full-size, transparent container; `d` is `&DEF[CF_STATE_ATTENTION]`. */
void build_attention(lv_obj_t *scene, const cf2_def_t *d);

/** IDLE -- claude_face_v2_idle.cpp. `scene` is an empty, full-size,
 *  transparent container; `d` is `&DEF[CF_STATE_IDLE]`. */
void build_idle(lv_obj_t *scene, const cf2_def_t *d);

/** DONE -- claude_face_v2_done.cpp. `scene` is an empty, full-size,
 *  transparent container; `d` is `&DEF[CF_STATE_DONE]`. */
void build_done(lv_obj_t *scene, const cf2_def_t *d);

/** FAIL -- claude_face_v2_fail.cpp. `scene` is an empty, full-size,
 *  transparent container; `d` is `&DEF[CF_STATE_FAIL]`. */
void build_fail(lv_obj_t *scene, const cf2_def_t *d);

/** DANGER -- claude_face_v2_danger.cpp. `scene` is an empty, full-size,
 *  transparent container; `d` is `&DEF[CF_STATE_DANGER]`. */
void build_danger(lv_obj_t *scene, const cf2_def_t *d);

/** RATELIMIT -- claude_face_v2_ratelimit.cpp. `scene` is an empty,
 *  full-size, transparent container; `d` is `&DEF[CF_STATE_RATELIMIT]`. */
void build_ratelimit(lv_obj_t *scene, const cf2_def_t *d);

/** SUBAGENT -- claude_face_v2_subagent.cpp. `scene` is an empty, full-size,
 *  transparent container; `d` is `&DEF[CF_STATE_SUBAGENT]`. */
void build_subagent(lv_obj_t *scene, const cf2_def_t *d);

/** END -- claude_face_v2_end.cpp. `scene` is an empty, full-size,
 *  transparent container; `d` is `&DEF[CF_STATE_END]`. */
void build_end(lv_obj_t *scene, const cf2_def_t *d);

#ifdef __cplusplus
}
#endif

#endif /* CF_FACE_VERSION == 2 */
#endif /* CLAUDE_FACE_V2_FACES_H */
