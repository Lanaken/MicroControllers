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

enum {
  ST0,
  ST1
} states;

volatile boolean intFlag = false;
const int  YELLOW_LEFT = 6;
const int  YELLOW_RIGHT = 5;
int ledState = LOW;
int leftState = LOW;
int rightState = LOW;
int waitState = 0;



unsigned long last_time;


void setup() {
  states = ST0;
  pinMode(RED_2,OUTPUT);
  pinMode(RED,OUTPUT);
  pinMode(SB1_LEFT,INPUT_PULLUP);
  pinMode(SB1_RIGHT,INPUT_PULLUP);
  pinMode(SB2,INPUT_PULLUP);
  pinMode(SB3,INPUT_PULLUP);
  pinMode(YELLOW_LEFT,OUTPUT);
  pinMode(YELLOW_RIGHT,OUTPUT);
 // analogWrite(YELLOW_LEFT,100);
 // digitalWrite(YELLOW_RIGHT,HIGH);
  Serial.begin(9600);

  Timer1.setPeriod(10000);
  Timer1.enableISR(CHANNEL_A);
}

ISR(TIMER1_A) {
  intFlag = true;
}


void loop() {

  if (true == intFlag){
    intFlag = false;
    switch(states)
    {
      case ST0:{
        if (HIGH == digitalRead(SB3))
        {
          if (ledState == LOW) {
          ledState = HIGH;
          } else {
          ledState = LOW;
          }
          digitalWrite(YELLOW_LEFT,ledState);
          digitalWrite(YELLOW_RIGHT,ledState);
        }
        else if (HIGH == digitalRead(SB1_RIGHT))
        {
         digitalWrite(YELLOW_RIGHT,!digitalRead(YELLOW_RIGHT));
         digitalWrite(YELLOW_LEFT,LOW);
         Serial.println("leftState = " + digitalRead(SB1_LEFT));
       }
       else if (HIGH == digitalRead(SB1_LEFT))
       {
        digitalWrite(YELLOW_LEFT,!digitalRead(YELLOW_LEFT));
        digitalWrite(YELLOW_RIGHT,LOW);
        Serial.println("rightState = " + digitalRead(SB1_RIGHT));
       }
       else 
       {
        digitalWrite(YELLOW_LEFT,LOW);
        digitalWrite(YELLOW_RIGHT,LOW);
        }
        waitState = 100;
        states = ST1;
      }
      break;

      case ST1: {
        if (waitState > 0)
        {
          waitState--;
        }
        else states = ST0;
      }
      break;

      default:
      break;
    }
  }

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
