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
    if (state->state_id == AUTO_STATE_ID) {
        state->state_id = MANUAL_STATE_ID;
    } else if (state->state_id == MANUAL_STATE_ID) {
        state->state_id = AUTO_STATE_ID;
    }
}

void Controller::downHandler() {
    std::cout << "down" << std:: endl;
}

void Controller::upHandler() {
    std::cout << "up" << std:: endl;
}

void Controller::cancelHandler() {
    std::cout << "cancel" << std:: endl;
}

void Controller::okHandler() {
    std::cout << "ok" << std:: endl;
}