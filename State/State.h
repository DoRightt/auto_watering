#ifndef STATE_H
#define STATE_H

class State {
public:
    unsigned short id;
    unsigned short waterDosage;
    unsigned short moisture;
    unsigned short daysToWatering;
    unsigned short daysPassed;
    unsigned short contextId = 0;
    option options[3] {o1, o2, o3};
    unsigned short selectedOptionId = options[0].id;
    unsigned short prevOptionId;
    State(unsigned short stateId, unsigned short dosage, unsigned short moisturePercent, unsigned short daysTo, unsigned short daysPass) {};
    void setContext(unsigned short id) {};
};

#endif