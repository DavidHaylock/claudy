/**
 * @file claude_face_config.h
 * Picks which face design is compiled into the firmware.
 *
 * claude_face.cpp/.h (v1) and claude_face_v2.cpp/.h (v2) export the same
 * public API (claude_face_create, claude_face_set_state, ...). Both are
 * wrapped whole-file in `#if CF_FACE_VERSION == N`, so exactly one of them
 * supplies those symbols -- compiling both in with the same version picked
 * would either link-fail (duplicate symbols) or silently do nothing
 * (neither guard matches). Set the macro below and nothing else needs to
 * change: Claudy.ino, claude_face_from_key(), and the hook script's state
 * keys are identical across versions.
 */
#ifndef CLAUDE_FACE_CONFIG_H
#define CLAUDE_FACE_CONFIG_H

/** 1 = "Claude Status Screens standalone v1", 2 = "Claude Status Faces v2". */
#ifndef CF_FACE_VERSION
#define CF_FACE_VERSION 2
#endif

/*--------------------------------------------------------------------------
 * v2-only knobs (ignored when CF_FACE_VERSION == 1)
 *------------------------------------------------------------------------*/

/** Bezel decorations: start's sweep bar, idle's zzz, attention's breathing
 *  ring, ratelimit's gauge, danger's dashed ring. Set 0 if these cost too
 *  much CPU/flicker on hardware -- each face still shows its static shape. */
#ifndef CF2_LIVELY
#define CF2_LIVELY 1
#endif

/** Small event-name caption at the top of the disc (e.g. "PERMISSION_PROMPT"). */
#ifndef CF2_SHOW_HOOK_LABELS
#define CF2_SHOW_HOOK_LABELS 1
#endif

/** 1 = use the vendored Silkscreen/IBM Plex Mono bitmap fonts this design
 *  calls for. 0 = fall back to LVGL's built-in fonts (no extra assets
 *  needed, but sizes/letter-spacing won't match the design). */
#ifndef CF2_USE_DESIGN_FONTS
#define CF2_USE_DESIGN_FONTS 1
#endif

#endif /* CLAUDE_FACE_CONFIG_H */
