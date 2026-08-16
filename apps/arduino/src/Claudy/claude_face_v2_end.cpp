/**
 * @file claude_face_v2_end.cpp
 * Claude Status Faces v2 — END (SessionEnd, word "SIGNING OFF")
 *
 * Geometry from designs/Claude Status Faces v2.dc.html:360-387 /
 * claude_face_v2_PLAN.md section 9, absolute px on the 412x412 canvas.
 *
 * Two eye bars and a three-dot mouth, all five rects fading together
 * (`fadeout`, 4s alternate -> modelled as one 8s round-trip cycle, see
 * cf2_fadeout_start()). Unlike start/idle/attention/danger's decorations,
 * the source HTML doesn't gate this behind `lively` -- it always runs.
 */

#include "claude_face_v2_faces.h"

#if CF_FACE_VERSION == 2

void build_end(lv_obj_t *scene, const cf2_def_t *d)
{
    static const int8_t MOUTH_DY[3] = { 0, 0, 0 };

    lv_obj_t *bars[5];
    bars[0] = cf2_rect(scene, 82,  140, 96, 16, d->accent);   /* eye bar L */
    bars[1] = cf2_rect(scene, 234, 140, 96, 16, d->accent);   /* eye bar R */
    cf2_rect_row(scene, 179, 252, 3, 18, 18, 18, MOUTH_DY, d->accent, bars + 2);

    cf2_fadeout_start(bars, 5, 8000);
}

#endif /* CF_FACE_VERSION == 2 */
