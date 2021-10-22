#include <AFMotor.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

byte pressCount;
unsigned long balance;
volatile unsigned long pulseTime;

AF_DCMotor motor(2);

void setup(){
  attachInterrupt(digitalPinToInterrupt(2), coinInterrupt, RISING);
  //attachInterrupt(digitalPinToInterrupt(3), stoping, RISING);
  //pinMode(3,INPUT);
  pinMode(5,INPUT);
  Serial.begin(9600);
  motor.setSpeed(255);
  lcd.begin(16, 2);
  
  motor.run(FORWARD);
  delay(2000);
  motor.run(RELEASE);
  
  lcd.setCursor(0,0);
  lcd.print("WELCOME to  MASK");
  lcd.setCursor(0,1);
  lcd.print("VENDING  MACHINE");
  delay(2000);
  lcd.clear();

  lcd.setCursor(4,0);
  lcd.print("Made by:");
  lcd.setCursor(0,1);
  lcd.print("K    J    N    P");
  delay(2000);
  lcd.clear();

  motor.run(FORWARD);
  delay(2000);
  motor.run(RELEASE);
}
  
void loop(){
  if(digitalRead(5) == 0){
 
    lcd.setCursor(0,0);
    lcd.print("Please insert");
    lcd.setCursor(0,1);
    lcd.print("2x Rs.5 or Rs.10");
  
    if (balance==5 && millis()-pulseTime < 10000){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Please insert");
      lcd.setCursor(0,1);
      lcd.print("Rs.5 more!!");
      delay(1000);
      lcd.clear();
    }
    if (balance==5 && millis()-pulseTime > 10000){
      balance=0;
    }
    
    if(balance==10){
      lcd.setCursor(0,0);
      lcd.print("Balance is 10");
      delay(2000);
      lcd.clear();
      Serial.println("Rs.10 collected!");
      Serial.println("Balance : "+(String)balance);
      lcd.setCursor(0,0);
      lcd.print("Motor will run");
      delay(2000);
      lcd.clear();
      motor.run(FORWARD);
      delay(5000);
      motor.run(RELEASE);
      lcd.setCursor(0,0);
      lcd.print("Please collect");
      lcd.setCursor(0,1);
      lcd.print("your Mask!!");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Thank You!!");
      delay(2000);
      lcd.clear();
//      lcd.setCursor(0,0);
//      lcd.print("Thank You!!");
//      delay(2000);
      balance=0;
//      break;
    }
  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("NO MASKS");
    lcd.setCursor(0,1);
    lcd.print("AVAILABLE");
    delay(5000);
  }
}

void stoping(){
  Serial.println("Motor Stopped");
  motor.run(RELEASE);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Please collect");
  lcd.setCursor(0,1);
  lcd.print("your Mask!!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Thank You!!");
  delay(2000);
  lcd.clear();
}

void coinInterrupt(){
  balance+=5;
  pulseTime = millis();
}
