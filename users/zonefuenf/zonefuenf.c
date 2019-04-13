#include QMK_KEYBOARD_H

#include "zonefuenf.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

int hold_cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted) {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (!state->pressed) return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

void register_shift_eight (void) {
  register_code (KC_LSFT);
  register_code (KC_8);
}

void unregister_shift_eight (void) {
  unregister_code (KC_LSFT);
  unregister_code (KC_8);
}

void register_altgr_seven (void) {
  register_code (KC_RALT);
  register_code (KC_7);
}

void unregister_altgr_seven (void) {
  unregister_code (KC_RALT);
  unregister_code (KC_7);
}

void register_altgr_eight (void) {
  register_code (KC_RALT);
  register_code (KC_8);
}

void unregister_altgr_eight (void) {
  unregister_code (KC_RALT);
  unregister_code (KC_8);
}

void register_altgr_zero (void) {
  register_code (KC_RALT);
  register_code (KC_0);
}

void unregister_altgr_zero (void) {
  unregister_code (KC_RALT);
  unregister_code (KC_0);
}

void register_altgr_nine (void) {
  register_code (KC_RALT);
  register_code (KC_9);
}

void unregister_altgr_nine (void) {
  unregister_code (KC_RALT);
  unregister_code (KC_9);
}

void register_shift_nine (void) {
  register_code (KC_LSFT);
  register_code (KC_9);
}

void unregister_shift_nine (void) {
  unregister_code (KC_LSFT);
  unregister_code (KC_9);
}

static xtap lshift_tap_state = {
  .is_press_action = true,
  .state = 0
};

static xtap rshift_tap_state = {
  .is_press_action = true,
  .state = 0
};

void lshift_finished (qk_tap_dance_state_t *state, void *user_data) {
  lshift_tap_state.state = hold_cur_dance(state);
  switch (lshift_tap_state.state) {
    case SINGLE_TAP: register_shift_eight(); break;
    case SINGLE_HOLD: register_code(KC_LSFT); break;
    case DOUBLE_TAP: register_altgr_seven(); break;
    case TRIPLE_TAP: register_altgr_eight(); break;
  }
}

void lshift_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (lshift_tap_state.state) {
    case SINGLE_TAP: unregister_shift_eight(); break;
    case SINGLE_HOLD: unregister_code(KC_LSFT); break;
    case DOUBLE_TAP: unregister_altgr_seven(); break;
    case TRIPLE_TAP: unregister_altgr_eight();
  }
  lshift_tap_state.state = 0;
}

void rshift_finished (qk_tap_dance_state_t *state, void *user_data) {
  rshift_tap_state.state = hold_cur_dance(state);
  switch (rshift_tap_state.state) {
    case SINGLE_TAP: register_shift_nine(); break;
    case SINGLE_HOLD: register_code(KC_RSFT); break;
    case DOUBLE_TAP: register_altgr_zero(); break;
    case TRIPLE_TAP: register_altgr_nine(); break;
  }
}

void rshift_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (rshift_tap_state.state) {
    case SINGLE_TAP: unregister_shift_nine(); break;
    case SINGLE_HOLD: unregister_code(KC_RSFT); break;
    case DOUBLE_TAP: unregister_altgr_zero(); break;
    case TRIPLE_TAP: unregister_altgr_nine();
  }
  rshift_tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [XLSHIFT]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lshift_finished, lshift_reset),
  [XRSHIFT]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rshift_finished, rshift_reset)
};

