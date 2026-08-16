/**
 * @file claude_face_v2_attention.cpp
 * Claude Status Faces v2 — ATTENTION (Notification / permission_prompt,
 * word "YOUR TURN")
 *
 * Geometry from designs/Claude Status Faces v2.dc.html:125-159 /
 * claude_face_v2_PLAN.md section 3, absolute px on the 412x412 canvas.
 *
 * Brows + eyes drift together (`drift`, 2.6s); each eye's pupil-hole cutout
 * (a 30x30 rect painted in the disc's own background colour, `d->bg`, so it
 * reads as a hole rather than a second shape) has to drift *with* its eye
 * -- the source CSS nests the hole inside the eye div so a transform on the
 * eye carries the hole along for free, but this port draws every element as
 * a flat sibling rect, so the hole is included in the same cf2_drift_start()
 * call as its eye. The mouth dot pulses on its own (`pulse`, 1.3s) and the
 * bezel ring breathes (`breathe`, 1.3s) when CF2_LIVELY -- both single-object
 * animations, built locally with LVGL's native playback+path mechanism
 * (same technique claude_face_v2_start.cpp's sweep bar uses) rather than
 * the shared kf_eval() engine, since neither is reused by another state.
 */

#include "claude_face_v2_faces.h"

#if CF_FACE_VERSION == 2

#if CF2_LIVELY
/* pulse: mouth dot scale 1 -> 1.18 (+ bg_opa 255 -> 178) about its own
 * centre (206, 276) -- LVGL 8.3 can't transform_zoom a plain obj, so this
 * recomputes size + centred pos every frame instead, per
 * claude_face_v2_PLAN.md's guidance. */
static void pulse_cb(void *var, int32_t v)
{
    lv_obj_t *o = (lv_obj_t *)var;
    int32_t size = 36 + v * (36 * 18 / 100) / 1000;   /* 36 -> 36*1.18 */
    lv_obj_set_size(o, size, size);
    lv_obj_set_pos(o, 206 - size / 2, 276 - size / 2);
    lv_obj_set_style_bg_opa(o, (lv_opa_t)(255 - v * 77 / 1000), 0);
}

/* breathe: ring border_opa 0.3 -> 1 -> 0.3 (77 -> 255 -> 77). */
static void breathe_cb(void *var, int32_t v)
{
    lv_obj_t *o = (lv_obj_t *)var;
    lv_obj_set_style_border_opa(o, (lv_opa_t)(77 + v * 178 / 1000), 0);
}
#endif

void build_attention(lv_obj_t *scene, const cf2_def_t *d)
{
    lv_obj_t *drifters[6];
    drifters[0] = cf2_rect(scene, 84,  96,  96, 14, d->accent);          /* brow L */
    drifters[1] = cf2_rect(scene, 84,  128, 96, 96, d->accent);          /* eye L  */
    drifters[2] = cf2_rect(scene, 98,  142, 30, 30, d->bg);              /* eye L hole */
    drifters[3] = cf2_rect(scene, 232, 96,  96, 14, d->accent);          /* brow R */
    drifters[4] = cf2_rect(scene, 232, 128, 96, 96, d->accent);          /* eye R  */
    drifters[5] = cf2_rect(scene, 246, 142, 30, 30, d->bg);              /* eye R hole */
    cf2_drift_start(drifters, 6, 2600);

#if CF2_LIVELY
    lv_obj_t *ring = cf2_ring(scene, 6, 8, d->accent);
    lv_anim_t ba;
    lv_anim_init(&ba);
    lv_anim_set_var(&ba, ring);
    lv_anim_set_exec_cb(&ba, breathe_cb);
    lv_anim_set_values(&ba, 0, 1000);
    lv_anim_set_time(&ba, 650);
    lv_anim_set_playback_time(&ba, 650);
    lv_anim_set_path_cb(&ba, lv_anim_path_ease_in_out);
    lv_anim_set_repeat_count(&ba, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&ba);
#endif

    lv_obj_t *mouth = cf2_rect(scene, 188, 258, 36, 36, d->accent);
#if CF2_LIVELY
    lv_anim_t pa;
    lv_anim_init(&pa);
    lv_anim_set_var(&pa, mouth);
    lv_anim_set_exec_cb(&pa, pulse_cb);
    lv_anim_set_values(&pa, 0, 1000);
    lv_anim_set_time(&pa, 650);
    lv_anim_set_playback_time(&pa, 650);
    lv_anim_set_path_cb(&pa, lv_anim_path_ease_in_out);
    lv_anim_set_repeat_count(&pa, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&pa);
#endif
}

#endif /* CF_FACE_VERSION == 2 */
