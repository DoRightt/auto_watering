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

int main() {
    State state(2, 100, 0, 1, 0);
    View view;
    Controller controller(&state, &view);


    return 0;
}