#ifndef AUTOWATERING_CONTROLLER_H
#define AUTOWATERING_CONTROLLER_H

#include "constants.h"
#include "State.h"
#include "View.h"
#include "Button.h"

enum buttons {
    state_button,
    setting_button,
    ok_button,
    cancel_button,
    up_button,
    down_button
};


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

    Controller(State* st, View* v);

    void settingHandler();
    void stateHandler();
    void downHandler();
    void upHandler();
    void cancelHandler();
    void okHandler();
};


#endif //AUTOWATERING_CONTROLLER_H
