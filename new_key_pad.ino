#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleKeypad.h>
LiquidCrystal_I2C lcd(0x27, 16, 4);
char key=0;
int key1=0;
int total=0;
int key2=0;
const byte nb_rows = 4;                         // four rows
const byte nb_cols = 4;                         // four columns
char key_chars[nb_rows][nb_cols] = {            // The symbols of the keys
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[nb_rows] = { 6,7,8,9 };           // The pins where the rows are connected
byte colPins[nb_cols] = {2,3,4,5};          // The pins where the columns are connected
SimpleKeypad kp1((char*)key_chars, rowPins, colPins, nb_rows, nb_cols);   // New keypad called kp1
void setup()
{ 
  lcd.init();
  lcd.backlight();
  }
  void loop()
  {  
    menu();
  }
  //****************************** Menu ******************************
void menu()
{ int i=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("-LASER  MACHINE-");
  lcd.setCursor(0,1);
  lcd.print("PRESS A:ON WORK");
  lcd.setCursor(-4,2);
  lcd.print("PRESS B:OFF WORK");
 while(i == 0)
  { char key = kp1.getKey();
  if(key && (key == 'A' || key == 'B'))
  {
    if(key == 'A')
    { lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("-LASER  MACHINE-");
  lcd.setCursor(0,1);
  lcd.print("ENTER SHEETS:");
  lcd.setCursor(-4,2);
  lcd.print("TOTAL:");
  lcd.setCursor(-4,3);
  lcd.print("PRESS B:OFF WORK");
     set_check();
  }
  if(key == 'B')
    { 
        absent();
    }
  }
 }
}
//************************** set_check *****************************
void set_check()
{   int k = 0;
 while(k == 0)
  { char key = ' ';
  key = kp1.getKey();
     if(key) 
     {  
        if((key) && (key == '1'|| key == '2' || key == '3' || key == '4'))
       { 
        lcd.setCursor(13,1);
        lcd.print(key);
        key1 = key - '0';
       }
     if((key) && (key == '#'))
  {
  key = ' ';
  lcd.setCursor(13,1);
  lcd.print(key);
  total = key1+total;
  lcd.setCursor(2,2);
  lcd.print(total);
  key1=0;
  }
  if(key == 'D')
  {
     key = ' ';
   lcd.setCursor(13,1);
  lcd.print(key);
  }
  if(key == 'B')
  {
    absent();
  }
   }
  }} 
  //*********************************************** Absent ***********************************
void absent()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("-LASER  MACHINE-");
  lcd.setCursor(0,1);
  lcd.print("OPERATOR IS NOT");
  lcd.setCursor(0,2);
  lcd.print("AVAILABLE");
  lcd.setCursor(-4,3);
  lcd.print("PRESS C TO BACK");
  key = kp1.getKey();
  int j = 0;
  while(j == 0)
  {
    char key = kp1.getKey();
    if (key &&(key == 'C'))
     {
      menu();
      }
  }    
}
