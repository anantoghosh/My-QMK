
#include QMK_KEYBOARD_H

#define BIGRAM_KEY KC_DELETE

static const uint16_t skip_bigram_pairs[][2] = {
    {KC_C, KC_F},
    {KC_F, KC_C},
    {KC_L, KC_M},
    {KC_M, KC_L},
    {KC_D, KC_V},
    {KC_V, KC_D},
    {KC_B, KC_G},
    {KC_G, KC_D},
    {KC_K, KC_Y}
    // more pairs could be specified here
};

static const uint8_t skip_bigram_pairs_length = sizeof(skip_bigram_pairs) / sizeof(skip_bigram_pairs[0]);
bool skip_bigram_mode = false;
uint8_t skip_bigrams_pair_idx = 0;

static inline bool pressed_first_bigram_key(uint16_t basic_keycode) {

    for (uint8_t i = 0; i < skip_bigram_pairs_length; i++) {

        if (basic_keycode == skip_bigram_pairs[i][0]) {
            skip_bigrams_pair_idx = i;
            return true;
        }

    }

    return false;
}

static inline bool is_ignore_letter(uint16_t basic_keycode) {
    switch (basic_keycode) {
        case KC_A:
        case KC_E:
        case KC_O:
        case KC_U:
        case KC_I:
        case KC_Y:
            return true;
        default:
            return false;
    }
}

bool process_skip_bigrams(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uint16_t basic_keycode = keycode & 0x00FF;

        if (pressed_first_bigram_key(basic_keycode)) {
            skip_bigram_mode = true;
            return true;
        }

        if (skip_bigram_mode) {

            if (is_ignore_letter(basic_keycode)) {
                return true;
            }

            if (keycode == BIGRAM_KEY) {
                tap_code16(skip_bigram_pairs[skip_bigrams_pair_idx][1]);
                return false;
            }

            skip_bigram_mode = false;

        }

    }

    return true;
}
