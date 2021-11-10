//
// Created by antoo on 10/11/2021.
//

#include <cstdio>
#include <cstring>
#include "LCD.h"
#include "iostream"

#define LCD_RS  22              //Register select pin
#define LCD_E   24              //Enable Pin
#define LCD_D4  23              //Data pin D4
#define LCD_D5  2               //Data pin D5
#define LCD_D6  3               //Data pin D6
#define LCD_D7  29              // Data pin D7

using namespace std;

LCD::LCD() {
    this->fd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
}

void LCD::waiting() {
    string dots[3] = {".", "..", "..."};

    for (int i = 0; i < 3; i++) {
        turnOff();

        string final = "Waiting " + dots[i];

        lcdPrintf(this->fd, final.c_str());
        delay(200);
    }
}

void LCD::reading() {
    string dots[3] = {".", "..", "..."};

    for (int i = 0; i < 3; i++) {
        turnOff();

        string final = "Reading " + dots[i];

        lcdPrintf(this->fd, final.c_str());
        delay(200);
    }
}

void LCD::success() {
    lcdClear(this->fd);
    lcdPosition(this->fd, 0, 0);
    lcdPrintf(this->fd, "Success :)");
    delay(1000);
}

void LCD::error() {
    lcdClear(this->fd);
    lcdPosition(this->fd, 0, 0);
    lcdPrintf(this->fd, "Error :(");
    delay(1000);
}

void LCD::turnOff() {
    lcdClear(this->fd);
}