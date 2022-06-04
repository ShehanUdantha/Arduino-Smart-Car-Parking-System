#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servoMotor;

//gate sensors
int IR1 = 7; 
int IR2 = 4; 

//slots sensors
int IR3 = 2; 
int IR4 = 3;
int IR5 = 5; 
int IR6 = 6;

//number of slots
int slots = 4;

//count filling slots
int counter = counter + slots;

//check all slots filled or not
int S1 = 0, S2 = 0, S3 = 0, S4 = 0;

//led bulbs and ldr
int LEDPins = 12;
int LDRPin = A0;

void setup()
{
  lcd.init();
  lcd.backlight();
  
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  pinMode(IR6, INPUT);

  servoMotor.attach(9);
  servoMotor.write(90);
  
  pinMode(LDRPin, INPUT);
  pinMode(LEDPins, OUTPUT);
  
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
  
  Serial.begin(9600); 

  delay (1000);

}
void loop(){
  
    Read_Sensor();

    lcd.setCursor (0,0);
    if(S1 == 1){
      lcd.print("S1:Fill ");
    }else{
      lcd.print("S1:Free");
    }

    lcd.setCursor (9,0);
    if(S2 == 1){
       lcd.print("S2:Fill ");
    }else{
       lcd.print("S2:Free");
    }

    lcd.setCursor (0,1);
    if(S3 == 1){
       lcd.print("S3:Fill ");
    }else{
       lcd.print("S3:Free");
    } 

    lcd.setCursor (9,1);
    if(S4 == 1){
       lcd.print("S4:Fill ");
    }else{
       lcd.print("S4:Free");
    }

    delay(1000);
  
    //if enternce signal equal 1 and there are no any vehicle to exit, the gate will open
    if(digitalRead(IR1) == 1 && digitalRead(IR2) == 0)
    {
      if(counter > 0 && counter <= 4){
        lcd.clear();
        lcd.setCursor (0,0);
        lcd.print("     Welcome!  "); 
        lcd.setCursor (0,1);
        lcd.print("Slots Available"); 
        servoMotor.write(0);
        counter = counter - 1;
        Serial.println(counter); 
        Serial.println("enternceGate");
        delay(1000);
        lcd.clear();
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
    if(digitalRead(IR2) == 0)
    {
      delay(3000);
      servoMotor.write(90);
    }
  
    //if exit signal equal 1 and there are no any vehicle to enter, the gate will open
    if(digitalRead(IR2) == 1 && digitalRead(IR1) == 0)
    {
      lcd.clear();
      lcd.setCursor (0,0);
      lcd.print("    Good Bye!   "); 
      lcd.setCursor (0,1);
      lcd.print("   Drive Safe   "); 
      servoMotor.write(0);
      if(counter >= 4){
        counter = 4;
      }else{
        counter = counter + 1;
      }
      Serial.println(counter); 
      Serial.println("excitGate");
      delay(1000);
      lcd.clear();
    }
    if(digitalRead(IR1) == 0)
    {
      delay(3000);
      servoMotor.write(90);
    }
  
  //LED gets brighter the darker it is at the ldr sensor
  int data = analogRead(LDRPin);
  if(data <= 200){
    digitalWrite(LEDPins, HIGH);
  }else{
    digitalWrite(LEDPins, LOW);
  }
}

void Read_Sensor() {
  S1 = 0, S2 = 0, S3 = 0, S4 = 0;

  if (digitalRead(IR3) == 1) {
    S1 = 1;
  }
  if (digitalRead(IR4) == 1) {
    S2 = 1;
  }
  if (digitalRead(IR5) == 1) {
    S3 = 1;
  }
  if (digitalRead(IR6) == 1) {
    S4 = 1;
  }

}
