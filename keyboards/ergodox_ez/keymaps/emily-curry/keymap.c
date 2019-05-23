#include "ergodox_ez.h"
#include "version.h"

// Just here to squash red squiggles
#ifdef EMILY_EDITOR
    #include "../../config.h"
    #include "./config.h"
    #include "rgb_matrix.h"
#endif

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)

rgb_config_t rgb_matrix_config;

enum custom_layers {
    BASE = 0, // default layer
    SYMB, // symbols
    MDIA, // media keys
    GAME, // game base
    GME2 // game alt
};

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE, // can always be here
    EPRM,
    RGB_SLD_TGL,
    GAY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  |  Esc |           | PrtSc|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   F  |   P  |   G  |  F12 |           | F5   |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |   O  |   '    |
 * |--------+------+------+------+------+------|  Del |           | Ins  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |   ,  |   .  |  /   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl |'"/Alt|  `~  | Left | Right|                                       |  Up  | Down |   [  |   ]  | RCtl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Home | End  |       |PgDown| PgUp |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Win  |       | Esc  |      |      |
 *                                 | Spc  | Bkspc|------|       |------| Tab  |Enter |
 *                                 |      |      | SYMB |       | Alt  |      |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_EQL,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_ESC,
        KC_TAB,     KC_Q,       KC_W,       KC_F,       KC_P,       KC_G,       KC_F12,
        KC_BSPC,    KC_A,       KC_R,       KC_S,       KC_T,       KC_D,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_DELT,
        KC_LCTL,    LALT_T(KC_QUOT),KC_GRV, KC_LEFT,    KC_RGHT,
                                                                    KC_HOME,    KC_END,
                                                                                KC_LGUI,
                                                        KC_SPC,     KC_BSPC,    MO(SYMB),
        // right hand
        KC_PSCREEN, KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,
        KC_F5,      KC_J,       KC_L,       KC_U,       KC_Y,       KC_SCLN,    KC_BSLS,
                    KC_H,       KC_N,       KC_E,       KC_I,       KC_O,       KC_QUOT,
        KC_INS,     KC_K,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
                                KC_UP,      KC_DOWN,    KC_LBRC,    KC_RBRC,    KC_RCTL,
        KC_PGDN,    KC_PGUP,
        KC_ESC,
        KC_LALT,    KC_TAB,     KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | RGBTGL |  F1  |  F2  |  F3  |  F4  |  F5  |      |           | GAME |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | RGBVAI |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   /  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | RGBVAD |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   *  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   -  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   +  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
        // left hand
        RGB_SLD_TGL,KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_TRNS,
        RGB_VAI,    KC_EXLM,    KC_AT,      KC_LCBR,    KC_RCBR,    KC_PIPE,    KC_TRNS,
        RGB_VAD,    KC_HASH,    KC_DLR,     KC_LPRN,    KC_RPRN,    KC_GRV,
        KC_TRNS,    KC_PERC,    KC_CIRC,    KC_LBRC,    KC_RBRC,    KC_TILD,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                                    KC_TRNS,    KC_TRNS,
                                                                                KC_TRNS,
                                                        KC_TRNS,    KC_TRNS,    KC_TRNS,
        // right hand
        TO(GAME),   KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,
        KC_TRNS,    KC_UP,      KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_PSLS,    KC_F12,
                    KC_DOWN,    KC_KP_4,    KC_KP_5,    KC_KP_6,    KC_PAST,    KC_TRNS,
        KC_TRNS,    KC_AMPR,    KC_KP_1,    KC_KP_2,    KC_KP_3,    KC_PMNS,    KC_TRNS,
                                KC_TRNS,    KC_PDOT,    KC_0,       KC_PPLS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
