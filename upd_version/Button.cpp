#include "Button.h"

Button::Button(unsigned btn_pin, unsigned btn_id) {
    pin = btn_pin;
    id = btn_id;
    was_up = true;
}
