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
    state_id = id;
    digitalWrite(AUTO_LED_PIN, id == AUTO_STATE_ID);
    digitalWrite(MANUAL_LED_PIN, id == MANUAL_STATE_ID);
}

void State::setWateringType(int type) {
    watering_type = type;
}

void State::setDosage(unsigned dose) {
    water_dosage = dose;
}

void State::setNextWatering(unsigned nxt) {
    if (watering_type == w_types::by_days) {
        days_to_watering = nxt;
    } else if (watering_type == w_types::by_moisture) {
        moisture_to_watering = nxt;
    }
}

bool State::isSettings() {
    return context_id == contexts::settings_ctx;
}

int State::getContext() {
    return context_id;
}

bool State::isAutoState() {
    return state_id == AUTO_STATE_ID;
}

bool State::isManualState() {
    return state_id == MANUAL_STATE_ID;
}
