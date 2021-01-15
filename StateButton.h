//
// Created by cosmicintruder on 13.01.2021.
//

#ifndef AUTOPOLIV_STATEBUTTON_H
#define AUTOPOLIV_STATEBUTTON_H

#include "CustomButton.h"
#include "State.h"


class StateButton : public CustomButton {
public:
    StateButton(unsigned short btnPin);
    void handler(State*);
};


#endif //AUTOPOLIV_STATEBUTTON_H
