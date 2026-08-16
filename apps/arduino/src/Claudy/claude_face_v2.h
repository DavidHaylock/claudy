/**
 * @file claude_face_v2.h
 * Claude CLI status faces — 412x412 round LCD (ESP32 + LVGL)
 *
 * 1:1 port of the "Claude Status Faces v2" design (designs/Claude Status
 * Faces v2.dc.html). Same public API as v1 (claude_face.h) so Claudy.ino
 * and the hook script's state keys don't need to change -- see
 * claude_face_config.h for how the two ports coexist in one build.
 * Works on LVGL 8.3+ and 9.x.
 */
#ifndef CLAUDE_FACE_V2_H
#define CLAUDE_FACE_V2_H

#include "claude_face_config.h"
#if CF_FACE_VERSION == 2

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

/*--------------------------------------------------------------------------
 * States — one per Claude Code hook event
 *
 * Numeric order kept identical to v1 for stability (claude_face_next() /
 * claude_face_cycle() order); the hook script only ever uses the string
 * keys via claude_face_from_key(), which is order-independent.
 *------------------------------------------------------------------------*/

typedef enum {
    CF_STATE_START = 0,   /* SessionStart               BOOTING    */
    CF_STATE_ATTENTION,   /* Notification (permission)  YOUR TURN  */
    CF_STATE_IDLE,        /* idle_prompt                IDLE       */
    CF_STATE_DONE,        /* Stop                       DONE       */
    CF_STATE_FAIL,        /* PostToolUseFailure         FAILED     */
    CF_STATE_DANGER,      /* PreToolUse (rm / push)     DANGER     */
    CF_STATE_RATELIMIT,   /* StopFailure (rate_limit)   RATE LIMIT */
    CF_STATE_SUBAGENT,    /* SubagentStop               SUBAGENT   */
    CF_STATE_END,         /* SessionEnd                 SIGNING OFF*/
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

/** Show/hide the small detail line under the state word. */
void        claude_face_set_hint_visible(bool en);

/** Show/hide the small hook-event caption at the top of the disc
 *  (e.g. "PERMISSION_PROMPT"). v2-only; mirrors CF2_SHOW_HOOK_LABELS. */
void        claude_face_set_hook_label_visible(bool en);

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

#endif /* CF_FACE_VERSION == 2 */
#endif /* CLAUDE_FACE_V2_H */
