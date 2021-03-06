#ifndef AUTOWATERING_CONSTANTS_H
#define AUTOWATERING_CONSTANTS_H

#define WATERLEVEL_PIN A4
#define MOISTURE_PIN A6
#define PUMP_PIN 13

// State watering types:
enum w_types {
    by_days,
    by_moisture
};

enum contexts {
    main_ctx,
    settings_ctx,
    watering_type_ctx,
    watering_next_ctx,
    watering_dosage_ctx
};

enum buttons {
    state_button,
    setting_button,
    ok_button,
    cancel_button,
    up_button,
    down_button
};

enum options {
    watering_type = 1,
    watering_next = 2,
    watering_dosage = 3
};

enum screens {
    MAIN,
    SETTINGS,
    WATERING_TYPE,
    NEXT_WATERING,
    WATERING_DOSAGE
};

enum main_screens {
    FIRST,
    SECOND,
    THIRD
};

// State types
const unsigned AUTO_STATE_ID = 1;
const unsigned MANUAL_STATE_ID = 2;

// Leds
const unsigned AUTO_LED_PIN = 10;
const unsigned MANUAL_LED_PIN = 9;

const unsigned PUMP_POWER = 80; // litres per hour
const unsigned ML_PER_SECOND = PUMP_POWER / 3.6;


#endif //AUTOWATERING_CONSTANTS_H
