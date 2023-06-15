#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void printString(String string);

void setup()
{
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.clear();
  lcd.print("12345678901234567890");
  lcd.setCursor(0,1);
  lcd.print("-0-0-0-0-0");
}

void loop(){
  
}