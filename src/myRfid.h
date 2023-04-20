#ifndef MYRFID
#define MYRFID

#include <MFRC522.h>

class MyRfid {
  public:
    MyRfid(byte ssPin, byte rstPin);
    void setup();
    bool isNewCardPresent();
    String readCardSerial();
  
  private:
    MFRC522 mfrc522;
};

#endif