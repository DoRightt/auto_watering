//
// Created by cosmicintruder on 13.01.2021.
//

#include "StateButton.h"
#include "CustomButton.h"

StateButton::StateButton(unsigned short btnPin):CustomButton(btnPin) {}

void StateButton::handler(State* st) {
    if (st->id == AUTO_STATE_ID) {
        st->id = MANUAL_STATE_ID;
    } else if (st->id == MANUAL_STATE_ID) {
        st->id = AUTO_STATE_ID;
    }

    st->setState(st->id);
//    showScreen(MAIN);
}

//void StateButton::handler() {
//    if (currentState.id == AUTO_STATE_ID) {
//        currentState.id = MANUAL_STATE_ID;
//    } else if (currentState.id == MANUAL_STATE_ID) {
//        currentState.id = AUTO_STATE_ID;
//    }
//
//    setState(currentState.id);
//}
