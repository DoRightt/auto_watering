#include <Arduino.h>
#include "constants.h"
#include "option.h"
#include "State.h"
#include "Controller.h"
#include "View.h"

#define WATERLEVEL_PIN A4
#define MOISTURE_PIN A5

unsigned long btn_timer;
unsigned long moisture_timer;
unsigned long w_level_timer;
unsigned long days_timer;

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

    btn_timer = millis();
    w_level_timer = millis();
    moisture_timer = millis();
    days_timer = millis();

    Serial.begin(9600);
    state.setStateId(MANUAL_STATE_ID);
    view.begin(16, 2);
    view.showScreen(screens::MAIN);
}

void loop() {
    checkBtn(controller.state_btn);
    checkBtn(controller.setting_btn);
    checkBtn(controller.up_btn);
    checkBtn(controller.down_btn);
    checkBtn(controller.cancel_btn);
    checkBtn(controller.ok_btn);

    checkWaterLevel();
    checkMoisture();
    checkWatering();
}

void checkBtn(Button &btn) {
    bool btn_is_up = digitalRead(btn.pin);
    if (btn.was_up && !btn_is_up) {
        if (millis() - btn_timer > 100){
            btn_timer = millis();

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

void checkWaterLevel() {
    if (millis() - w_level_timer > 1000) {
        w_level_timer = millis();

        int w_level = analogRead(WATERLEVEL_PIN);
        state.water_level = w_level < 900 ? "low" : "OK";
    }
}

void checkMoisture() {
    if (millis() - moisture_timer > 1000) {
        moisture_timer = millis();

        int moisture = convertToPercent(analogRead(MOISTURE_PIN));
        state.moisture = moisture;
        Serial.println(state.moisture);
    }
}

void checkWatering() {
    int seconds = millis() / 1000;
    int minutes = (millis() / 1000) / 60;
    int hours = (millis() / 1000) / 60 / 60;
    if (state.watering_type == w_types::by_days) {
//        Serial.println(minutes);
//        Serial.println(seconds);
        delay(1000);
    }
}

int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value, 1023, 465, 0, 100);
  return percentValue;
}
