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
#include "option.h"
#include "State.h"
#include "buttons.h"
#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

enum Screens {MAIN, SETTINGS, WATERING_TYPE, NEXT_WATERING, WATERING_DOSAGE};
unsigned long timer;
State currentState(2, 100, 0, 1, 0);

// Btns
StateButton stateBtn(6);
SettingButton settingBtn(7);
BotButton botBtn(14);
TopButton topBtn(15);
CancelButton cancelBtn(16);
OkButton okBtn(17);

void setup() {
  pinMode(AUTO_LED_PIN, OUTPUT);
  pinMode(MANUAL_LED_PIN, OUTPUT);
  pinMode(stateBtn.pin, INPUT_PULLUP);
  pinMode(settingBtn.pin, INPUT_PULLUP);
  pinMode(botBtn.pin, INPUT_PULLUP);
  pinMode(topBtn.pin, INPUT_PULLUP);
  pinMode(cancelBtn.pin, INPUT_PULLUP);
  pinMode(okBtn.pin, INPUT_PULLUP);

  timer = millis();
  
  Serial.begin(9600);
  currentState.setState(MANUAL_STATE_ID);
  
// first screen
  lcd.begin(16, 2);
  lcd.print("Moisture: 97%");
  lcd.setCursor(0, 1);
  lcd.print("Water level: low");

// second screen
//  lcd.begin(16, 2);
//  lcd.print("nxt watering:10%");
//  lcd.setCursor(0, 1);
//  lcd.print("lst watering:10d");

// third screen
//  lcd.begin(16, 2);
//  lcd.print("watering dosage:");
//  lcd.setCursor(0, 1);
//  lcd.print("100ml");
}

void loop() {
  checkBtn(stateBtn);
  checkBtn(settingBtn);
  checkBtn(topBtn);
  checkBtn(botBtn);
  checkBtn(cancelBtn);
  checkBtn(okBtn);
}

void StateButton::handler() {
  if (currentState.id == AUTO_STATE_ID) {
    currentState.id = MANUAL_STATE_ID;
  } else if (currentState.id == MANUAL_STATE_ID) {
    currentState.id = AUTO_STATE_ID;
  }

  currentState.setState(currentState.id);
  showScreen(MAIN);
}

void SettingButton::handler() {
  if (currentState.id == AUTO_STATE_ID) {
    currentState.setContext(1);

    updateOptionsView();
  }
}

void CancelButton::handler() {
  currentState.setContext(0);
  lcd.begin(16, 2);
  lcd.print("Moisture: 97%");
  lcd.setCursor(0, 1);
  lcd.print("Water level: low");
}

void OkButton::handler() {
  if (currentState.contextId == 1) {
    if (currentState.selectedOptionId == 3) {
       currentState.setContext(4);
       char message[16];
       sprintf(message, "%dml", currentState.waterDosage);
       lcd.clear();
       lcd.begin(16, 2);
       lcd.print("Set dosage:");
       lcd.setCursor(0, 1);
       lcd.print(message);
    }

    if (currentState.selectedOptionId == 2) {
       currentState.setContext(3);
       char message[16];
       if (currentState.wateringType == 0) {
        sprintf(message, "In %d days", currentState.daysToWatering);
       } 

       if (currentState.wateringType == 1) {
        sprintf(message, "Moisture is %d%%", currentState.moisture);
       }
       lcd.clear();
       lcd.begin(16, 2);
       lcd.print("Next watering:");
       lcd.setCursor(0, 1);
       lcd.print(message);
    }

    if (currentState.selectedOptionId == 1) {
       currentState.setContext(2);
       char message[16];
       sprintf(message, "By %s", currentState.wateringType == 0 ? "days" : "soil moisture");
       lcd.clear();
       lcd.begin(16, 2);
       lcd.print("Watering type:");
       lcd.setCursor(0, 1);
       lcd.print(message);
    }
  }
}

void TopButton::handler() {
  if (currentState.contextId == 4) {
    if (currentState.waterDosage < 500) {
      clearLCDLine(2);
      currentState.waterDosage += 25;
      char message[16];
      sprintf(message, "%dml", currentState.waterDosage);
      lcd.setCursor(0, 1);
      lcd.print(message);
    }
  }

  if (currentState.contextId == 3) {
    if (currentState.wateringType == 0) {
      if (currentState.daysToWatering < 30) {
        clearLCDLine(2);
        currentState.daysToWatering += 1;
        char message[16];
        sprintf(message, "In %d days", currentState.daysToWatering);
        lcd.setCursor(0, 1);
        lcd.print(message);
      }
    }

    if (currentState.wateringType == 1) {
      if (currentState.moisture < 100) {
        clearLCDLine(2);
        currentState.moisture += 5;
        char message[16];
        sprintf(message, "Moisture is %d%%", currentState.moisture);
        lcd.setCursor(0, 1);
        lcd.print(message);
      }
    }
  }

  if (currentState.contextId == 2) {
    clearLCDLine(2);
    currentState.wateringType = 0;
    char message[16];
    sprintf(message, "By %s", currentState.wateringType == 0 ? "days" : "soil moisture");
    lcd.setCursor(0, 1);
    lcd.print(message);
  }

  if (currentState.contextId == 1) {
    if (currentState.selectedOptionId > 1) {
      currentState.prevOptionId = currentState.selectedOptionId;
      currentState.selectedOptionId -= 1;
      updateOptionsView();
    }
  }
}

