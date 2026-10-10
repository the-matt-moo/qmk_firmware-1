/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#undef DEBOUNCE
#define DEBOUNCE 5

//#undef ONESHOT_TIMEOUT
//#define ONESHOT_TIMEOUT 3500

#define AUTO_SHIFT_TIMEOUT 150
/*
#define NO_AUTO_SHIFT_TAB
#define NO_AUTO_SHIFT_SPECIAL/
*/
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_NO_AUTO_REPEAT
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#undef RGBLIGHT_SLEEP
#define RGBLIGHT_SLEEP
#define TAPPING_TERM_PER_KEY
