/**
 * @file claude_face_v2_done.cpp
 * Claude Status Faces v2 — DONE (Stop)
 *
 * Geometry from designs/Claude Status Faces v2.dc.html:161-201 /
 * claude_face_v2_PLAN.md section 4, absolute px on the 412x412 canvas.
 *
 * Eyes: two chevrons of five 24x24 squares, pitch 24 (no gap), dy sweeping
 * the row up toward the middle (48,24,0,24,48) so the pair reads as a
 * checkmark shape. Only the eyes animate (`bob`, 2.4s); the mouth is
 * static, matching the source HTML where the eyes sit in their own
 * `animation:bob` wrapper and the mouth doesn't.
 */

#include "claude_face_v2_faces.h"

#if CF_FACE_VERSION == 2

void build_done(lv_obj_t *scene, const cf2_def_t *d)
{
    static const int8_t EYE_DY[5]   = { 48, 24, 0, 24, 48 };
    static const int8_t MOUTH_DY[6] = { 0, 14, 22, 22, 14, 0 };

    lv_obj_t *eyes[10];
    cf2_rect_row(scene, 60,  116, 5, 24, 24, 24, EYE_DY,   d->accent, eyes);
    cf2_rect_row(scene, 232, 116, 5, 24, 24, 24, EYE_DY,   d->accent, eyes + 5);
    cf2_rect_row(scene, 146, 250, 6, 20, 20, 20, MOUTH_DY, d->accent, NULL);

    cf2_bob_start(eyes, 10, 2400);
}

#endif /* CF_FACE_VERSION == 2 */
