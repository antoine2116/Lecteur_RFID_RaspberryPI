//
// Created by antoo on 10/11/2021.
//

#include "LCD.h"

#define LCD_RS        6
#define LCD_E        19
#define LCD_D4       13
#define LCD_D5       27
#define LCD_D6       22
#define LCD_D7       21

LCD::LCD() {
    fd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
}

void LCD::waiting() {
    lcdClear(fd);
    lcdPosition(fd, 0, 0);
    lcdPrintf(fd, "Waiting ...");
}

void LCD::success() {
    lcdClear(fd);
    lcdPosition(fd, 0, 0);
    lcdPrintf(fd, "Success :)");
    delay(1000);
    waiting();
}

void LCD::error() {
    lcdClear(fd);
    lcdPosition(fd, 0, 0);
    lcdPrintf(fd, "Error :(");
    delay(1000);
    waiting();
}

void LCD::turnOff() {
    lcdClear(fd);
}