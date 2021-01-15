//
// Created by cosmicintruder on 15.01.2021.
//
#include <Arduino.h>

#ifndef AUTO_WATERING_OPTION_H
#define AUTO_WATERING_OPTION_H


struct option {
public:
    int id;
    String name;
    option(int optionId, String optionName);
};


#endif //AUTO_WATERING_OPTION_H
