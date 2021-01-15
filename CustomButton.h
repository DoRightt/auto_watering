//
// Created by cosmicintruder on 13.01.2021.
//
#include "State.h"

#ifndef AUTOPOLIV_CUSTOMBUTTON_H
#define AUTOPOLIV_CUSTOMBUTTON_H


class CustomButton {
public:
    unsigned short pin;
    bool wasUp;
    virtual void handler(State*);
    CustomButton(unsigned short btnPin);
};


#endif //AUTOPOLIV_CUSTOMBUTTON_H
