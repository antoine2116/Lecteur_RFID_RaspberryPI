//
// Created by antoo on 10/11/2021.
//

#ifndef RAT_RFID_H
#define RAT_RFID_H

#include "MFRC522.h"

class RFID {
public:
    RFID();
    bool isReading();
    bool success();

private:
    MFRC522 *mfrc;
};


#endif //RAT_RFID_H