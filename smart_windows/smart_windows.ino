#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal.h>


#include "DFRobot_mmWave_Radar.h"

#define SoundSensor A0
#define PWM 9
#define button 8

const unsigned long guard_time = 10 * 1000;

Servo servo;
boolean isOpened = false;
boolean isManual = false; 
boolean isNoisy = false;
boolean isEmpty = false;

int firstPress = 0;
int secondPress = 0;
unsigned long guard = 0;

int threshold = 300;

SoftwareSerial mySerial(3, 2);
DFRobot_mmWave_Radar sensor(&mySerial);

const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  Serial.begin(115200);
  mySerial.begin(115200);
  servo.attach(PWM);
  pinMode(button, INPUT);
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  lcd.begin(16, 2);

  sensor.factoryReset();    //Restore to the factory settings   
  sensor.DetRangeCfg(0, 9);    //The detection range is as far as 9m
  sensor.OutputLatency(0, 0);
}

void loop()
{
  // lcd display
  lcd.clear();

  if(isOpened){
    lcd.print("open ");
  }else{
    lcd.print("close");
  }

  lcd.setCursor(9, 0);
  if(isNoisy){
    lcd.print("noisy");
  }else{
    lcd.print("quiet");
  }

  lcd.setCursor(0, 1);
  if(isEmpty){
    lcd.print("empty");
  }else{
    lcd.print("occupied");
  }

  lcd.setCursor(9, 1);
  if(isManual){
    lcd.print("manual");
  }else{
    lcd.print("auto");
  }

  // read sound sensor
  long sum = 0;
  for(int i = 0; i < 32; i++){
    sum += analogRead(SoundSensor);
  }
  sum >>= 5;
  Serial.println(sum);
  if(sum >= threshold){
    isNoisy = true;
  }else{
    isNoisy = false;
  }
  // read mmwave radar
  int Flag  = sensor.readPresenceDetection();
  if(Flag == 0){
    isEmpty = true;
  }else{
    isEmpty = false;
  }

  // adjust windows open and close according to noise and indoor status
  if(!isManual){
    if(isEmpty){
      if(!isOpened){
        // guard algorithm
        if(millis() - guard > guard_time){
          servo.writeMicroseconds(1400);
          delay(500);
          servo.writeMicroseconds(1500);
          isOpened = true;
          guard = millis();
        }
      }
    }else{
      if(isNoisy){
        if(isOpened){
          if(millis() - guard > guard_time){
            servo.writeMicroseconds(1600);
            delay(500);
            servo.writeMicroseconds(1500);
            isOpened = false;
            guard = millis();
            Serial.print("guardtime: ");
            Serial.println(millis() - guard);
            Serial.print("guard: ");
            Serial.println(guard);
          }
          
        }
      }else{
        if(!isOpened){
          if(millis() - guard > guard_time){
            servo.writeMicroseconds(1400);
            delay(500);
            servo.writeMicroseconds(1500);
            isOpened = true;
            guard = millis();
          }
        }
      }
    }
  }

  // read button action
  if(digitalRead == HIGH){
    int time = millis();
    if(secondPress <= firstPress && time > firstPress){
      firstPress = time;
    }else if(secondPress < firstPress && firstPress > time){
      secondPress = time;
      if(secondPress - firstPress < 150){
        // change the status
        isManual = !isManual;
      }else{
        firstPress = time;
        // manually control
        if(isManual){
          if(isOpened){
            servo.writeMicroseconds(1600);
            delay(500);
            servo.writeMicroseconds(1500);
            isOpened = false;
          }else{
            servo.writeMicroseconds(1400);
            delay(500);
            servo.writeMicroseconds(1500);
            isOpened = true;
          }
        }
      }
    }
  }

  delay(10);
}