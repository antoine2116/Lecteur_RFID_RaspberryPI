//====================================
// Name        : ReadIrq.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : lit un module MFRC522
//====================================


#include <iostream>
#include <signal.h>	  // Fin, fonction cyclique
#include <unistd.h>	  // Delais pour les alarmes
#include "reader/MFRC522.h"
#include "addons/GestionPinGPIO.h"
#include "wiringPi.h"

#define IRQ     5

MFRC522 mfrc;
bool mesureOk;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

// ************************************
// Lecture d'une carte sur interruption
// ************************************
void irqEnabled(void) {
    // Print UID
    if(mesureOk) {
        for(byte i = 0; i < mfrc.uid.size; ++i) {
            if(mfrc.uid.uidByte[i] < 0x10) {
                cout << " 0";
                cout << hex << (int)mfrc.uid.uidByte[i];
            } else {
                cout << " ";
                cout << hex << (int)mfrc.uid.uidByte[i];
            }
        }
        cout << endl;
        mesureOk = false;
    }
}

// ***********************************
// Fonction lancée cycliquement
// Demande si une mesure est diponible
// ***********************************
void alarmWakeup(int sig) {
    if(mfrc.PICC_IsNewCardPresent()) {
        mfrc.PICC_ReadCardSerial();
        mesureOk = true;
    }
}
void callback() {
    printf("---------------------------deedded\n");
}
int main(){
    // Broche d'interruption
    GestionPinGPIO irq(GPIO24);

    mfrc.PCD_Init();
    irq.in();

    pullUpDnControl(IRQ, PUD_DOWN);
    wiringPiISR(IRQ, INT_EDGE_RISING, callback);

    while (true) {

    }
}