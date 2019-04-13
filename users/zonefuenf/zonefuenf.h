#ifndef ZONEFUENF
#define ZONEFUENF

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

typedef struct {
  bool is_press_action;
  int state;
} xtap;

int cur_dance (qk_tap_dance_state_t *state);

void lshift_finished (qk_tap_dance_state_t *state, void *user_data);
void lshift_reset (qk_tap_dance_state_t *state, void *user_data);
void rshift_finished (qk_tap_dance_state_t *state, void *user_data);
void rshift_reset (qk_tap_dance_state_t *state, void *user_data);
void register_shift_eight (void);
void register_shift_nine (void);
void unregister_shift_eight (void);
void unregister_shift_nine (void);

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
  XLSHIFT = 0,
  XRSHIFT
};

#endif
