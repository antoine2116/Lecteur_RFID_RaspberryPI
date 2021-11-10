//
// Created by antoo on 10/11/2021.
//

#include <iostream>
#include <cstring>
#include "RFID.h"

typedef unsigned char BYTE;

RFID::RFID() {
    this->mfrc = new MFRC522();
    this->mfrc->PCD_Init();
}


bool RFID::isReading() {
    if(!(this->mfrc->PICC_IsNewCardPresent())) {

        return false;
    }

    if(!(this->mfrc->PICC_ReadCardSerial())) {
        return false;
    }

    return true;

}

bool RFID::success() {
    byte valid[4] = { 0xFA, 0x38, 0x99, 0x1A };

    int n;

    n = memcmp(valid, this->mfrc->uid.uidByte, sizeof(valid));

    return n == 0;
}
