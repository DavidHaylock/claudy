/**
 * @file claude_face_v2_subagent.cpp
 * Claude Status Faces v2 — SUBAGENT (SubagentStop)
 *
 * Geometry from designs/Claude Status Faces v2.dc.html:321-358 /
 * claude_face_v2_PLAN.md section 8, absolute px on the 412x412 canvas.
 *
 * Eyes: two 2x2 checkerboards, 44px cells + 8px gap. CSS grid auto-places
 * row-major (TL, TR, BL, BR); TL+BR are the light colour, TR+BL the dark
 * one. All 8 cells bob together (`bob`, 2.8s) and (design spec) blink
 * together as one `steps(1,end)` group, the two eyes 250ms (62 permille of
 * 4000ms) out of phase -- see cf2_blink2_start()'s per-object phase array.
 * The blink2 call is temporarily commented out below; re-enable it to
 * restore that. The 5-rect mouth is static, matching the source HTML where
 * only the two eye grids sit inside the `animation:bob` wrapper.
 */

#include "claude_face_v2_faces.h"

#if CF_FACE_VERSION == 2

#define SUBAGENT_DARK_COL 0x188489u

void build_subagent(lv_obj_t *scene, const cf2_def_t *d)
{
    lv_obj_t *cells[8];
    /* left eye, origin (84,112), cell pitch 52 (44 + 8 gap) */
    cells[0] = cf2_rect(scene, 84,  112, 44, 44, d->accent);           /* TL light */
    cells[1] = cf2_rect(scene, 136, 112, 44, 44, SUBAGENT_DARK_COL);   /* TR dark  */
    cells[2] = cf2_rect(scene, 84,  164, 44, 44, SUBAGENT_DARK_COL);   /* BL dark  */
    cells[3] = cf2_rect(scene, 136, 164, 44, 44, d->accent);           /* BR light */
    /* right eye, origin (232,112) */
    cells[4] = cf2_rect(scene, 232, 112, 44, 44, d->accent);           /* TL light */
    cells[5] = cf2_rect(scene, 284, 112, 44, 44, SUBAGENT_DARK_COL);   /* TR dark  */
    cells[6] = cf2_rect(scene, 232, 164, 44, 44, SUBAGENT_DARK_COL);   /* BL dark  */
    cells[7] = cf2_rect(scene, 284, 164, 44, 44, d->accent);           /* BR light */

    cf2_bob_start(cells, 8, 2800);

    /* blink2 temporarily disabled -- re-enable by uncommenting.
    static const uint16_t BLINK_PHASE[8] = { 0, 0, 0, 0, 62, 62, 62, 62 };
    cf2_blink2_start(cells, BLINK_PHASE, 8, 4000);
    */

    static const int8_t MOUTH_DY[5] = { 0, 12, 16, 12, 0 };
    cf2_rect_row(scene, 156, 254, 5, 20, 20, 20, MOUTH_DY, d->accent, NULL);
}

#endif /* CF_FACE_VERSION == 2 */
