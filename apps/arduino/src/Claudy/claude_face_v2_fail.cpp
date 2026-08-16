/**
 * @file claude_face_v2_fail.cpp
 * Claude Status Faces v2 — FAIL (PostToolUseFailure, word "FAILED")
 *
 * Geometry from designs/Claude Status Faces v2.dc.html:235-267 /
 * claude_face_v2_PLAN.md section 6, absolute px on the 412x412 canvas.
 *
 * Eyes: two 3x3 grids of 30x30 cells (pitch 33 -- 30 + 3 gap), five cells
 * filled per grid forming an X (corners + centre). Grid cells shake
 * together (`shake`, 3s); the mouth (a static frown of six 20x20 squares)
 * doesn't move, matching the source HTML where only the grids sit inside
 * the `animation:shake` wrapper.
 */

#include "claude_face_v2_faces.h"

#if CF_FACE_VERSION == 2

void build_fail(lv_obj_t *scene, const cf2_def_t *d)
{
    /* local origins {0,33,66} on both axes; X pattern = 4 corners + centre */
    static const int8_t GRID_X[5]   = { 0, 66, 33, 0, 66 };
    static const int8_t GRID_Y[5]   = { 0, 0, 33, 66, 66 };
    static const int8_t MOUTH_DY[6] = { 22, 12, 0, 0, 12, 22 };

    lv_obj_t *grid[10];
    for(int i = 0; i < 5; i++)
        grid[i]     = cf2_rect(scene, 84  + GRID_X[i], 112 + GRID_Y[i], 30, 30, d->accent);
    for(int i = 0; i < 5; i++)
        grid[5 + i] = cf2_rect(scene, 232 + GRID_X[i], 112 + GRID_Y[i], 30, 30, d->accent);

    cf2_rect_row(scene, 146, 248, 6, 20, 20, 20, MOUTH_DY, d->accent, NULL);

    cf2_shake_start(grid, 10, 3000);
}

#endif /* CF_FACE_VERSION == 2 */