/* Keymap 3: Game
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      | GME2 |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[GAME] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, MO(GME2),
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_OPER,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 4: Game Ctrl Mods
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        | Ctl1 | Ctl2 | Ctl3 | Ctl4 | Ctl5 |      |           | BASE | Ctl6 | Ctl7 | Ctl8 | Ctl9 | Ctl0 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | CtlQ | CtlW |      | CtlF | CtlP |CtlF12|           | CtlF5|  F1  |  F2  |  F3  |  F4  | F10  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | CtlA |      |      |      | CtlD |------|           |------|  F5  |  F6  |  F7  |  F8  | F11  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | CtlZ | CtlX | CtlC | CtlV | CtlB |      |           |      |  F9  |      |      |      | F12  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      | Ctl' | Ctl` |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[GME2] = LAYOUT_ergodox(
       KC_TRNS, LCTL(KC_1), LCTL(KC_2), LCTL(KC_3), LCTL(KC_4), LCTL(KC_5), KC_TRNS,
       KC_TRNS, LCTL(KC_Q), LCTL(KC_W), KC_TRNS,    LCTL(KC_P), LCTL(KC_G), LCTL(KC_F12),
       KC_TRNS, LCTL(KC_A), KC_TRNS,    KC_TRNS,    KC_TRNS,    LCTL(KC_D),
       KC_TRNS, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_B), KC_TRNS,
       KC_TRNS, LCTL(KC_QUOT),LCTL(KC_GRV),KC_TRNS, KC_TRNS,
                                                                KC_TRNS,    KC_TRNS,
                                                                            KC_TRNS,
                                                    KC_TRNS,    KC_TRNS,    KC_TRNS,
    // right hand
       TO(BASE),    LCTL(KC_6),   LCTL(KC_7), LCTL(KC_8), LCTL(KC_9), LCTL(KC_0), KC_TRNS,
       LCTL(KC_F5), KC_F1,        KC_F12,     KC_F3,      KC_F4,      KC_F10,   KC_TRNS,
                    KC_F5,        KC_F6,      KC_F7,      KC_F8,      KC_F11,   KC_TRNS,
       KC_TRNS,     KC_F9,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_F12,   KC_TRNS,
                                  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

/**
 * Illuminates all the leds of a layer with the same color, hsv format.
 * Contains data for the hue and saturation only, since value (aka brightness)
 * will be overriden with the value from the eeprom to take into account the user's brightness settings
 */
const uint8_t PROGMEM layercolors[][2] = {
    [BASE] = {240,100} // Currently unused
};

/**
 * Illuminate individual keys on a layer, defined per-layer, hsv format.
 * Value (last index) is also ignored here unless 0 (then that key appears off).
 */
const uint8_t PROGMEM ledcolors[][DRIVER_LED_TOTAL][3] = {
    [BASE] = {
        // right side
        {240,70,255},   {240,70,255},   {240,70,255},   {240,70,255},   {240,70,255},
        {240,90,255},   {240,90,255},   {240,90,255},   {240,90,255},   {240,90,255},
        {240,110,255},  {240,110,255},  {240,110,255},  {240,110,255},  {240,110,255},
        {240,90,255},   {240,90,255},   {240,90,255},   {240,90,255},   {240,90,255},
                        {240,70,255},   {240,70,255},   {240,70,255},   {240,70,255},

        // left side (mirrored)
        {240,70,255},   {240,70,255},   {240,70,255},   {240,70,255},   {240,70,255},
        {240,90,255},   {240,90,255},   {240,90,255},   {240,90,255},   {240,90,255},
        {240,110,255},  {240,110,255},  {240,110,255},  {240,110,255},  {240,110,255},
        {240,90,255},   {240,90,255},   {240,90,255},   {240,90,255},   {240,90,255},
                        {240,70,255},   {240,70,255},   {240,70,255},   {240,70,255}
    },
    [SYMB] = {
        // right side
        {98,70,255},   {98,70,255},   {98,70,255},   {98,70,255},   {98,70,255},
        {98,70,255},   {98,180,255},  {98,180,255},  {98,180,255},  {98,70,255},
        {98,70,255},   {98,180,255},  {98,180,255},  {98,180,255},  {98,70,255},
        {98,70,255},   {98,180,255},  {98,180,255},  {98,180,255},  {98,70,255},
                        {98,70,255},   {98,70,255},   {98,180,255},  {98,70,255},

        // left side (mirrored)
        {150,90,255},   {150,140,255},   {150,140,255},   {150,90,255},   {150,90,255},
        {150,140,255},   {150,180,255},   {150,180,255},  {150,140,255},  {150,90,255},
        {150,140,255},   {150,180,255},   {150,180,255},  {150,140,255},  {150,90,255},
        {150,140,255},   {150,180,255},   {150,180,255},  {150,140,255},  {150,90,255},
                        {150,140,255},   {150,140,255},   {150,90,255},   {150,90,255}
    },
    [GAME] = {
        // right side
        {42,153,1},   {42,153,1},   {42,153,1},   {42,153,1},   {42,153,1},
        {240,70,1},   {240,70,1},   {240,70,1},   {240,70,1},   {240,70,1},
        {240,70,1},  {240,70,1},  {240,70,1},  {240,70,1},  {240,70,1},
        {240,70,1},   {240,70,1},   {240,70,1},   {240,70,1},   {240,70,1},
                        {240,50,1},   {240,50,1},   {240,50,1},   {240,50,1},

        // left side (mirrored)
        {42,153,1},   {42,153,1},   {42,153,1},   {42,153,1},   {42,153,1},
        {240,70,1},   {240,70,1},   {98,180,1},   {240,70,1},   {240,70,1},
        {240,70,1},  {98,180,1},  {98,180,1},  {98,180,1},  {240,70,1},
        {240,70,1},   {240,70,1},   {240,70,1},   {240,70,1},   {240,70,1},
                        {240,50,1},   {240,50,1},   {240,50,1},   {240,50,1},
    },
    [GME2] = {
        // right side
        {42,153,1},   {42,153,1},   {42,153,1},   {42,153,1},   {42,153,1},
        {98,180,1},   {130,153,1},   {130,153,1},   {130,153,1},   {30,180,1},
        {130,153,1},  {130,153,1},  {130,153,1},  {130,153,1},  {240,120,1},
        {98,180,1},   {240,70,1},   {240,70,1},   {240,70,1},   {183,140,1},
                        {240,50,1},   {240,50,1},   {240,50,1},   {240,50,1},

        // left side (mirrored)
        {42,153,1},   {42,153,1},   {42,153,1},   {42,153,1},   {42,153,1},
        {240,70,1},   {240,70,1},   {98,180,1},   {240,70,1},   {240,70,1},
        {240,70,1},  {98,180,1},  {98,180,1},  {98,180,1},  {240,70,1},
        {240,70,1},   {240,70,1},   {240,70,1},   {240,70,1},   {240,70,1},
                        {240,50,1},   {240,50,1},   {240,50,1},   {240,50,1},
    },
};


