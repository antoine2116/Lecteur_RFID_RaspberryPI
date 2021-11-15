//
// Created by antoo on 10/11/2021.
//

#include "LCD.h"

#define LCD_RS  22              //Register select pin
#define LCD_E   24              //Enable Pin
#define LCD_D4  23              //Data pin D4
#define LCD_D5  2               //Data pin D5
#define LCD_D6  3               //Data pin D6
#define LCD_D7  29              // Data pin D7

LCD::LCD() {
    fd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
}

void LCD::waiting() {
//    string dots[3] = {".", "..", "..."};
//
//    for (int i = 0; i < 3; i++) {
//        turnOff();
//
//        string final = "Waiting " + dots[i];
//
//        lcdPrintf(fd, final.c_str());
//        delay(200);
//    }
//        turnOff();
    lcdClear(fd);
    lcdPosition(fd, 0, 0);
    lcdPrintf(fd, "Waiting ...");
}

void LCD::reading() {
//    string dots[3] = {".", "..", "..."};
//
//    for (int i = 0; i < 3; i++) {
//        turnOff();
//
//        string final = "Reading " + dots[i];
//
//        lcdPrintf(fd, final.c_str());
//        delay(200);
//    }
    lcdClear(fd);
    lcdPosition(fd, 0, 0);
    lcdPrintf(fd, "Reading...");
}

void LCD::success() {
    lcdClear(fd);
    lcdPosition(fd, 0, 0);
    lcdPrintf(fd, "Success :)");
}

void LCD::turnOff() {
    lcdClear(fd);
}