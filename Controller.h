#ifndef AUTOWATERING_CONTROLLER_H
#define AUTOWATERING_CONTROLLER_H

#include "constants.h"
#include "State.h"
#include "View.h"
#include "Button.h"


class Controller {
public:
    State* state;
    View* view;
    Button state_btn = decltype(state_btn)(6, buttons::state_button);
    Button setting_btn = decltype(setting_btn)(7, buttons::setting_button);
    Button down_btn = decltype(down_btn)(14, buttons::down_button);
    Button up_btn = decltype(up_btn)(15, buttons::up_button);
    Button cancel_btn = decltype(cancel_btn)(16, buttons::cancel_button);
    Button ok_btn = decltype(ok_btn)(17, buttons::ok_button);

    unsigned w_type_tmp;
    unsigned w_next_d_tmp = 0;
    unsigned w_next_m_tmp = 0;
    unsigned dosage_tmp = 0;

    Controller(State* st, View* v);

    void clearTemp();
    void settingHandler();
    void stateHandler();
    void downHandler();
    void upHandler();
    void cancelHandler();
    void okHandler();
    void watering();
    void watering(unsigned time);
    void stopWatering();
    bool hasEnoughWater();
};


#endif //AUTOWATERING_CONTROLLER_H
