
#include QMK_KEYBOARD_H

#define BIGRAM_KEY KC_DELETE
#define MAX_LAST_KEYS 3
static uint16_t last_keys[MAX_LAST_KEYS] = {KC_NO, KC_NO, KC_NO};
static uint8_t last_key_idx = 0;
static const uint16_t skip_bigram_pairs[][2] = {
    {KC_C, KC_F},
    {KC_F, KC_C},
    {KC_L, KC_M},
    {KC_M, KC_L},
    {KC_D, KC_V},
    {KC_V, KC_D},
    {KC_B, KC_G},
    {KC_G, KC_D},
    // more pairs could be specified here
};
static const uint8_t num_skip_bigram_pairs = sizeof(skip_bigram_pairs) / sizeof(skip_bigram_pairs[0]);

bool process_skip_bigrams(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {
        uint16_t basic_keycode = keycode & 0x00FF;

        last_key_idx = (last_key_idx + 1) % MAX_LAST_KEYS;
        last_keys[last_key_idx] = basic_keycode;

        if (keycode == BIGRAM_KEY) {
            uint8_t idx = (last_key_idx + MAX_LAST_KEYS - 2) % MAX_LAST_KEYS;
            for (uint8_t i = 0; i < num_skip_bigram_pairs; i++) {
                if (last_keys[idx] == skip_bigram_pairs[i][0]) {
                    keycode = skip_bigram_pairs[i][1];
                    tap_code16(keycode);
                    return false;
                }
            }
        }

    }

    return true;
}
