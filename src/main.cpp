#include <SPI.h>
#include <MFRC522.h>

// #define RST_PIN 9 // Configurable, see typical pin layout above
// #define SS_PIN 10 // Configurable, see typical pin layout above
const int RST_PIN = 22; // Reset pin
const int SS_PIN = 21;  // Slave select pin

bool adding = 0;
bool authorisation = 0;

String masterCard = "72 0C AA 1B";
String cards[] = {"B2 A8 3F 61"};

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

    Serial.print("UID tag : ");
    String content = "";
    byte letter;

    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

    Serial.println();
    content.toUpperCase();

    if (adding)
    {
        Serial.println("Next card will be added .... ");
        //cards[(sizeof(cards) / sizeof(int)) + 1] = content.substring(1); // marche pas ca
    }
    else
    {
        for (byte i = 0; i < sizeof(cards) / sizeof(int); i++)
        {

            if (content.substring(1) == masterCard)
            {
                //adding = 1;
                break;
            }
            else
            {
                if (content.substring(1) == cards[i])
                {
                    authorisation = 1;
                }
            }
        }

        if (authorisation)
        {
            Serial.println("access oui");
        }
        else
        {
            Serial.println("non tu non non");
        }
        authorisation = 0;
    }
    delay(1000);
}