//https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#define relay PA9
LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display
HardwareSerial rfid(PA3, PA2);
bool rfid_chk = false;
String input;
String rfid_num[5] = {" "," "," "," "};
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(PA3,INPUT);
pinMode(relay, OUTPUT); digitalWrite(relay, HIGH);
rfid.begin(9600);
Wire.setSDA(PB9);
Wire.setSCL(PB8);
Wire.begin();
lcd.begin(16, 4); 
lcd.setBacklight(255);
lcd.home(); 
lcd.clear();
}
void loop() {
  // put your main code here, to run repeatedly:
  main_dis();
    if(rfid.available() == 12)
{
  input = rfid.readString();
  if (input) 
{
      Serial.println(input);
            for (int i = 0; i < 4; i++) {
        if (input == rfid_nm[i])
        {    
          rfid_chk = true;
          rfid.flush();
        }
            }
            if(rfid_chk == true)
            {
               digitalWrite(relay, LOW);
               lcd.setCursor(0,0);
              lcd.print("door is opening");
              lcd.setCursor(0,1);
              lcd.print("Thanx");
              delay(2000);
              rfid_chk = false;
            }
            else
            {
              lcd.setCursor(0,0);
              lcd.print("XXXXXXXXXXXXXX");
              lcd.setCursor(0,1);
              lcd.print(" Wrong ID ");
              lcd.setCursor(0,2);
              lcd.print("Try Again");
              delay(3000);
            }
}
}
}
void main_dis()
{
  lcd.setCursor(0,0);
  lcd.print("Security System");
  lcd.setCursor(0,1);
  lcd.print("Please Swipe Your Card");
}
