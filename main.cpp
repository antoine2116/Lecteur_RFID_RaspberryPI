#include <unistd.h>
#include <wiringPi.h>
#include <iostream>
#include <csignal>
#include <cstring>
#include "displays/LCD.h"
#include "reader/MFRC522.h"
#include "displays/LED.h"
#include "displays/Buzzer.h"
#include "addons/GestionPinGPIO.h"

#define BUTTON             23
#define MAX_DIFF_BTN      200
#define MAX_DIFF_RFID     200

// Button
int btnHasBeenPressed = false;
clock_t last_btn_press = clock(); // Clock au démarrage du programme
double diff_btn = MAX_DIFF_BTN; // Initialise une différence de base

// RFID
MFRC522 mfrc;
GestionPinGPIO irq(GPIO24);
byte validUid[4] = { 0xFA, 0x38, 0x99, 0x1A };
bool mesureOk = false;
bool cardIsPresent = false;
clock_t last_mesure_rfid = clock(); // Clock au démarrage du programme
double diff_rfid = MAX_DIFF_RFID; // Initialise une différence de base

// Display
IDisplay *display = new Buzzer();

// *********************************************
// Lecture d'un click du bouton sur interruption
// *********************************************
void btnPressed() {
    clock_t current = clock(); // On prend la valeur de la clock
    diff_btn = ((double)current - last_btn_press) / CLOCKS_PER_SEC * 1000; // Différence entre le dernier click et maintenant
    last_btn_press = current; // On stock la valeur de la clock dans la variable stockant le dernier clique
    btnHasBeenPressed = true;
}

// ************************************
// Lecture d'une carte sur interruption
// ************************************
void irqEnabled() {
    if(mesureOk) {
        clock_t current = clock(); // On prend la valeur de la clock
        diff_rfid = ((double)current - last_mesure_rfid) / CLOCKS_PER_SEC * 1000; // Différence entre le dernier click et maintenant
        last_mesure_rfid = current; // On stock la valeur de la clock dans la variable stockant le dernier clique

        cardIsPresent = true;
        mesureOk = false;
    }
}

// ***********************************
// Vérifie la validité de la carte lue
// ***********************************
bool cardIsValid() {
    return memcmp(validUid, mfrc.uid.uidByte, sizeof(validUid)) == 0;
}

// *****************************************************************
// Fonction lancée cycliquement, demande si une mesure est diponible
// *****************************************************************
void alarmWakeup(int sig) {
    if(mfrc.PICC_IsNewCardPresent()) {
        mfrc.PICC_ReadCardSerial();
        mesureOk = true;
    }
}

// ****************************************
// Permet de vérifier le type de d'un objet
// ****************************************
template<typename Base, typename T>
inline bool instanceof(const T*) {
    return std::is_base_of<Base, T>::value;
}

// ***************************************************************************
// Change de display en fonction de l'état acutelle du système (parttern état)
// ***************************************************************************
void switchDisplay() {
    if (instanceof<LED>(display)) {
        display = new LCD();
    }
    else if (instanceof<LCD>(display)) {
        display = new Buzzer();
    }
    else if (instanceof<Buzzer>(display)) {
        display = new LED();
    }
}

int main() {
    // Initialisation du lecteur RFID
    mfrc.PCD_Init();

    // Gestion de l'interruption
    irq.in();
    irq.fctInterrupt(Rising, &irqEnabled);

    // Lancement cyclique d'un test de mesure toutes les millisecondes
    signal(SIGALRM, alarmWakeup);
    ualarm(50000, 50000);

    display->waiting();

    // Gestion de l'interruption bouton
    wiringPiISR(BUTTON, INT_EDGE_RISING, btnPressed);

    while (true) {
        // Boutton pressed
        if (btnHasBeenPressed && diff_btn >= MAX_DIFF_BTN) {
            btnHasBeenPressed = false;
            display->turnOff();
            switchDisplay();
            display->waiting();
        }

        // Gestion de l'interruption IRQ
        if (cardIsPresent && diff_rfid >= MAX_DIFF_RFID) {
            if (cardIsValid()) {
                display->success();
            } else {
                display->error();
            }
            cardIsPresent = false;
        }
    }
}