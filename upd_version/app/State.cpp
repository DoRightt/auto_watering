#include "State.h"

State::State(unsigned id, unsigned dosage, unsigned moisture_percent, unsigned days_to, unsigned days_pass) {
    state_id = id;
    water_dosage = dosage;
    moisture = moisture_percent;
    days_to_watering = days_to;
    days_passed = days_pass;
}

void State::setContext(unsigned id) {
    context_id = id;
}

void State::setStateId(int id) {
//    digitalWrite(AUTO_LED_PIN, id == AUTO_STATE_ID);
//    digitalWrite(MANUAL_LED_PIN, id == MANUAL_STATE_ID);
}
