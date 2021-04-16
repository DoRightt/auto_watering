#ifndef AUTOWATERING_BUTTON_H
#define AUTOWATERING_BUTTON_H


class Button {
public:
    unsigned id;
    unsigned pin;
    bool was_up;
    Button(unsigned btn_pin, unsigned btn_id);
};



#endif //AUTOWATERING_BUTTON_H
