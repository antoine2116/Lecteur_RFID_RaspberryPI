//
// Created by antoo on 10/11/2021.
//

#ifndef RAT_LED_H
#define RAT_LED_H
#include "IDisplay.h"

class LED: public IDisplay {
public:
    LED();
    void waiting();
    void reading();
    void success();
    void error();
    void turnOff();

private:
    void blink(int led, int duration, int frequency);
};


#endif //RAT_LED_H
