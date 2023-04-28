#ifndef MYRFID
#define MYRFID

#include <MFRC522.h>

class MyRfid {
  public:
    MyRfid(byte ssPin, byte rstPin);
    void setup();
    String card;
    bool isNewCardPresent();
    void readCardSerial();
  
  private:
    MFRC522 mfrc522;
};

#endif