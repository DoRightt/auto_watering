#ifndef AUTO_WATERING_OPTION_H
#define AUTO_WATERING_OPTION_H

#include <Arduino.h>

struct option {
public:
    int id;
    String name;
    option(int option_id, String option_name);
};


#endif //AUTO_WATERING_OPTION_H
