//
// Created by cosmicintruder on 13.01.2021.
//

#ifndef AUTOPOLIV_CANCELBUTTON_H
#define AUTOPOLIV_CANCELBUTTON_H

#include "CustomButton.h"

class CancelButton : public CustomButton {
  public:
    CancelButton(unsigned short btnPin);
    void handler();
};


#endif //AUTOPOLIV_CANCELBUTTON_H
