//
// Created by antoo on 10/11/2021.
//

#ifndef RAT_LCD_H
#define RAT_LCD_H

#include <wiringPi.h>
#include <lcd.h>
#include "IDisplay.h"

class LCD: public IDisplay  {
public:
    LCD();
    void waiting();
    void success();
    void error();
    void turnOff();

private:
    int fd;
};


#endif //RAT_LCD_H
