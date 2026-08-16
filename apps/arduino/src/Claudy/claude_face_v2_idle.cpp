/**
 * @file claude_face_v2_idle.cpp
 * Claude Status Faces v2 — IDLE (Notification / idle_prompt)
 *
 * Geometry from designs/Claude Status Faces v2.dc.html:84-123 /
 * claude_face_v2_PLAN.md section 2, absolute px on the 412x412 canvas.
 *
 * Brows + eyes bob unconditionally (the design's `animation:bob` wrapper
 * around them has no `lively` guard); the two sleepy "z"s are the only
 * lively-gated element, per claude_face_v2_PLAN.md's D4. The mouth is
 * static in both the design and here.
 */

#include "claude_face_v2_faces.h"

#if CF_FACE_VERSION == 2

/* Declared locally rather than routed through claude_face_v2.cpp's private
 * CF2_FONT_* macros -- each face builder only depends on the shared
 * cf2_*() contract in claude_face_v2_faces.h, never on another builder's
 * or the chrome file's internals. LV_FONT_DECLARE is just an `extern`, so
 * redeclaring it here is safe and standard. */
LV_FONT_DECLARE(silkscreen_20)
LV_FONT_DECLARE(silkscreen_13)

#define IDLE_BROW_COL 0x386CA0u
#define IDLE_ZZZ_COL  0x6CBDFFu

void build_idle(lv_obj_t *scene, const cf2_def_t *d)
{
    /* brows + eyes -- these 6 bob together */
    lv_obj_t *bobbers[6];
    bobbers[0] = cf2_rect(scene, 82,  128, 32, 12, IDLE_BROW_COL);  /* brow L outer */
    bobbers[1] = cf2_rect(scene, 114, 136, 64, 12, IDLE_BROW_COL);  /* brow L inner */
    bobbers[2] = cf2_rect(scene, 82,  170, 96, 18, d->accent);      /* eye L        */
    bobbers[3] = cf2_rect(scene, 234, 136, 64, 12, IDLE_BROW_COL);  /* brow R inner */
    bobbers[4] = cf2_rect(scene, 298, 128, 32, 12, IDLE_BROW_COL);  /* brow R outer */
    bobbers[5] = cf2_rect(scene, 234, 170, 96, 18, d->accent);      /* eye R        */
    cf2_bob_start(bobbers, 6, 5000);

    /* mouth -- static */
    cf2_rect(scene, 180, 258, 52, 14, d->accent);

#if CF2_LIVELY
    /* Silkscreen 22px/16px aren't vendored; substituting 20/13 per
     * claude_face_v2_PLAN.md. z-small's y is 82 + silkscreen_20's real
     * line_height (24) + the design's 6px column gap. */
    lv_obj_t *z_big   = cf2_text(scene, 296, 82,    &silkscreen_20, IDLE_ZZZ_COL, "z");
    lv_obj_t *z_small = cf2_text(scene, 296, 82+24+6, &silkscreen_13, IDLE_ZZZ_COL, "z");
    cf2_zzz_start(z_big,   2400, 0);
    cf2_zzz_start(z_small, 2400, 800);
#endif
}

#endif /* CF_FACE_VERSION == 2 */
