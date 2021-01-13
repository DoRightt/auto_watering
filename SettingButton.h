//
// Created by cosmicintruder on 13.01.2021.
//

#ifndef AUTOPOLIV_SETTINGBUTTON_H
#define AUTOPOLIV_SETTINGBUTTON_H

#include "CustomButton.h"

class SettingButton : public CustomButton {
public:
    SettingButton(unsigned short btnPin);
    void handler();
};


#endif //AUTOPOLIV_SETTINGBUTTON_H
