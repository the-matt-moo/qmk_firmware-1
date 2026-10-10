/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#undef DEBOUNCE
#define DEBOUNCE 3

#undef ONESHOT_TIMEOUT
#define ONESHOT_TIMEOUT 3500

#define AUTO_SHIFT_TIMEOUT 175
/*
#define NO_AUTO_SHIFT_TAB
#define NO_AUTO_SHIFT_SPECIAL
*/
#define NO_AUTO_SHIFT_ALPHA

#define AUTO_SHIFT_NO_AUTO_REPEAT
#define TAPPING_TERM 250

#define PERMISSIVE_HOLD
#define RGBLIGHT_SLEEP 300
