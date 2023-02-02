#include <SPI.h>
#include <MFRC522.h>

// #define RST_PIN 9 // Configurable, see typical pin layout above
// #define SS_PIN 10 // Configurable, see typical pin layout above
const int RST_PIN = 22; // Reset pin
const int SS_PIN = 21;  // Slave select pin

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

/**
 * Initialize.
 */
void setup()
{

    Serial.begin(115200); // Initialize serial communications with the PC
    while (!Serial)
        ; // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

    SPI.begin(); // Init SPI bus
    mfrc522.PCD_Init();
    delay(10);
    mfrc522.PCD_DumpVersionToSerial();
    Serial.println("Lessgo scan...");
}

/**
 * Main loop.
 */
void loop()
{
    if (!mfrc522.PICC_IsNewCardPresent()) { return; }

    if (!mfrc522.PICC_ReadCardSerial()) { return; }

    String card = "";

    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        card.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        card.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

    card.toUpperCase();
    Serial.print("UID tag : ");
    Serial.println(card);

    delay(1000);
}