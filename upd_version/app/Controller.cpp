#include "Controller.h"

Controller::Controller(State* st, View* v) {
    state = st;
    view = v;
}

void Controller::settingHandler() {
    if (state->state_id == AUTO_STATE_ID) {
        state->setContext(1);

        view->updateOptionsView();
    }
}

void Controller::stateHandler() {
    if (state->isAutoState()) {
        state->state_id = MANUAL_STATE_ID;
    } else if (state->isManualState()) {
        state->state_id = AUTO_STATE_ID;
    }
}

void Controller::downHandler() {

    switch (state->context_id) {
        case 4: {
            if (state->water_dosage > 0) {
                view->clearLcdLine(2);
                state->water_dosage -= 25;
                char message[16];
                sprintf(message, "%dml", state->water_dosage);

//              Should call view method
//              lcd.setCursor(0, 1);
//              lcd.print(message);
            }

            break;
        }
        case 3: {
            if (state->watering_type == 0) {
                if (state->days_to_watering > 1) {
                    view->clearLcdLine(2);
                    state->days_to_watering -= 1;
                    char message[16];
                    sprintf(message, "In %d days", state->days_to_watering);

//                  View method
//                  lcd.setCursor(0, 1);
//                  lcd.print(message);
                }
            }

            if (state->watering_type == 1) {
                if (state->moisture > 0) {
                    view->clearLcdLine(2);
                    state->moisture -= 5;
                    char message[16];
                    sprintf(message, "Moisture is %d%%", state->moisture);

//                  View method
//                  lcd.setCursor(0, 1);
//                  lcd.print(message);
                }
            }

            break;
        }
        case 2: {
            view->clearLcdLine(2);
            state->watering_type = 1;
            char message[16];
            sprintf(message, "By %s", state->watering_type == 0 ? "days" : "soil moisture");

//          View method
//          lcd.setCursor(0, 1);
//          lcd.print(message);

            break;
        }
        case 1: {
            if (state->selected_option_id < 3) {
                state->prev_option_id = state->selected_option_id;
                state->selected_option_id += 1;
                view->updateOptionsView();
            }

            break;
        }
        default: ;
    }
}

void Controller::upHandler() {

    switch (state->context_id) {
        case 4: {
            if (state->water_dosage < 500) {
                view->clearLcdLine(2);
                state->water_dosage += 25;
                char message[16];
                sprintf(message, "%dml", state->water_dosage);

//              View method
//              lcd.setCursor(0, 1);
//              lcd.print(message);
            }

            break;
        }
        case 3: {
            if (state->watering_type == 0) {
                if (state->days_to_watering < 30) {
                    view->clearLcdLine(2);
                    state->days_to_watering += 1;
                    char message[16];
                    sprintf(message, "In %d days", state->days_to_watering);

//                  View method
//                  lcd.setCursor(0, 1);
//                  lcd.print(message);
                }
            }

            if (state->watering_type == 1) {
                if (state->moisture < 100) {
                    view->clearLcdLine(2);
                    state->moisture += 5;
                    char message[16];
                    sprintf(message, "Moisture is %d%%", state->moisture);

//                  View method
//                  lcd.setCursor(0, 1);
//                  lcd.print(message);
                }
            }

            break;
        }
        case 2: {
            view->clearLcdLine(2);
            state->watering_type = 0;
            char message[16];
            sprintf(message, "By %s", state->watering_type == 0 ? "days" : "soil moisture");

//          View method
//          lcd.setCursor(0, 1);
//          lcd.print(message);

            break;
        }
        case 1: {
            if (state->selected_option_id > 1) {
                state->prev_option_id = state->selected_option_id;
                state->selected_option_id -= 1;
                view->updateOptionsView();
            }
        }
    }
}

void Controller::cancelHandler() {
    state->setContext(0);

    // Should call view method
    //lcd.begin(16, 2);
    //lcd.print("Moisture: 97%");
    //lcd.setCursor(0, 1);
    //lcd.print("Water level: low");
}

void Controller::okHandler() {
    if (state->isSettings()) {

        switch (state->selected_option_id) {
            case 3: {
                state->setContext(4);
                char message[16];
                sprintf(message, "%dml", state->water_dosage);

//              Should call view method
//                lcd.clear();
//                lcd.begin(16, 2);
//                lcd.print("Set dosage:");
//                lcd.setCursor(0, 1);
//                lcd.print(message);

                break;
            }
            case 2: {
                state->setContext(3);
                char message[16];

                if (state->watering_type == 0) {
                    sprintf(message, "In %d days", state->days_to_watering);
                }

                if (state->watering_type == 1) {
                    sprintf(message, "Moisture is %d%%", state->moisture);
                }

//              Should call view method
//                lcd.clear();
//                lcd.begin(16, 2);
//                lcd.print("Next watering:");
//                lcd.setCursor(0, 1);
//                lcd.print(message);

                break;
            }
            case 1: {
                state->setContext(2);
                char message[16];
                sprintf(message, "By %s", state->watering_type == 0 ? "days" : "soil moisture");

//              Should call view method
//                lcd.clear();
//                lcd.begin(16, 2);
//                lcd.print("Watering type:");
//                lcd.setCursor(0, 1);
//                lcd.print(message);

                break;
            }
        }
    }
}