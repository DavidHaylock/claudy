/**
 * @file claude_face_v2_danger.cpp
 * Claude Status Faces v2 — DANGER (PreToolUse guard on rm / git push)
 *
 * Geometry from designs/Claude Status Faces v2.dc.html:273-319 /
 * claude_face_v2_PLAN.md section 7, absolute px on the 412x412 canvas.
 *
 * Brows (3 offset slabs per side) + eyes shake together (`shake`, 2.2s);
 * the 7-rect zigzag mouth is static, matching the source HTML where only
 * the brow+eye group sits inside the `animation:shake` wrapper. The dashed
 * ring (lively only) is 30 short lv_arc segments spaced 12deg apart -- the
 * repeating-conic-gradient's period -- animated 0 -> 12deg in 300ms
 * (9000ms / (360/12)), per claude_face_v2_PLAN.md's "useful shortcut": a
 * 12deg sweep is visually identical to a full 360deg spin at the same
 * angular speed, since the dash pattern repeats every 12deg, and costs far
 * less to recompute every frame.
 */

#include "claude_face_v2_faces.h"

#if CF_FACE_VERSION == 2

#define DANGER_BROW_COL 0xC65D26u
#define DANGER_RING_COL 0xFF8C49u

#if CF2_LIVELY
#define DANGER_RING_N     30
#define DANGER_RING_SPAN  6   /* deg, matches the CSS dash width */
#define DANGER_RING_PITCH 12  /* deg, dash + gap == the repeat period */

static lv_obj_t *g_danger_ring[DANGER_RING_N];

static void danger_ring_cb(void *var, int32_t v)
{
    LV_UNUSED(var);
    for(int i = 0; i < DANGER_RING_N; i++)
        lv_arc_set_rotation(g_danger_ring[i], v);
}
#endif

void build_danger(lv_obj_t *scene, const cf2_def_t *d)
{
    /* brow row is a flex row (pitch 32, no gap); each slab's own
     * margin-top staggers it vertically -- left dips toward the eye,
     * right rises away from it, mirror images of each other. */
    static const int8_t BROW_L_DY[3] = { 0, 12, 24 };
    static const int8_t BROW_R_DY[3] = { 24, 12, 0 };
    static const int8_t MOUTH_DY[7]  = { 0, 16, 0, 16, 0, 16, 0 };

    lv_obj_t *shakers[8];
    cf2_rect_row(scene, 86, 112, 3, 32, 14, 32, BROW_L_DY, DANGER_BROW_COL, shakers);
    shakers[3] = cf2_rect(scene, 86, 160, 96, 52, d->accent);        /* eye L */
    cf2_rect_row(scene, 230, 112, 3, 32, 14, 32, BROW_R_DY, DANGER_BROW_COL, shakers + 4);
    shakers[7] = cf2_rect(scene, 230, 160, 96, 52, d->accent);       /* eye R */
    cf2_shake_start(shakers, 8, 2200);

    cf2_rect_row(scene, 143, 250, 7, 18, 18, 18, MOUTH_DY, d->accent, NULL);

#if CF2_LIVELY
    for(int i = 0; i < DANGER_RING_N; i++) {
        int a0 = i * DANGER_RING_PITCH;
        g_danger_ring[i] = cf2_arc(scene, 6, 8, DANGER_RING_COL, a0, a0 + DANGER_RING_SPAN,
                                    LV_OPA_COVER);
    }
    /* var = the first dash, a genuine scene child -- lv_obj_clean(scene) on
     * the next state change deletes it, and LVGL cancels this anim as a
     * side effect of deleting its var, same technique cf2_zzz_start() uses
     * (see its comment in claude_face_v2.cpp). No explicit stop needed. */
    lv_anim_t ra;
    lv_anim_init(&ra);
    lv_anim_set_var(&ra, g_danger_ring[0]);
    lv_anim_set_exec_cb(&ra, danger_ring_cb);
    lv_anim_set_values(&ra, 0, DANGER_RING_PITCH);
    lv_anim_set_time(&ra, 300);
    lv_anim_set_path_cb(&ra, lv_anim_path_linear);
    lv_anim_set_repeat_count(&ra, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&ra);
#endif
}

#endif /* CF_FACE_VERSION == 2 */
