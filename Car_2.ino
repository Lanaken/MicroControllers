#include "GyverTimers.h"

#define thirtyPercent 76
#define brakes 306
#define SB1_LEFT 10
#define SB1_RIGHT 11
#define SB2 2
#define SB3 9
#define RP1 1


#define RED 8
#define RED_2 7

const int  YELLOW_LEFT = 6;
const int  YELLOW_RIGHT = 5;
int ledState = LOW;
int leftState = LOW;
int rightState = LOW;



unsigned long last_time;

int timer(int pin,int state){
  Serial.println(last_time);
  Serial.println(millis());
   if (millis() - last_time >= 1000){
    last_time = millis();
    if (state == LOW) {
      state = HIGH;
      } 
      else 
      {
        state = LOW;
      }
      digitalWrite(pin,state);
  }
  return state;
}

void setup() {
  pinMode(RED_2,OUTPUT);
  pinMode(RED,OUTPUT);
  pinMode(SB1_LEFT,INPUT);
  pinMode(SB1_RIGHT,INPUT);
  pinMode(SB2,INPUT_PULLUP);
  pinMode(SB3,INPUT);
  pinMode(YELLOW_LEFT,OUTPUT);
  pinMode(YELLOW_RIGHT,OUTPUT);
 // analogWrite(YELLOW_LEFT,100);
 // digitalWrite(YELLOW_RIGHT,HIGH);
  Serial.begin(9600);

  Timer1.setPeriod(1000000);
  Timer1.enableISR(CHANNEL_A);
  Timer0.setPeriod(1000000);
  Timer0.enableISR(CHANNEL_A);
  Timer2.setPeriod(1000000);
  Timer2.enableISR(CHANNEL_A);
}

ISR(TIMER1_A) {
  Serial.println("1");
  digitalWrite(YELLOW_LEFT,!digitalRead(YELLOW_LEFT));
  digitalWrite(YELLOW_RIGHT,!digitalRead(YELLOW_RIGHT));
}

ISR(TIMER0_A) {
  Serial.println("2");
  digitalWrite(YELLOW_LEFT,!digitalRead(YELLOW_LEFT));
}

ISR(TIMER2_A) {
  Serial.println("3");
  digitalWrite(YELLOW_RIGHT,!digitalRead(YELLOW_RIGHT));
}

void loop() {

 /* if (HIGH == digitalRead(SB3))
  {
    if (millis() - last_time >= 1000)
    {
      last_time = millis();
      if (ledState == LOW) {
      ledState = HIGH;
      } else {
      ledState = LOW;
      }
      digitalWrite(YELLOW_LEFT,ledState);
      digitalWrite(YELLOW_RIGHT,ledState);
    }
  }
  else if (HIGH == digitalRead(SB1_LEFT))
       {
        digitalWrite(YELLOW_RIGHT,LOW);
        leftState = timer(YELLOW_LEFT,leftState);
        Serial.println("leftState = " + digitalRead(SB1_LEFT));
       }
  else if (HIGH == digitalRead(SB1_RIGHT))
       {
        digitalWrite(YELLOW_LEFT,LOW);
        rightState = timer(YELLOW_RIGHT,rightState);
        Serial.println("rightState = " + rightState);
       }
  else 
  {
   digitalWrite(YELLOW_LEFT,LOW);
   digitalWrite(YELLOW_RIGHT,LOW);
  }*/
  //Serial.println(analogRead(SB1));
   if (brakes < analogRead(RP1))
  {
    digitalWrite(RED_2,HIGH);
    analogWrite(RED,1023);
  } else if (LOW == digitalRead(SB2))
         {
          digitalWrite(RED_2,LOW);
          analogWrite(RED,0);
         }
         else 
         {
          digitalWrite(RED_2,LOW);
          analogWrite(RED,thirtyPercent);
         }

}
