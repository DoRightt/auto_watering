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

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

/*
context ids:
  0: main;
  1: settings;
  2: watering type;
  3: next watering;
  4: watering dosage;
*/

#include "buttons.h"
#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

struct option {
  public: 
    int id;
    String name;
    option(int optionId, String optionName) {
      id = optionId;
      name = optionName;
    }
};

option o1(1, "Watering type");
option o2(2, "Next watering");
option o3(3, "Watering dosage");


// States
const unsigned short AUTO_STATE_ID = 1;
const unsigned short MANUAL_STATE_ID = 2;

// Leds
const unsigned short AUTO_LED_PIN = 10;
const unsigned short MANUAL_LED_PIN = 9;

class State {
  public:
    unsigned short id;
    unsigned short waterDosage;
    unsigned short moisture;
    unsigned short daysToWatering;
    unsigned short daysPassed;
    unsigned short contextId = 0;
    option options[3] {o1, o2, o3};
    unsigned short selectedOptionId = options[0].id;
    unsigned short prevOptionId;
    State(unsigned short stateId, unsigned short dosage, unsigned short moisturePercent, unsigned short daysTo, unsigned short daysPass) {
      id = stateId;
      waterDosage = dosage;
      moisture = moisturePercent;
      daysToWatering = daysTo;
      daysPassed = daysPass;
    }
    setContext(unsigned short id) {
      contextId = id;
    }
    setState(int stateId) {
      digitalWrite(AUTO_LED_PIN, id == AUTO_STATE_ID);
      digitalWrite(MANUAL_LED_PIN, id == MANUAL_STATE_ID);
    }
};

State currentState(2, 100, 0, 0, 0);

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
}

void SettingButton::handler() {
  if (currentState.id == AUTO_STATE_ID) {
    currentState.setContext(1);

    updateOptionsView();
//    lcd.begin(16, 2);
//    lcd.print("*Watering type");  
//    
//    lcd.setCursor(0, 1);
//    lcd.print("*Next watering");
//    lcd.print(" Watering dosage");
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
    delay(10);

    buttonIsUp = digitalRead(btn.pin);
   

    if (!buttonIsUp) {
      btn.handler();
    }
  }

  btn.wasUp = buttonIsUp;
}

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
