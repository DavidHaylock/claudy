/**
 * @file claude_face.h
 * Claude CLI status faces — 412x412 round LCD (ESP32 + LVGL)
 *
 * 1:1 port of the "Claude CLI status faces / 1a" design.
 * Works on LVGL 8.3+ and 9.x.
 */
#ifndef CLAUDE_FACE_H
#define CLAUDE_FACE_H

#include "claude_face_config.h"
#if CF_FACE_VERSION == 1

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

/*--------------------------------------------------------------------------
 * Configuration
 *------------------------------------------------------------------------*/

/** Physical panel size. The design is authored at 412x412. */
#ifndef CF_DISPLAY_SIZE
#define CF_DISPLAY_SIZE 412
#endif

/** Set to 1 once you add silkscreen_34.cpp / silkscreen_13.cpp to the build. */
#ifndef CF_USE_SILKSCREEN_FONTS
#define CF_USE_SILKSCREEN_FONTS 1
#endif

/** Set to 0 to temporarily disable the pulsing halo ring. */
#ifndef CF_ENABLE_PULSE_HALO
#define CF_ENABLE_PULSE_HALO 0
#endif

/*--------------------------------------------------------------------------
 * States — one per Claude Code hook event
 *------------------------------------------------------------------------*/

typedef enum {
    CF_STATE_START = 0,   /* SessionStart               HELLO     */
    CF_STATE_ATTENTION,   /* Notification (permission)  ALLOW?    */
    CF_STATE_IDLE,        /* idle_prompt                YOUR TURN */
    CF_STATE_DONE,        /* Stop                       DONE      */
    CF_STATE_FAIL,        /* PostToolUseFailure         TOOL FAIL */
    CF_STATE_DANGER,      /* PreToolUse (rm / push)     DANGER    */
    CF_STATE_RATELIMIT,   /* StopFailure (rate_limit)   THROTTLED */
    CF_STATE_SUBAGENT,    /* SubagentStop               SUBAGENT  */
    CF_STATE_END,         /* SessionEnd                 BYE       */
    CF_STATE_COUNT
} cf_state_t;

/*--------------------------------------------------------------------------
 * API
 *------------------------------------------------------------------------*/

/** Build the face on `parent` (pass NULL for the active screen). */
lv_obj_t   *claude_face_create(lv_obj_t *parent);

/** Tear everything down (timers + animations included). */
void        claude_face_destroy(void);

/** Switch state. Rebuilds the face shape and restarts its animations. */
void        claude_face_set_state(cf_state_t s);
cf_state_t  claude_face_get_state(void);

/** Advance to the next state (wraps). */
void        claude_face_next(void);

/** Show/hide the small hint line under the label. */
void        claude_face_set_hint_visible(bool en);

/** Auto-cycle through all states every 2200 ms, as in the design demo. */
void        claude_face_cycle(bool en);

/** Root object, or NULL if not created yet. */
lv_obj_t   *claude_face_root(void);

/** Map to/from the string keys used by the hook script.
 *  "start" "attention" "idle" "done" "fail" "danger" "ratelimit"
 *  "subagent" "end"  — returns CF_STATE_IDLE for an unknown key. */
const char *claude_face_key(cf_state_t s);
cf_state_t  claude_face_from_key(const char *key);

/** Design metadata, handy for a serial banner or a secondary screen. */
const char *claude_face_label(cf_state_t s);
const char *claude_face_hint(cf_state_t s);
const char *claude_face_trigger(cf_state_t s);
lv_color_t  claude_face_color(cf_state_t s);

#ifdef __cplusplus
}
#endif

#endif /* CF_FACE_VERSION == 1 */
#endif /* CLAUDE_FACE_H */
