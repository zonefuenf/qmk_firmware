#pragma once
#include "quantum.h"

#include "process_keycode/process_tap_dance.h"

#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      k1f, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e,      \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e,      \
    k40,      k42, k43,                k47,           k4a, k4b,      k4d, k4e, k4f  \
) { \
   {k00, k01,   k02, k03, k04,   k05,   k06,   k07, k08,   k09,   k0a, k0b, k0c,   k0d, k0e,   k0f},   \
   {k10, k11,   k12, k13, k14,   k15,   k16,   k17, k18,   k19,   k1a, k1b, k1c,   k1d, KC_NO, k1f},   \
   {k20, k21,   k22, k23, k24,   k25,   k26,   k27, k28,   k29,   k2a, k2b, k2c,   k2d, k2e,   KC_NO}, \
   {k30, k31,   k32, k33, k34,   k35,   k36,   k37, k38,   k39,   k3a, k3b, k3c,   k3d, k3e,   KC_NO}, \
   {k40, KC_NO, k42, k43, KC_NO, KC_NO, KC_NO, k47, KC_NO, KC_NO, k4a, k4b, KC_NO, k4d, k4e,   k4f}    \
}

#define KEYMAP LAYOUT_all
#define LAYOUT LAYOUT_all
  
typedef struct {
  bool is_press_action;
  int state;
} xtap;

int cur_dance(qk_tap_dance_state_t *state);

void lshift_finished(qk_tap_dance_state_t *state, void *user_data);
void lshift_reset(qk_tap_dance_state_t *state, void *user_data);
void rshift_finished(qk_tap_dance_state_t *state, void *user_data);
void rshift_reset(qk_tap_dance_state_t *state, void *user_data);
void register_shift_eight(void);
void register_shift_nine(void);
void unregister_shift_eight(void);
void unregister_shift_nine(void);

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5,  // send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

// Tap dance enums
enum { XLSHIFT = 0, XRSHIFT };
