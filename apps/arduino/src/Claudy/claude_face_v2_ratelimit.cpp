/**
 * @file claude_face_v2_ratelimit.cpp
 * Claude Status Faces v2 — RATELIMIT (StopFailure / rate_limit, word
 * "RATE LIMIT")
 *
 * Geometry from designs/Claude Status Faces v2.dc.html:203-233 /
 * claude_face_v2_PLAN.md section 5, absolute px on the 412x412 canvas.
 *
 * Eyes are 96x96 bordered frames (cf2_frame(), 20px border, no fill) with a
 * 20x20 pupil that orbits the frame's centre at radius 8 -- per
 * claude_face_v2_PLAN.md's D5(a), this stands in for the design's literal
 * `transform: rotate()` on the frame itself, which is unproven on plain
 * LVGL 8.3 objects. The pupil's rest position (design default, 8px left of
 * centre) is orbit angle 180 deg in the standard math convention used here
 * (x = cx + r*cos(theta), y = cy + r*sin(theta)); increasing theta sweeps
 * 3 o'clock -> 6 -> 9 -> 12 -> 3, i.e. clockwise on screen, so the left
 * eye's `spin` is +theta and the right eye's `spinback` is -theta. Kept
 * local (not promoted to the shared engine) since the eye-centre constants
 * are baked into the two callbacks, mirroring claude_face_v2_danger.cpp's
 * local ring-spin driver.
 *
 * The mouth's three dots tick together via the shared engine
 * (cf2_tick_start(), phased 0/167/333 permille of 1200ms). The gauge
 * (lively only) is six cf2_arc() segments spanning 108->270deg with an
 * opacity ramp, rotated as a group via lv_arc_set_rotation() -- same
 * auto-cancel-on-scene-clean technique as danger's dashed ring, so no
 * explicit stop function is needed.
 */

#include "claude_face_v2_faces.h"

#if CF_FACE_VERSION == 2

#include <math.h>

/* the gauge ring is a notch darker than the eyes/mouth (`d->accent`,
 * 0xCF9BFF) -- distinct swatches per claude_face_v2_PLAN.md's oklch->hex
 * table, same pattern as danger's separate ring/brow colours. */
#define RATELIMIT_GAUGE_COL 0xC995FFu

#define RATELIMIT_EYE_L_CX 132
#define RATELIMIT_EYE_L_CY 160
#define RATELIMIT_EYE_R_CX 280
#define RATELIMIT_EYE_R_CY 160
#define RATELIMIT_ORBIT_R  8

/* left eye pupil, `spin` (CW): theta = 180deg + v */
static void orbit_cw_cb(void *var, int32_t v)
{
    lv_obj_t *o = (lv_obj_t *)var;
    float theta = (180.0f + (float)v) * (float)M_PI / 180.0f;
    int cx = RATELIMIT_EYE_L_CX + (int)lroundf(RATELIMIT_ORBIT_R * cosf(theta));
    int cy = RATELIMIT_EYE_L_CY + (int)lroundf(RATELIMIT_ORBIT_R * sinf(theta));
    lv_obj_set_pos(o, cx - 10, cy - 10);
}

/* right eye pupil, `spinback` (CCW): theta = 180deg - v */
static void orbit_ccw_cb(void *var, int32_t v)
{
    lv_obj_t *o = (lv_obj_t *)var;
    float theta = (180.0f - (float)v) * (float)M_PI / 180.0f;
    int cx = RATELIMIT_EYE_R_CX + (int)lroundf(RATELIMIT_ORBIT_R * cosf(theta));
    int cy = RATELIMIT_EYE_R_CY + (int)lroundf(RATELIMIT_ORBIT_R * sinf(theta));
    lv_obj_set_pos(o, cx - 10, cy - 10);
}

static void orbit_start(lv_obj_t *pupil, lv_anim_exec_xcb_t cb)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, pupil);
    lv_anim_set_exec_cb(&a, cb);
    lv_anim_set_values(&a, 0, 360);
    lv_anim_set_time(&a, 3400);
    lv_anim_set_path_cb(&a, lv_anim_path_linear);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}

#if CF2_LIVELY
#define RATELIMIT_GAUGE_N 6
static lv_obj_t *g_gauge[RATELIMIT_GAUGE_N];

static void gauge_spin_cb(void *var, int32_t v)
{
    LV_UNUSED(var);
    for(int i = 0; i < RATELIMIT_GAUGE_N; i++)
        lv_arc_set_rotation(g_gauge[i], v);
}
#endif

void build_ratelimit(lv_obj_t *scene, const cf2_def_t *d)
{
    cf2_frame(scene, 84,  112, 96, 96, 20, d->accent);   /* eye L frame */
    lv_obj_t *pupil_l = cf2_rect(scene, 114, 150, 20, 20, d->accent);
    orbit_start(pupil_l, orbit_cw_cb);

    cf2_frame(scene, 232, 112, 96, 96, 20, d->accent);   /* eye R frame */
    lv_obj_t *pupil_r = cf2_rect(scene, 262, 150, 20, 20, d->accent);
    orbit_start(pupil_r, orbit_ccw_cb);

    static const int8_t DOT_DY[3] = { 0, 0, 0 };
    lv_obj_t *dots[3];
    cf2_rect_row(scene, 167, 254, 3, 18, 18, 30, DOT_DY, d->accent, dots);
    static const uint16_t DOT_PHASE[3] = { 0, 167, 333 };
    cf2_tick_start(dots, DOT_PHASE, 3, 1200);

#if CF2_LIVELY
    /* CSS conic gradient: transparent 0-55%, ramping to full colour by
     * 100% -- visible span is 198deg->360deg in CSS's 12-o'clock-start,
     * CCW-negative-is-clockwise convention; converting to LVGL's
     * 3-o'clock-start/CW convention (lvgl = css - 90) gives 108->270deg,
     * split into 6 segments of 27deg each with an opacity ramp standing in
     * for the gradient. */
    static const int a0[RATELIMIT_GAUGE_N]  = { 108, 135, 162, 189, 216, 243 };
    static const lv_opa_t op[RATELIMIT_GAUGE_N] = { 21, 64, 107, 149, 191, 234 };
    for(int i = 0; i < RATELIMIT_GAUGE_N; i++)
        g_gauge[i] = cf2_arc(scene, 6, 8, RATELIMIT_GAUGE_COL, a0[i], a0[i] + 27, op[i]);

    /* var = the first segment, a genuine scene child -- lv_obj_clean(scene)
     * deletes it on the next state change and LVGL cancels this anim as a
     * side effect, same technique as danger's ring (see its comment). */
    lv_anim_t ga;
    lv_anim_init(&ga);
    lv_anim_set_var(&ga, g_gauge[0]);
    lv_anim_set_exec_cb(&ga, gauge_spin_cb);
    lv_anim_set_values(&ga, 0, -360);
    lv_anim_set_time(&ga, 5000);
    lv_anim_set_path_cb(&ga, lv_anim_path_linear);
    lv_anim_set_repeat_count(&ga, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&ga);
#endif
}

#endif /* CF_FACE_VERSION == 2 */
