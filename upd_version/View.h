#ifndef AUTOWATERING_VIEW_H
#define AUTOWATERING_VIEW_H

#include "constants.h"
#include "State.h"
#include <LiquidCrystal.h>

class View {
public:
    View();

    void updateOptionsView(State* st);
    void clearLcdLine(unsigned line);
    void showScreen(Screens screen);
    void setCursor(int x, int y);
    void print(char msg);
    void begin(int x, int y);
    void clear();
};


#endif //AUTOWATERING_VIEW_H
