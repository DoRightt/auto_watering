#ifndef STATE_H
#define STATE_H

//class State {
//public:
//    unsigned short id;
//    unsigned short waterDosage;
//    unsigned short moisture;
//    unsigned short daysToWatering;
//    unsigned short daysPassed;
//    unsigned short contextId = 0;
//    option options[3] {o1, o2, o3};
//    unsigned short selectedOptionId = options[0].id;
//    unsigned short prevOptionId;
//    State(unsigned short stateId, unsigned short dosage, unsigned short moisturePercent, unsigned short daysTo, unsigned short daysPass) {};
//    void setContext(unsigned short id) {};
//};

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
    State(unsigned short stateId, unsigned short dosage, unsigned short moisturePercent, unsigned short daysTo, unsigned short daysPass) {
        id = stateId;
        waterDosage = dosage;
        moisture = moisturePercent;
        daysToWatering = daysTo;
        daysPassed = daysPass;
    }
    setContext(unsigned short id) {
        contextId = id;
    }
    setState(int stateId) {
        digitalWrite(AUTO_LED_PIN, id == AUTO_STATE_ID);
        digitalWrite(MANUAL_LED_PIN, id == MANUAL_STATE_ID);
    }
};

#endif