#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

//set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servoMotor;

//gate IR Sensors
int IR1 = 7;  
int IR2 = 3;

//slot IR Sensor
const int IR3 = 4; 
const int IR4 = 13; 
const int IR5 = 12; 

//number of slots
int slots = 3;

//check all slots filled or not
int IR3Value, IR4Value, IR5Value;
int IR3Temp, IR4Temp, IR5Temp;

boolean validate = true, validate2 = true;
int gate = 0;

void setup()
{
  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);

  IR3Value = digitalRead(IR3);
  IR4Value = digitalRead(IR4);
  IR5Value = digitalRead(IR5);
  
  IR3Temp = IR3Value;
  IR4Temp = IR4Value;
  IR5Temp = IR5Value;

  servoMotor.attach(8);
  servoMotor.write(90);

  lcd.clear();
  lcd.setCursor (0,0);  
  lcd.print("      SMART  "); 
  lcd.setCursor (0,1);  
  lcd.print(" PARKING SYSTEM "); 
  delay (2000);
  lcd.clear();

  
  lcd.setCursor (0,0);  
  lcd.print("      Team  ");  
  lcd.setCursor (0,1);  
  lcd.print("    Tuffline ");  
  delay (1000);
  lcd.clear();
  
  delay (1000);

}

void loop(){
    
    lcd.setCursor (0,0);
    lcd.print(String("Slots: ") + slots);

    lcd.setCursor (9,0);
    if(IR3Value == 1){
       lcd.print("S1:Fill ");
    }else{
       lcd.print("S1:Free");
    }

    lcd.setCursor (0,1);
    if(IR4Value == 1){
       lcd.print("S2:Fill ");
    }else{
       lcd.print("S2:Free");
    } 

    lcd.setCursor (9,1);
    if(IR5Value == 1){
       lcd.print("S3:Fill ");
    }else{
       lcd.print("S3:Free");
    }

    checkSlots();
    
    delay(1000);

    //if enternce signal equal 0 and there are no any vehicle to exit, the gate will open
    if(digitalRead(IR1) == 0 && digitalRead(IR2) == 1 && validate2 == true)
    {
      if(slots > 0 && slots <= 3){
        lcd.clear();
        lcd.setCursor (0,0);
        lcd.print("     Welcome!  "); 
        lcd.setCursor (0,1);
        lcd.print("Slots Available"); 
        validate = false;
        servoMotor.write(180);
        delay(5000);
        servoMotor.write(90);
        lcd.clear();
        validate = true;
      }else{
        lcd.clear();
        lcd.setCursor (0,0);
        lcd.print("     Sorry!  "); 
        lcd.setCursor (0,1);
        lcd.print("  Parking Full ");
        delay(1000);
        lcd.clear();
      }
    }

    delay(1000);
    
    //if exit signal equal 0 and there are no any vehicle to enter, the gate will open    
    if(digitalRead(IR2) == 0 && digitalRead(IR1) == 1 && validate == true && slots != 3)
      {
        lcd.clear();
        lcd.setCursor (0,0);
        lcd.print("    Good Bye!   "); 
        lcd.setCursor (0,1);
        lcd.print("   Drive Safe   "); 
        validate2 = false;
        servoMotor.write(180);
        delay(5000);
        servoMotor.write(90);
        lcd.clear();
        validate2 = true;
      }

    delay(1000);
}

void checkSlots(){
  if(IR3Value == 1 && IR3Temp != 1)
  {
    if(slots > 0 && slots <= 3){
      slots = slots - 1;
      }
  }
  if(IR4Value == 1 && IR4Temp != 1)
  {
    if(slots > 0 && slots <= 3){
      slots = slots - 1;
      }
  }
  if(IR5Value == 1 && IR5Temp != 1)
  {
    if(slots > 0 && slots <= 3){
      slots = slots - 1;
      }
  }
  if(IR3Value == 0 && IR3Temp != 0)
  {
     if(slots == 0 || slots < 3){
      slots = slots + 1;
      }
  }
  if(IR4Value == 0 && IR4Temp != 0)
  {
     if(slots == 0 || slots < 3){
      slots = slots + 1;
      }
  }
  if(IR5Value == 0 && IR5Temp != 0)
  {
    if(slots == 0 || slots < 3){
      slots = slots + 1;
      }
  }

  IR3Temp = IR3Value;
  IR4Temp = IR4Value;
  IR5Temp = IR5Value;

  IR3Value = digitalRead(IR3);
  IR4Value = digitalRead(IR4);
  IR5Value = digitalRead(IR5);
}
