#ifndef AUTO_WATERING_STATE_H
#define AUTO_WATERING_STATE_H

//#include <Arduino.h>
#include "option.h"
#include "constants.h"
#include <iostream>

//enum Options {
//    watering_type = 1,
//    watering_next = 2,
//    watering_dosage = 3
//};
//
//// Options
////1: "Watering type";
////2: "Next watering";
////3: "Watering dosage";
//
//// State types
//const unsigned AUTO_STATE_ID = 1;
//const unsigned MANUAL_STATE_ID = 2;
//
//// Leds
//const unsigned AUTO_LED_PIN = 10;
//const unsigned MANUAL_LED_PIN = 9;

class State {
public:
    unsigned state_id;
    unsigned context_id = 0;
    unsigned moisture;
    unsigned water_dosage;
    unsigned days_passed;
    unsigned days_to_watering;
    option options[3] {
        option (Options::watering_type, "Watering type"),
        option (Options::watering_next, "Next watering"),
        option (Options::watering_dosage, "Watering dosage")
    };
    unsigned selected_option_id = options[0].id;
    unsigned prev_option_id;
    unsigned watering_type = 0;
    State(unsigned id, unsigned dosage, unsigned moisture_percent, unsigned days_to, unsigned days_pass);
    void setContext(unsigned id);
    void setStateId(int id);
    bool isSettings();
    bool isAutoState();
    bool isManualState();
};


#endif //AUTO_WATERING_STATE_H
