/**
 * @file claude_face_v2_start.cpp
 * Claude Status Faces v2 — START (SessionStart / startup, word "BOOTING")
 *
 * Geometry from designs/Claude Status Faces v2.dc.html:44-82 /
 * claude_face_v2_PLAN.md section 1, absolute px on the 412x412 canvas.
 *
 * Brows + both eye halves bob together (`bob`, 3.2s); the four eye halves
 * additionally blink as one group (`blink`, 5s) independently of the bob.
 * The mouth is a sweep bar that grows/shrinks between 12px and 168px when
 * CF2_LIVELY, or a fixed 56px bar when not -- it does not bob or blink.
 */

#include "claude_face_v2_faces.h"

#if CF_FACE_VERSION == 2

#define START_BROW_COL      0x4E9A52u
#define START_EYE_DARK_COL  0x4D9351u

#if CF2_LIVELY
static void sweep_width_cb(void *var, int32_t v)
{
    lv_obj_t *o = (lv_obj_t *)var;
    lv_obj_set_width(o, v);
    lv_obj_set_x(o, 206 - v / 2);
}
#endif

void build_start(lv_obj_t *scene, const cf2_def_t *d)
{
    lv_obj_t *bobbers[6];
    bobbers[0] = cf2_rect(scene, 82,  104, 96, 14, START_BROW_COL);      /* brow L */
    bobbers[1] = cf2_rect(scene, 234, 104, 96, 14, START_BROW_COL);      /* brow R */
    bobbers[2] = cf2_rect(scene, 82,  134, 48, 96, d->accent);           /* eye L light */
    bobbers[3] = cf2_rect(scene, 130, 134, 48, 96, START_EYE_DARK_COL);  /* eye L dark  */
    bobbers[4] = cf2_rect(scene, 234, 134, 48, 96, d->accent);           /* eye R light */
    bobbers[5] = cf2_rect(scene, 282, 134, 48, 96, START_EYE_DARK_COL);  /* eye R dark  */
    cf2_bob_start(bobbers, 6, 3200);

    lv_obj_t *eye_halves[4] = { bobbers[2], bobbers[3], bobbers[4], bobbers[5] };
    cf2_blink_start(eye_halves, 4, 5000);

    /* mouth -- sweep bar, centred at x=206 (206 - w/2) */
#if CF2_LIVELY
    lv_obj_t *mouth = cf2_rect(scene, 200, 262, 12, 14, d->accent);
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, mouth);
    lv_anim_set_exec_cb(&a, sweep_width_cb);
    lv_anim_set_values(&a, 12, 168);
    lv_anim_set_time(&a, 1800);
    lv_anim_set_playback_time(&a, 1800);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
#else
    cf2_rect(scene, 178, 262, 56, 14, d->accent);
#endif
}

#endif /* CF_FACE_VERSION == 2 */
