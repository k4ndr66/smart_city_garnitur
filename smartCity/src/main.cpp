#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define SPKR 14
#define BUTTON 15
#define LED_PIST 16
#define LED_ALLEY 17

Servo myservo;
int pos = 90;

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int i = 0;
int servoDirection = -1;
int c;
bool isBtnPushed = false;
bool isBlinking = false;
int delayMs;
long t_zero = 0;

void showProduct();
void turnOffLED();

void setup()
{
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.clear();
  lcd.print("Scan a product");
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(SPKR, OUTPUT);
  pinMode(LED_PIST, OUTPUT);
  pinMode(LED_ALLEY, OUTPUT);
  pinMode(BUTTON, INPUT);
  myservo.write(pos);
  digitalWrite(LED_PIST, HIGH);
  digitalWrite(LED_ALLEY, HIGH);
}

void loop(){
  // Serial.println(i);
  // delay(1000);
  // ++i;
              // tell servo to go to position in variable 'pos'
  // delay(15);
  if(isBlinking){
    if((millis() - t_zero) >= delayMs){
      if(digitalRead(LED_PIST)){
        digitalWrite(LED_PIST, LOW);
      }else{
        digitalWrite(LED_PIST, HIGH);
      }
      t_zero = millis();
    }
  }
  if(Serial.available()){
    c = Serial.read();
    switch(c){
      case 'd':
        if(pos > 0)
          pos = pos - 2;
        break;
      case 'a':
        if(pos < 180)
          pos = pos + 2;
        break;
      case 's':
        digitalWrite(SPKR, HIGH);
        delay(50);
        digitalWrite(SPKR, LOW);
        delay(50);
        digitalWrite(SPKR, HIGH);
        delay(50);
        digitalWrite(SPKR, LOW);
        break;
      case '0':
        turnOffLED();
        break;
      case '1':
        isBlinking = true;
        delayMs = 100;
        break;
      case '2':
        isBlinking = true;
        delayMs = 300;
        break;
      case '3':
        isBlinking = true;
        delayMs = 600;
        break;
      default:
        break;
    }
    myservo.write(pos);
    Serial.println(pos);
  }
  if(digitalRead(BUTTON)){
    turnOffLED();
    if(!isBtnPushed){
      isBtnPushed = true;
      digitalWrite(SPKR, HIGH);
      showProduct();
    }
  }else{
    if(isBtnPushed){
      isBtnPushed = false;
      digitalWrite(SPKR, LOW);
    }
  }
}

void showProduct(){
  static int product = 0;
  lcd.clear();
  switch(product){
    case 0:
      lcd.setCursor(0,0);
      lcd.print("Bananas");
      lcd.setCursor(0,1);
      lcd.print("653g      6.13zl");
      delay(100);
      digitalWrite(SPKR, LOW);
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sum:      6.13zl");
      lcd.setCursor(0,1);
      lcd.print("Weight:     653g");
      break;
    case 1:
      lcd.setCursor(0,0);
      lcd.print("Potatos");
      lcd.setCursor(0,1);
      lcd.print("4kg       8.50zl");
      delay(100);
      digitalWrite(SPKR, LOW);
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sum:     14.63zl");
      lcd.setCursor(0,1);
      lcd.print("Weight:    4.6kg");
      break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("Barcode is");
      lcd.setCursor(0,1);
      lcd.print("not detected");
      delay(100);
      digitalWrite(SPKR, LOW);
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sum:     14.63zl");
      lcd.setCursor(0,1);
      lcd.print("Weight:    4.6kg");
      break;
    case 3:
      lcd.setCursor(0,0);
      lcd.print("Stapler");
      lcd.setCursor(0,1);
      lcd.print("1 item   15.00zl");
      delay(100);
      digitalWrite(SPKR, LOW);
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sum:     29.63zl");
      lcd.setCursor(0,1);
      lcd.print("Weight:    4.7kg");
      break;
  }

  product++;
  if(product >= 4){
    product = 0;
  }
}

void turnOffLED(){
  isBlinking = false;
  digitalWrite(LED_PIST, LOW);
}