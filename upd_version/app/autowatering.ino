/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

/*
context ids:
  0: main;
  1: settings;
  2: watering type;
  3: next watering;
  4: watering dosage;
*/


/* State watering types:
 *  0: by days;
 *  1: by soil moisture;
 */

#include <Arduino.h>
#include "constants.h"
#include "option.h"
#include "State.h"
#include "Controller.h"
#include <LiquidCrystal.h>

unsigned long timer;

State state(2, 100, 0, 1, 0);
View view(1);
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
}

void loop() {
    checkBtn(controller.state_btn);
    checkBtn(controller.setting_btn);
    checkBtn(controller.up_btn);
    checkBtn(controller.down_btn);
    checkBtn(controller.cancel_btn);
    checkBtn(controller.ok_btn);
}