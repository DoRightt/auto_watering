//
// Created by cosmicintruder on 15.01.2021.
//
#include <Arduino.h>
#include "option.h"

#ifndef AUTO_WATERING_STATE_H
#define AUTO_WATERING_STATE_H

// Options
//1: "Watering type";
//2: "Next watering";
//3: "Watering dosage";

// States
const unsigned short AUTO_STATE_ID = 1;
const unsigned short MANUAL_STATE_ID = 2;

// Leds
const unsigned short AUTO_LED_PIN = 10;
const unsigned short MANUAL_LED_PIN = 9;

class State {
public:
    unsigned short id;
    unsigned short waterDosage;
    unsigned short moisture;
    unsigned short daysToWatering;
    unsigned short daysPassed;
    unsigned short contextId = 0;
    option options[3] {option (1, "Watering type"), option (2, "Next watering"), option (3, "Watering dosage")};
    unsigned short selectedOptionId = options[0].id;
    unsigned short prevOptionId;
    unsigned short wateringType = 0;
    State(unsigned short stateId, unsigned short dosage, unsigned short moisturePercent, unsigned short daysTo, unsigned short daysPass);
    setContext(unsigned short id);
    setState(int stateId);
};


#endif //AUTO_WATERING_STATE_H
