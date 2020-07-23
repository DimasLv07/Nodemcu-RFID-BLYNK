#define BLYNK_PRINT Serial

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <MFRC522.h>

char auth[] = "AuthToken";
char ssid[] = "WifiName";
char pass[] = "Password";

#define SDA_PIN 4 //D2
#define RST_PIN 5 //D1

int virtual_State = 0;

MFRC522 mfrc522(SDA_PIN, RST_PIN); 

WidgetLCD lcd(V1);

void setup() 
{
  Serial.begin(115200);
  SPI.begin();      
  Blynk.begin(auth, ssid, pass);
  mfrc522.PCD_Init(); 
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
       
void loop()      
{
  Blynk.run();
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
 
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();  
    
  if(content.substring(1) == "ID UID MU")
          {
            lcd.clear();
            lcd.print(0, 0, "UID for Card is");                                             
            lcd.print(0, 1, content);
            delay(10000);      
          } 
                          
          else
          {                  
            lcd.clear();
            lcd.print(0, 0, "Invalid card");                                  
            lcd.print(0, 1, "Access Denied");
          }                           
          
}   
