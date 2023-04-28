#include "myRfid.h"

MyRfid::MyRfid(byte ssPin, byte rstPin) : mfrc522(ssPin, rstPin) {}

void MyRfid::setup() {
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init();
}

bool MyRfid::isNewCardPresent() {
  return mfrc522.PICC_IsNewCardPresent();
}

void MyRfid::readCardSerial() {
  card = "";
  mfrc522.PICC_ReadCardSerial(); // card is read
  for (byte i = 0; i < mfrc522.uid.size; i++){
    card.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    card.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  card.toUpperCase();
}