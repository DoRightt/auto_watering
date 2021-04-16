#ifndef AUTO_WATERING_OPTION_H
#define AUTO_WATERING_OPTION_H

//#include <Arduino.h>
#include <iostream>

using std::string;

struct option {
public:
    int id;
    string name;
    option(int option_id, string option_name);
};


#endif //AUTO_WATERING_OPTION_H