void BotButton::handler() {
  if (currentState.contextId == 4) {
    if (currentState.waterDosage > 0) {
      clearLCDLine(2);
      currentState.waterDosage -= 25;
      char message[16];
      sprintf(message, "%dml", currentState.waterDosage);
      lcd.setCursor(0, 1);
      lcd.print(message);
    }
  }

  if (currentState.contextId == 3) {
    if (currentState.wateringType == 0) {
      if (currentState.daysToWatering > 1) {
        clearLCDLine(2);
        currentState.daysToWatering -= 1;
        char message[16];
        sprintf(message, "In %d days", currentState.daysToWatering);
        lcd.setCursor(0, 1);
        lcd.print(message);
      }
    }

    if (currentState.wateringType == 1) {
      if (currentState.moisture > 0) {
        clearLCDLine(2);
        currentState.moisture -= 5;
        char message[16];
        sprintf(message, "Moisture is %d%%", currentState.moisture);
        lcd.setCursor(0, 1);
        lcd.print(message);
      }
    }
  }

  if (currentState.contextId == 2) {
    clearLCDLine(2);
    currentState.wateringType = 1;
    char message[16];
    sprintf(message, "By %s", currentState.wateringType == 0 ? "days" : "soil moisture");
    lcd.setCursor(0, 1);
    lcd.print(message);
  }

  if (currentState.contextId == 1) {
    if (currentState.selectedOptionId < 3) {
      currentState.prevOptionId = currentState.selectedOptionId;
      currentState.selectedOptionId += 1;
      updateOptionsView();
    }
  }
}

void checkBtn(CustomButton &btn) {
  boolean buttonIsUp = digitalRead(btn.pin);
  if (btn.wasUp && !buttonIsUp) {
    if (millis() - timer > 10){
      timer = millis(); 

      buttonIsUp = digitalRead(btn.pin);
   

      if (!buttonIsUp) {
        btn.handler();
      }
    }
  }

  btn.wasUp = buttonIsUp;
}

//void checkBtn(CustomButton &btn) {
//  boolean buttonIsUp = digitalRead(btn.pin);
//  if (btn.wasUp && !buttonIsUp) {
//    delay(10);
//
//    buttonIsUp = digitalRead(btn.pin);
//   
//
//    if (!buttonIsUp) {
//      btn.handler();
//    }
//  }
//
//  btn.wasUp = buttonIsUp;
//}

void updateOptionsView() {
  String firstOptionName = currentState.options[0].name;
  String secondOptionName = currentState.options[1].name;
  String thirdOptionName = currentState.options[2].name;
  unsigned short curId = currentState.selectedOptionId;
  unsigned short prevId = currentState.prevOptionId;
  char firstString[17];
  char secondString[17];
  
  if ((curId == 1 && (!prevId || prevId == 2)) || curId == 2 && prevId == 1) {
    sprintf(firstString, "%s%s", curId ==  1 ? ">" : " ", firstOptionName.c_str());
    sprintf(secondString, "%s%s", curId == 2 ? ">" : " ", secondOptionName.c_str());
  } else if (curId == 2 && (prevId == 3) || curId == 3 && (prevId == 2)) {
    sprintf(firstString, "%s%s", curId == 2 ? ">" : " ", secondOptionName.c_str());
    sprintf(secondString, "%s%s", curId == 3 ? ">" : " ", thirdOptionName.c_str());
  }

//  Serial.println(curId);
//  Serial.println(prevId);
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print(firstString);
  lcd.setCursor(0, 1);
  lcd.print(secondString);
}

void clearLCDLine(int line) {               
  lcd.setCursor(0,line);
  for(int n = 0; n < 20; n++) {
    lcd.print(" ");
  }
}

void showScreen(Screens screen) {
  switch (screen) {
    case MAIN: 
        lcd.begin(16, 2);
        lcd.print("Moisture: 97%");
        lcd.setCursor(0, 1);
        lcd.print("Water level: low");
        break;
  }
  enum Screens {MAIN, SETTINGS, WATERING_TYPE, NEXT_WATERING, WATERING_DOSAGE};
  Serial.println(screen);
}