/**
 * Executed just one time when the keyboard initializes.
 */
void matrix_init_user(void) {
    rgb_matrix_config.raw = eeprom_read_dword(EECONFIG_RGB_MATRIX);
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
}

void set_layer_color( uint8_t layer ) {
  HSV hsv = { .h = pgm_read_byte(&layercolors[layer][0]), .s = pgm_read_byte(&layercolors[layer][1]), .v = rgb_matrix_config.val};
  RGB rgb = hsv_to_rgb( hsv );
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
  }
}

void set_leds_color( int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    uint8_t val = pgm_read_byte(&ledcolors[layer][i][2]);
    // if the brightness of the led is set to 0 in the map,
    // the value is not overriden with global controls, allowing the led
    // to appear turned off
    HSV hsv = { .h = pgm_read_byte(&ledcolors[layer][i][0]), .s = pgm_read_byte(&ledcolors[layer][i][1]), .v = val == 0 ? 0 : rgb_matrix_config.val};
    RGB rgb = hsv_to_rgb( hsv );
    rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
  }
}

/**
 * Executes on layer change, when it is appropriate to modify the LED matrix.
 */
void rgb_matrix_indicators_user(void) {
  uint32_t mode = rgblight_get_mode();
  // assign colors if the matrix is on and the current mode
  // is SOLID COLORS => No animations running
  if(rgb_matrix_config.enable == 1 && mode == 1) {
    uint8_t layer = biton32(layer_state);
    switch (layer) {
      case BASE:
        set_leds_color(BASE);
        break;
      case SYMB:
        set_leds_color(SYMB);
        break;
      case GAME:
        set_leds_color(GAME);
        break;
      case GME2:
        set_leds_color(GME2);
        break;
    }
  }
}

/**
 * Executed on keypress.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case RGB_SLD_TGL:
      if (record->event.pressed) {
#ifdef RGB_MATRIX_ENABLE
        rgblight_mode(1);
        rgblight_toggle();
#endif
      }
      return false;
      break;
  }
return true;
}

void suspend_power_down_kb(void)
{
    // rgb_matrix_set_suspend_state(true); // what is this
}

void suspend_wakeup_init_kb(void)
{
    // rgb_matrix_set_suspend_state(false);
}

uint32_t layer_state_set_user(uint32_t state) {
    uint8_t layer = biton32(state);
    // TODO: Figure our what to do with board LEDs
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case GAME:
            // ergodox_right_led_3_on();
            break;
        default:
            break;
    }
    return state;
};
