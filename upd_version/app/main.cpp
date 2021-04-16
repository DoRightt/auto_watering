#include <iostream>
#include <vector>
#include "option.h"
#include "State.h"
#include "View.h"
#include "Controller.h"
#include "Button.h"


using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::end;
using std::begin;

enum Screens { MAIN, SETTINGS, WATERING_TYPE, NEXT_WATERING, WATERING_DOSAGE };


int main() {
    State state(2, 100, 0, 1, 0);
    View view(1);
    Controller controller(&state, &view);


    return 0;
}