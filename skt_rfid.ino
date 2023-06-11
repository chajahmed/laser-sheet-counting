//https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <HardwareSerial.h>
#define relay PA9
LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display
HardwareSerial rfid(PA3, PA2);
bool rfid_chk = false;
String input;
String rfid_num ="19000A09F9E3";
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(PA3,INPUT);
pinMode(relay, OUTPUT); digitalWrite(relay, HIGH);
rfid.begin(9600);
Wire.setSDA(PB9);
Wire.setSCL(PB8);
Wire.begin();
Wire.beginTransmission(0x27);
lcd.begin(16,4); 
lcd.setBacklight(255);
lcd.home(); 
lcd.clear();
}
void loop() {
  // put your main code here, to run repeatedly:
  main_dis();
    if(rfid.available())
{
  input = rfid.readString();
  if (input) 
{
        if (input == rfid_num)
        {    
          rfid_chk = true;
          rfid.flush();
        }
            if(rfid_chk == true)
            {  lcd.clear();
               digitalWrite(relay, LOW);
               lcd.setCursor(0,0);
              lcd.print("    Welcome");
              lcd.setCursor(0,1);
              lcd.print("Door is opening");
              delay(2000);
              digitalWrite(relay, HIGH);
              lcd.begin(16,4);
              input = " ";
              rfid_chk = false;
            }
            else
            { lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("XXXXXXXXXXXXXXXX");
              lcd.setCursor(0,1);
              lcd.print("    Wrong ID ");
              lcd.setCursor(0,2);
              lcd.print("   Try Again");
               delay(3000);
              lcd.begin(16,4);
              input = " ";
            }
  
}
}
}
void main_dis()
{
  lcd.setCursor(0,0);
  lcd.print("Security System");
  lcd.setCursor(0,1);
  lcd.print("Swipe Your Card");
}
