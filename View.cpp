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

// first screen
//  lcd.begin(16, 2);
//  lcd.print("Moisture: 97%");
//  lcd.setCursor(0, 1);
//  lcd.print("Water level: low");

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

#include "View.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

View::View() {};

void View::updateOptionsView(State* st) {
    String first_option_name = st->options[0].name;
    String second_option_name = st->options[1].name;
    String third_option_name = st->options[2].name;
    unsigned cur_id = st->selected_option_id;
    unsigned prev_id = st->prev_option_id;
    char first_string[17];
    char second_string[17];

    if ((cur_id == 1 && (!prev_id || prev_id == 2)) || cur_id == 2 && prev_id == 1) {
        sprintf(first_string, "%s%s", cur_id ==  1 ? ">" : " ", first_option_name.c_str());
        sprintf(second_string, "%s%s", cur_id == 2 ? ">" : " ", second_option_name.c_str());
    } else if (cur_id == 2 && (prev_id == 3) || cur_id == 3 && (prev_id == 2)) {
        sprintf(first_string, "%s%s", cur_id == 2 ? ">" : " ", second_option_name.c_str());
        sprintf(second_string, "%s%s", cur_id == 3 ? ">" : " ", third_option_name.c_str());
    }

    showScreen(first_string, second_string);
}

void View::clearLcdLine(unsigned line) {
    lcd.setCursor(0,line);
    for(int n = 0; n < 20; n++) {
        lcd.print(" ");
    }
}

void View::showScreen(screens screen, State* st) {
    String s1, s2;
    switch (screen) {
        case MAIN:
            showScreen(main_screens::FIRST, st);
    }
}

void View::showScreen(main_screens screen, State* st) {
    String s1, s2;
    switch (screen) {
        case FIRST:
            s1 = "Moisture: " + String(st->moisture) + "%";
            s2 = "Water level: " + st->water_level;
            current_main_screen = main_screens::FIRST;
            break;
        case SECOND:
            s1 = "Nxt watering:" + (st->watering_type == w_types::by_days ? String(st->days_to_watering) + "d" : String(st->moisture_to_watering) + "%");
            s2 = "Lst watering:" + String(st->days_passed) + "d";
            current_main_screen = main_screens::SECOND;
            break;
        case THIRD:
            s1 = "Watering dosage:";
            s2 = String(st->water_dosage) + "ml";
            current_main_screen = main_screens::THIRD;
            break;
    }

    showScreen(s1, s2);
}

void View::showScreen(String first, String second) {
    lcd.clear();
    printString(0, first);
    printString(1, second);
}

void View::printString(int i, String msg) {
    lcd.setCursor(0, i);
    lcd.print(msg);
}

void View::setCursor(int x, int y) {
    lcd.setCursor(x, y);
}

void View::print(String msg) {
    lcd.print(msg);
}

void View::begin(int x, int y) {
    lcd.begin(x, y);
}

void View::clear() {
    lcd.clear();
}
