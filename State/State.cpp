#include "State.h"

State::State(unsigned short stateId, unsigned short dosage, unsigned short moisturePercent, unsigned short daysTo, unsigned short daysPass) {
    id = stateId;
    waterDosage = dosage;
    moisture = moisturePercent;
    daysToWatering = daysTo;
    daysPassed = daysPass;
}

void State::setContext(unsigned short id) {
    contextId = id;
}