//
// Created by cosmicintruder on 15.01.2021.
//

#include "State.h"

State::State(unsigned short stateId, unsigned short dosage, unsigned short moisturePercent, unsigned short daysTo, unsigned short daysPass) {
    id = stateId;
    waterDosage = dosage;
    moisture = moisturePercent;
    daysToWatering = daysTo;
    daysPassed = daysPass;
}

State::setContext(unsigned short id) {
    contextId = id;
}

State::setState(int stateId) {
    digitalWrite(AUTO_LED_PIN, id == AUTO_STATE_ID);
    digitalWrite(MANUAL_LED_PIN, id == MANUAL_STATE_ID);
}
