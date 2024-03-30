
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

static const uint8_t num_skip_bigram_pairs = sizeof(skip_bigram_pairs) / sizeof(skip_bigram_pairs[0]);

bool skip_bigrams_mode = false;
uint8_t skip_bigrams_pair_idx = 0;

bool process_skip_bigrams(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {
        uint16_t basic_keycode = keycode & 0x00FF;

        for (uint8_t i = 0; i < num_skip_bigram_pairs; i++) {
            if (basic_keycode == skip_bigram_pairs[i][0]) {
                skip_bigrams_pair_idx = i;
                skip_bigrams_mode = true;
                return true;
            }
        }

        if (skip_bigrams_mode) {
            if (basic_keycode == KC_A || basic_keycode == KC_E || basic_keycode == KC_O || basic_keycode == KC_U || basic_keycode == KC_I || basic_keycode == KC_Y) {
                return true;
            } else if (keycode == BIGRAM_KEY) {
                tap_code16(skip_bigram_pairs[skip_bigrams_pair_idx][1]);
                return false;
            } else {
                skip_bigrams_mode = false;
            }
        }

    }

    return true;
}
