#ifndef AUTO_WATERING_STATE_H
#define AUTO_WATERING_STATE_H

#include <Arduino.h>
#include "option.h"
#include "constants.h"

class State {
public:
    unsigned state_id;
    unsigned context_id = 0;
    unsigned moisture;
    unsigned water_dosage;
    unsigned days_passed = 0;
    unsigned days_to_watering;
    unsigned moisture_to_watering;
    String water_level;
    option options[3] {
        option (options::watering_type, "Watering type"),
        option (options::watering_next, "Next watering"),
        option (options::watering_dosage, "Watering dosage")
    };
    unsigned selected_option_id = options[0].id;
    unsigned prev_option_id;
    unsigned watering_type = 0;
    unsigned watering_time;

    State(unsigned id, unsigned dosage, unsigned moisture_percent, unsigned days_to, unsigned days_pass);

    int getContext();
    void setContext(unsigned id);
    void setStateId(int id);
    void setWateringType(int type);
    void setNextWatering(unsigned nxt);
    void setDosage(unsigned dose);
    bool isSettings();
    bool isAutoState();
    bool isManualState();
};


#endif //AUTO_WATERING_STATE_H
