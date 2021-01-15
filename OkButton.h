    //
// Created by cosmicintruder on 13.01.2021.
//

#ifndef AUTOPOLIV_OKBUTTON_H
#define AUTOPOLIV_OKBUTTON_H

#include "CustomButton.h"

class OkButton : public CustomButton {
public:
    OkButton(unsigned short btnPin);
    void handler();
};



#endif //AUTOPOLIV_OKBUTTON_H
