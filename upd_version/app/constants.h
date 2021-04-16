#ifndef AUTOWATERING_CONSTANTS_H
#define AUTOWATERING_CONSTANTS_H


enum Options {
    watering_type = 1,
    watering_next = 2,
    watering_dosage = 3
};

// State types
const unsigned AUTO_STATE_ID = 1;
const unsigned MANUAL_STATE_ID = 2;

// Leds
const unsigned AUTO_LED_PIN = 10;
const unsigned MANUAL_LED_PIN = 9;


#endif //AUTOWATERING_CONSTANTS_H
