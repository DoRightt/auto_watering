#include <Arduino.h>
#include "constants.h"
#include "option.h"
#include "State.h"
#include "Controller.h"
#include "View.h"

#define WATERLEVEL_PIN A4
#define MOISTURE_PIN A6
#define PUMP_PIN 13

extern volatile unsigned long timer0_millis;

unsigned long btn_timer;
unsigned long moisture_timer;
unsigned long w_level_timer;
unsigned long days_timer;
unsigned long main_screen_timer;
unsigned long pump_timer;

unsigned days = 0;

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
    pinMode(PUMP_PIN, OUTPUT);

    btn_timer = millis();
    w_level_timer = millis();
    moisture_timer = millis();
    days_timer = millis();
    main_screen_timer = millis();

    Serial.begin(9600);
    state.setStateId(MANUAL_STATE_ID);
    view.begin(16, 2);
    view.showScreen(screens::MAIN, &state);
}

void loop() {
//    digitalWrite(PUMP_PIN, HIGH);
    checkBtn(controller.state_btn);
    checkBtn(controller.setting_btn);
    checkBtn(controller.up_btn);
    checkBtn(controller.down_btn);
    checkBtn(controller.cancel_btn);
    checkBtn(controller.ok_btn);

    checkWaterLevel();
    checkMoisture();
    checkWatering();
//    changeMainScreen();
}

void checkBtn(Button &btn) {
    bool btn_is_up = digitalRead(btn.pin);
    if (btn.was_up && !btn_is_up) {
        if (millis() - btn_timer > 100) {
            btn_timer = millis();

            btn_is_up = digitalRead(btn.pin);

            if (!btn_is_up) {
                switch (btn.id) {
                    case buttons::state_button:
                        controller.stateHandler();
                        break;
                    case buttons::setting_button:
                        controller.settingHandler();
                        break;
                    case buttons::ok_button:
                        controller.okHandler();
                        break;
                    case buttons::cancel_button:
                        controller.cancelHandler();
                        break;
                    case buttons::up_button:
                        controller.upHandler();
                        break;
                    case buttons::down_button:
                        controller.downHandler();
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
    if (millis() - moisture_timer > 500) {
        moisture_timer = millis();

        int moisture = convertToPercent(analogRead(MOISTURE_PIN));
        state.moisture = moisture;
    }
}

void checkWatering() {
//    unsigned days = (millis() / 1000) / 60 / 60 / 24;

    if (state.watering_type == w_types::by_days) {
        if (millis() > (1000*3600*24)) {
            ++days;
            ++state.days_passed;
            resetMillis();
        }

        if (days >= state.days_to_watering) {
            days = 0;
            state.days_passed = 0;
            watering();
        }
    } else if (state.watering_type == w_types::by_moisture) {
        if (state.moisture < state.moisture_to_watering) {
            watering();
        }
    }
}

void watering() {
    float mlPerSecond = PUMP_POWER / 3.6;
    float wateringTime = state.water_dosage / (mlPerSecond / 1000);

    digitalWrite(PUMP_PIN, HIGH);
    delay(wateringTime);
    digitalWrite(PUMP_PIN, LOW);
}

void changeMainScreen() {
    if (state.getContext() == contexts::main_ctx) {
        if (millis() - main_screen_timer > 10000) {
            main_screen_timer = millis();
            main_screens scr = (view.current_main_screen + 1) % 3;
            view.showScreen(scr, &state);
        }
    }
}

int convertToPercent(int value) {
    unsigned map_low = 1017;
    unsigned map_high = 302;
    int percentValue = 0;
    percentValue = map(value, map_low, map_high, 0, 100);
    return percentValue;
}

void resetMillis() {
    timer0_millis = 0;

    btn_timer = millis();
    w_level_timer = millis();
    moisture_timer = millis();
    days_timer = millis();
    main_screen_timer = millis();
}

void checkMillis() {
    unsigned long curTimer = millis();

    if (btn_timer > curTimer || moisture_timer > curTimer || w_level_timer > curTimer || days_timer > curTimer || main_screen_timer > curTimer || pump_timer > curTimer) {
        btn_timer = w_level_timer = moisture_timer = days_timer = main_screen_timer = pump_timer = curTimer;
    }
}