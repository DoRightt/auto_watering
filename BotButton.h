//
// Created by cosmicintruder on 13.01.2021.
//

#ifndef AUTOPOLIV_BOTBUTTON_H
#define AUTOPOLIV_BOTBUTTON_H

#include "CustomButton.h"

class BotButton : public CustomButton {
public:
    BotButton(unsigned short btnPin);
    void handler();
};


#endif //AUTOPOLIV_BOTBUTTON_H
