#ifndef AUTOWATERING_VIEW_H
#define AUTOWATERING_VIEW_H

#include "constants.h"

class View {
public:
    View();

    void updateOptionsView();
    void clearLcdLine(unsigned line);
    void showScreen(Screens screen);
};


#endif //AUTOWATERING_VIEW_H