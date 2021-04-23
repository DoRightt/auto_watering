#ifndef AUTOWATERING_VIEW_H
#define AUTOWATERING_VIEW_H

#include "constants.h"
#include "State.h"
#include <LiquidCrystal.h>

class View {
public:
    View();
    unsigned current_main_screen = main_screens::FIRST;

    void updateOptionsView(State* st);
    void clearLcdLine(unsigned line);
    void showScreen(screens screen, State* st);
    void showScreen(main_screens screen, State* st);
    void showScreen(String first, String second);
    void printString(int i, String msg);
    void setCursor(int x, int y);
    void print(String msg);
    void begin(int x, int y);
    void clear();
};


#endif //AUTOWATERING_VIEW_H
