#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
struct can_frame canMsg2;
struct can_frame canMsg3;
struct can_frame canMsg4;
struct can_frame canMsg5;
int buttonValue;
MCP2515 mcp2515(10);

void setup() {
//0x12F, 8, 37 7C 8A DD D4 05 33 06 -0x37, 0x7C, 0x8A, 0xDD, 0xD4, 0x05, 0x33, 0x06 UYANDIRMA
  canMsg1.can_id  = 0x12F;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x37;
  canMsg1.data[1] = 0x7C;
  canMsg1.data[2] = 0x8A;
  canMsg1.data[3] = 0xDD;
  canMsg1.data[4] = 0xD4;
  canMsg1.data[5] = 0x05;
  canMsg1.data[6] = 0x33;
  canMsg1.data[7] = 0x06; 
//0x130, 5, 45 42 69 8F FE - AYDINLATMA
  canMsg2.can_id  = 0x130;
  canMsg2.can_dlc = 5;
  canMsg2.data[0] = 0x55;
  canMsg2.data[1] = 0x40;
  canMsg2.data[2] = 0x21;//22
  canMsg2.data[3] = 0x8F;
  canMsg2.data[4] = 0xFE;
  //0x26E: 0x40, 0x40, 0x3F, 0x50, 0xFF, 0xFF, 0xFF, 0xFF
  canMsg3.can_id  = 0x26E;
  canMsg3.can_dlc = 8;
  canMsg3.data[0] = 0x00;
  canMsg3.data[1] = 0x00;
  canMsg3.data[2] = 0x3F;
  canMsg3.data[3] = 0x50;
  canMsg3.data[4] = 0xFF;
  canMsg3.data[5] = 0xFF;
  canMsg3.data[6] = 0xFF;
  canMsg3.data[7] = 0xFF;
  //0x1D6, 8, 0B 10 00 0D 1F DF 07 F2 - SES KIS
  canMsg4.can_id  = 0x1D6;
  canMsg4.can_dlc = 2;
    
  Serial.begin(115200); 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_16MHZ);  
  mcp2515.setNormalMode();
 } 
void loop() {
  buttonValue = analogRead(A0); //Read analog value from A0 pin
  mcp2515.sendMessage(&canMsg1);
  mcp2515.sendMessage(&canMsg2);
  mcp2515.sendMessage(&canMsg3);
  mcp2515.sendMessage(&canMsg4);
  mcp2515.sendMessage(&canMsg5);
  Serial.println("MESAJ LAR GÖNDERİLDİ");
  delay(20); 
    if (buttonValue>=768 && buttonValue<=769){
                      Serial.println ('+');
                      canMsg4.data[0] = 0xC8;
              }
  else if (buttonValue>=1021 && buttonValue<=1022){
                      Serial.println ('-');
                      canMsg4.data[0] = 0xC4;
  }
  //For 3rd button:ileri
  else if (buttonValue>=568  && buttonValue<=571){
                      Serial.println ('Y');
                      canMsg4.data[0] = 0xE0;
  }
  //For 4th button:GERİ-SRC
  else if (buttonValue>=391  && buttonValue<=394){
                          Serial.println ('A');
                          canMsg4.data[0] = 0x7F;
  }
  //For 5th button:
  else if (buttonValue>=230  && buttonValue<=231){
                         Serial.println ('C');
                         canMsg4.data[0] = 0x11;
  }
  //No button pressed, turn off LEDs
  else if (buttonValue>=0  && buttonValue<=5)
  {
                        canMsg4.data[0] = 0xC0;
                        Serial.println ('P');
  }
  delay(20);
}
