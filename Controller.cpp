#include "Controller.h"

Controller::Controller(State *st, View *v) {
    state = st;
    view = v;
}

void Controller::settingHandler() {
    if (state->state_id == AUTO_STATE_ID) {
        state->setContext(contexts::settings_ctx);

        view->updateOptionsView(state);
    }
}

void Controller::stateHandler() {
    if (state->isAutoState()) {
        state->setStateId(MANUAL_STATE_ID);
    } else if (state->isManualState()) {
        state->setStateId(AUTO_STATE_ID);
    }

    digitalWrite(A6, LOW);
    state->setContext(contexts::main_ctx);
    view->showScreen(screens::MAIN, state);
}

void Controller::downHandler() {

    switch (state->context_id) {
        case contexts::watering_dosage_ctx: {
            dosage_tmp = (dosage_tmp ? dosage_tmp : state->water_dosage);
            if (dosage_tmp > 0) {
                view->clearLcdLine(2);
                dosage_tmp -= 25;
                char message[16];
                sprintf(message, "%dml", dosage_tmp);

                view->printString(1, message);
            }

            break;
        }
        case contexts::watering_next_ctx: {
            if (state->watering_type == w_types::by_days) {
                w_next_d_tmp = (w_next_d_tmp ? w_next_d_tmp : state->days_to_watering);
                if (w_next_d_tmp > 1) {
                    view->clearLcdLine(2);
                    w_next_d_tmp -= 1;
                    char message[16];
                    sprintf(message, "In %d days", w_next_d_tmp);

                    view->printString(1, message);
                }
            }

            if (state->watering_type == w_types::by_moisture) {
                if (w_next_m_tmp > 0) {
                    w_next_m_tmp = (w_next_m_tmp ? w_next_m_tmp : state->moisture_to_watering);
                    view->clearLcdLine(2);
                    w_next_m_tmp -= 5;
                    char message[16];
                    sprintf(message, "Moisture is %d%%", w_next_m_tmp);

                    view->printString(1, message);
                }
            }

            break;
        }
        case contexts::watering_type_ctx: {
            view->clearLcdLine(2);
            w_type_tmp = w_types::by_moisture;
            char message[16];
            sprintf(message, "By %s", "soil moisture");

            view->printString(1, message);

            break;
        }
        case contexts::settings_ctx: {
            if (state->selected_option_id < 3) {
                state->prev_option_id = state->selected_option_id;
                state->selected_option_id += 1;
                view->updateOptionsView(state);
            }

            break;
        }
        default:;
    }
}

void Controller::upHandler() {

    switch (state->context_id) {
        case contexts::watering_dosage_ctx: {
            dosage_tmp = (dosage_tmp ? dosage_tmp : state->water_dosage);
            if (dosage_tmp < 500) {
                view->clearLcdLine(2);
                dosage_tmp += 25;
                char message[16];
                sprintf(message, "%dml", dosage_tmp);

                view->printString(1, message);
            }

            break;
        }
        case contexts::watering_next_ctx: {
            if (state->watering_type == w_types::by_days) {
                w_next_d_tmp = (w_next_d_tmp ? w_next_d_tmp : state->days_to_watering);
                if (w_next_d_tmp < 30) {
                    view->clearLcdLine(2);
                    w_next_d_tmp += 1;
                    char message[16];
                    sprintf(message, "In %d days", w_next_d_tmp);

                    view->printString(1, message);
                }
            }

            if (state->watering_type == w_types::by_moisture) {
                w_next_m_tmp = (w_next_m_tmp ? w_next_m_tmp : state->moisture_to_watering);
                if (w_next_m_tmp < 100) {
                    view->clearLcdLine(2);
                    w_next_m_tmp += 5;
                    char message[16];
                    sprintf(message, "Moisture is %d%%", w_next_m_tmp);

                    view->printString(1, message);
                }
            }

            break;
        }
        case contexts::watering_type_ctx: {
            view->clearLcdLine(2);
            w_type_tmp = w_types::by_days;
            char message[16];
            sprintf(message, "By %s", "days");

            view->printString(1, message);

            break;
        }
        case contexts::settings_ctx: {
            if (state->selected_option_id > 1) {
                state->prev_option_id = state->selected_option_id;
                state->selected_option_id -= 1;
                view->updateOptionsView(state);
            }
        }
    }
}

void Controller::cancelHandler() {
    if (state->isAutoState()) {
        String moisture_msg = "Moisture: " + String(state->moisture) + "%";
        String w_level_msg = "Water level: " + state->water_level;
        state->setContext(contexts::main_ctx);
        view->showScreen(moisture_msg, w_level_msg);
    } else if (state->isManualState()) {
        stopWatering();
    }
}

void Controller::okHandler() {
    if (state->isSettings()) {
        switch (state->selected_option_id) {
            case options::watering_dosage: {
                state->setContext(contexts::watering_dosage_ctx);
                char message[16];
                sprintf(message, "%dml", state->water_dosage);

                view->showScreen("Set dosage:", message);
                break;
            }
            case options::watering_next: {
                state->setContext(contexts::watering_next_ctx);
                char message[16];

                if (state->watering_type == w_types::by_days) {
                    sprintf(message, "In %d days", state->days_to_watering);
                }

                if (state->watering_type == w_types::by_moisture) {
                    sprintf(message, "Moisture is %d%%", state->moisture_to_watering);
                }

                view->showScreen("Next watering:", message);
                break;
            }
            case options::watering_type: {
                state->setContext(contexts::watering_type_ctx);
                char message[16];
                sprintf(message, "By %s", state->watering_type == w_types::by_days ? "days" : "soil moisture");

                view->showScreen("Watering type:", message);
                break;
            }
        }
    } else if (state->getContext() == contexts::watering_type_ctx) {
        state->setWateringType(w_type_tmp);
        state->setContext(contexts::main_ctx);
        view->showScreen(MAIN, state);
    } else if (state->getContext() == contexts::watering_next_ctx) {
        state->setNextWatering((state->watering_type == w_types::by_days ? w_next_d_tmp : w_next_m_tmp));
        state->setContext(contexts::main_ctx);
        view->showScreen(MAIN, state);
    } else if (state->getContext() == contexts::watering_dosage_ctx) {
        state->setDosage(dosage_tmp);
        state->setContext(contexts::main_ctx);
        view->showScreen(MAIN, state);
    } else if (state->isManualState()) {
        if (hasEnoughWater()) {
            watering();
        }
    }

    clearTemp();
}

bool Controller::hasEnoughWater() {
    int w_level = analogRead(WATERLEVEL_PIN);

    return w_level > 900;
}

void Controller::watering() {
    digitalWrite(PUMP_PIN, HIGH);
}

void Controller::watering(unsigned time) {
    watering();
    delay(time);
    stopWatering();
}

void Controller::stopWatering() {
    digitalWrite(PUMP_PIN, LOW);
}

void Controller::clearTemp() {
    w_next_d_tmp = 0;
    w_next_m_tmp = 0;
    w_type_tmp = 0;
    dosage_tmp = 0;
}
