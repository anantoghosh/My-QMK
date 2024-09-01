// Simplify using the mod keys
#define CK_Z LGUI_T(KC_Z)
#define CK_X LSFT_T(KC_X)
#define CK_C LALT_T(KC_C)
#define CK_V LCTL_T(KC_V)

#define CK_SLASH RGUI_T(KC_SLASH)
#define CK_DOT RSFT_T(KC_DOT)
#define CK_COMMA RALT_T(KC_COMMA)
#define CK_M RCTL_T(KC_M)

// Keymap helpers
#define K_ENUM(name, key, ...) name,
#define K_DATA(name, key, ...) const uint16_t PROGMEM cmb_##name[] = {__VA_ARGS__, COMBO_END};
#define K_COMB(name, key, ...) [name] = COMBO(cmb_##name, key),

#define A_ENUM(name, string, ...) name,
#define A_DATA(name, string, ...) const uint16_t PROGMEM cmb_##name[] = {__VA_ARGS__, COMBO_END};
#define A_COMB(name, string, ...) [name] = COMBO_ACTION(cmb_##name),
#define A_ACTI(name, string, ...) case name: if (pressed) SEND_STRING_DELAY(string, 16); break;
#define BLANK(...)


// Generate data needed for combos/actions
// Create Enum
#undef  COMB
#undef  SUBS
#define COMB  K_ENUM
#define SUBS  A_ENUM
enum combos {
  #include "combos.def"
};

// Bake combos into mem
#undef  COMB
#undef  SUBS
#define COMB K_DATA
#define SUBS A_DATA
  #include "combos.def"
#undef  COMB
#undef  SUBS

// Fill combo array
#define COMB K_COMB
#define SUBS A_COMB
combo_t key_combos[] = {
  #include "combos.def"
};
#undef  COMB
#undef  SUBS

// Export length to combo module
int COMBO_LEN = sizeof(key_combos)/sizeof(key_combos[0]);

// Fill QMK hook
#define COMB BLANK
#define SUBS A_ACTI
void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    #include "combos.def"
  }
}
#undef COMB
#undef SUBS
