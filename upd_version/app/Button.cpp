#include "Button.h"

Button::Button(unsigned btn_pin, unsigned btn_id) {
    id = btn_id;
    pin = btn_pin;
    was_up = true;
}
