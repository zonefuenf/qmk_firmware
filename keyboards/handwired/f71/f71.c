#include "f71.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"
#include "quantum.h"

void matrix_init_kb(void) {
  // Light up LED for a second after boot up
  setPinOutput(C13);
  writePinHigh(C13);
  wait_ms(1000);
  writePinLow(C13);

  matrix_init_user();
}

/* Tap dance setup for l shift and r shift:
   Hold   = Shift
   Tap 2x = {
   Tap 3x = [
   Works for (Windows) ISO-DE keymap; adjust key codes if using a different
   keymap.

   Functions are pulled from tap dance documentation:
   https://github.com/qmk/qmk_firmware/blob/master/docs/feature_tap_dance.md
*/
int hold_cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
      return SINGLE_HOLD;
  } else if (state->count == 2) {
      return DOUBLE_TAP;
  } else if (state->count == 3) {
      return TRIPLE_TAP;
  } else
    return 8;  // magic number. At some point this method will expand to work
               // for more presses
}

void register_shift_eight(void) {
  register_code(KC_LSFT);
  register_code(KC_8);
}

void unregister_shift_eight(void) {
  unregister_code(KC_LSFT);
  unregister_code(KC_8);
}

void register_altgr_seven(void) {
  register_code(KC_RALT);
  register_code(KC_7);
}

void unregister_altgr_seven(void) {
  unregister_code(KC_RALT);
  unregister_code(KC_7);
}

void register_altgr_eight(void) {
  register_code(KC_RALT);
  register_code(KC_8);
}

void unregister_altgr_eight(void) {
  unregister_code(KC_RALT);
  unregister_code(KC_8);
}

void register_altgr_zero(void) {
  register_code(KC_RALT);
  register_code(KC_0);
}

void unregister_altgr_zero(void) {
  unregister_code(KC_RALT);
  unregister_code(KC_0);
}

void register_altgr_nine(void) {
  register_code(KC_RALT);
  register_code(KC_9);
}

void unregister_altgr_nine(void) {
  unregister_code(KC_RALT);
  unregister_code(KC_9);
}

void register_shift_nine(void) {
  register_code(KC_LSFT);
  register_code(KC_9);
}

void unregister_shift_nine(void) {
  unregister_code(KC_LSFT);
  unregister_code(KC_9);
}

static xtap lshift_tap_state = {.is_press_action = true, .state = 0};

static xtap rshift_tap_state = {.is_press_action = true, .state = 0};

void lshift_finished(qk_tap_dance_state_t *state, void *user_data) {
  lshift_tap_state.state = hold_cur_dance(state);
  switch (lshift_tap_state.state) {
    case SINGLE_HOLD:
      register_code(KC_LSFT);
      break;
    case DOUBLE_TAP:
      register_altgr_seven();
      break;
    case TRIPLE_TAP:
      register_altgr_eight();
      break;
  }
}

void lshift_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (lshift_tap_state.state) {
    case SINGLE_HOLD:
      unregister_code(KC_LSFT);
      break;
    case DOUBLE_TAP:
      unregister_altgr_seven();
      break;
    case TRIPLE_TAP:
      unregister_altgr_eight();
  }
  lshift_tap_state.state = 0;
}

void rshift_finished(qk_tap_dance_state_t *state, void *user_data) {
  rshift_tap_state.state = hold_cur_dance(state);
  switch (rshift_tap_state.state) {
    case SINGLE_HOLD:
      register_code(KC_RSFT);
      break;
    case DOUBLE_TAP:
      register_altgr_zero();
      break;
    case TRIPLE_TAP:
      register_altgr_nine();
      break;
  }
}

void rshift_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (rshift_tap_state.state) {
    case SINGLE_HOLD:
      unregister_code(KC_RSFT);
      break;
    case DOUBLE_TAP:
      unregister_altgr_zero();
      break;
    case TRIPLE_TAP:
      unregister_altgr_nine();
  }
  rshift_tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [XLSHIFT] =
        ACTION_TAP_DANCE_FN_ADVANCED(NULL, lshift_finished, lshift_reset),
    [XRSHIFT] =
        ACTION_TAP_DANCE_FN_ADVANCED(NULL, rshift_finished, rshift_reset)};
