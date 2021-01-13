//
// Created by cosmicintruder on 13.01.2021.
//

#ifndef AUTOPOLIV_TOPBUTTON_H
#define AUTOPOLIV_TOPBUTTON_H

#include "CustomButton.h"

class TopButton : public CustomButton {
public:
    TopButton(unsigned short btnPin);
    void handler();
};


#endif //AUTOPOLIV_TOPBUTTON_H
