#ifndef AUTOWATERING_CONSTANTS_H
#define AUTOWATERING_CONSTANTS_H

/*
context ids:
  0: main;
  1: settings;
  2: watering type;
  3: next watering;
  4: watering dosage;
*/


/* State watering types:
 *  0: by days;
 *  1: by soil moisture;
 */

enum buttons {
    state_button,
    setting_button,
    ok_button,
    cancel_button,
    up_button,
    down_button
};


enum Options {
    watering_type = 1,
    watering_next = 2,
    watering_dosage = 3
};

enum Screens {
    MAIN,
    SETTINGS,
    WATERING_TYPE,
    NEXT_WATERING,
    WATERING_DOSAGE
};

// State types
const unsigned AUTO_STATE_ID = 1;
const unsigned MANUAL_STATE_ID = 2;

// Leds
const unsigned AUTO_LED_PIN = 10;
const unsigned MANUAL_LED_PIN = 9;


#endif //AUTOWATERING_CONSTANTS_H
