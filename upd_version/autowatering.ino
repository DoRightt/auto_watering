#include <Arduino.h>
#include "constants.h"
#include "option.h"
#include "State.h"
#include "Controller.h"
#include "View.h"

unsigned long timer;

State state(2, 100, 0, 1, 0);
View view;
Controller controller(&state, &view);

void setup() {
    pinMode(AUTO_LED_PIN, OUTPUT);
    pinMode(MANUAL_LED_PIN, OUTPUT);
    pinMode(controller.state_btn.pin, INPUT_PULLUP);
    pinMode(controller.setting_btn.pin, INPUT_PULLUP);
    pinMode(controller.down_btn.pin, INPUT_PULLUP);
    pinMode(controller.up_btn.pin, INPUT_PULLUP);
    pinMode(controller.cancel_btn.pin, INPUT_PULLUP);
    pinMode(controller.ok_btn.pin, INPUT_PULLUP);

    timer = millis();

    Serial.begin(9600);
    state.setStateId(MANUAL_STATE_ID);
    view.showScreen(Screens::MAIN);
}

void loop() {
    checkBtn(controller.state_btn);
    checkBtn(controller.setting_btn);
    checkBtn(controller.up_btn);
    checkBtn(controller.down_btn);
    checkBtn(controller.cancel_btn);
    checkBtn(controller.ok_btn);
}

void checkBtn(Button &btn) {
    bool btn_is_up = digitalRead(btn.pin);
    if (btn.was_up && !btn_is_up) {
        if (millis() - timer > 10){
            timer = millis();

            btn_is_up = digitalRead(btn.pin);

            if (!btn_is_up) {
                switch (btn.id) {
                    case buttons::state_button: controller.stateHandler();
                        break;
                    case buttons::setting_button: controller.settingHandler();
                        break;
                    case buttons::ok_button: controller.okHandler();
                        break;
                    case buttons::cancel_button: controller.cancelHandler();
                        break;
                    case buttons::up_button: controller.upHandler();
                        break;
                    case buttons::down_button: controller.downHandler();
                        break;
                }
            }
        }
    }

    btn.was_up = btn_is_up;
}
