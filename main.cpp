#include <unistd.h>
#include <wiringPi.h>
#include "displays/LCD.h"
#include "reader/MFRC522.h"
#include "displays/LED.h"
#include "reader/RFID.h"

#define BUTTON 4

void delay(int ms) {
    usleep(ms*1000);
}


int main() {
    bool displayIsLed = true;

    wiringPiSetup() ;

    IDisplay *display = new LCD();
    RFID *reader = new RFID();

    while(1) {
        // Switch between LCD and LED
        if (digitalRead(BUTTON)) {
            display->turnOff();

            if (displayIsLed) {
                display = new LCD();
            } else {
                display = new LED();
            }
            displayIsLed = !displayIsLed;
        }


        if (reader->isReading()) {

            display->reading();

            if (reader->success())
                display->success();
            else
                display->error();
        }
        delay(500);
        display->waiting();

    }

    return 0;
}
