//
// Created by antoo on 11/15/2021.
//

#ifndef RAT_BUZZER_H
#define RAT_BUZZER_H


#include "IDisplay.h"

class Buzzer: public IDisplay  {
public:
    Buzzer();
    void waiting();
    void success();
    void error();
    void turnOff();
};

#endif //RAT_BUZZER_H
