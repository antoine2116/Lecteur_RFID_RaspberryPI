#include <unistd.h>
#include <wiringPi.h>
#include <iostream>
#include "displays/LCD.h"
#include "reader/MFRC522.h"
#include "displays/LED.h"
#include "reader/RFID.h"
#include "displays/Buzzer.h"

#define BUTTON       4
#define MAX_DIFF   200

enum DisplayTypes { T_LED, T_LCD, T_Buzzer };

// Button
int btnHasBeenPressed = false;
clock_t last = clock(); // Clock au démarrage du programme
double diff = MAX_DIFF; // Initialise une différence de base

// RFID
byte validUid[4] = { 0xFA, 0x38, 0x99, 0x1A };

DisplayTypes currentDisplay = T_LED;


void btnCallback() {
    clock_t current = clock(); // On prend la valeur de la clock
    diff = ((double)current - last) / CLOCKS_PER_SEC * 1000; // Différence entre le dernier click et maintenant
    last = current; // On stock la valeur de la clock dans la variable stockant le dernier clique
    btnHasBeenPressed = true;
}

IDisplay *switchDisplay() {
    if (currentDisplay == T_LED) {
        currentDisplay = T_LCD;
        return new LCD();
    }
    else if (currentDisplay == T_LCD) {
        currentDisplay = T_Buzzer;
        return new Buzzer();
    } else {
        currentDisplay = T_LED;
        return new LED();
    }
}


int main() {
    // Setup Pins
    wiringPiSetup();
    wiringPiISR(BUTTON, INT_EDGE_RISING, btnCallback);

    // Setup RFID
    RFID *reader = new RFID();

    // Setup Display
    IDisplay *display = new LED();

    display->waiting();

    while (true) {
        // Boutton pressed
        if (btnHasBeenPressed && diff >= MAX_DIFF) {
            btnHasBeenPressed = false;
            display->turnOff();
            display = switchDisplay();
        }

        // Look for a card
        if (reader->isReading()) {
            display->reading();

            // Checks if the card is valid
            if (reader->cardIsValid(validUid)) {
                display->success();
            }
        }
        else {
            display->waiting();
        }
    }
}