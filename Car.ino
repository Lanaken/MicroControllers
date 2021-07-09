#define thirtyPercent 76
#define brakes 306
#define SB1 0
#define SB2 2
#define SB3 8
#define RP1 1

#define RED 9
#define RED_2 7
#define WHITE 9

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
  pinMode(SB2,INPUT_PULLUP);
  pinMode(SB3,INPUT_PULLUP);
  pinMode(YELLOW_LEFT,OUTPUT);
  pinMode(YELLOW_RIGHT,OUTPUT);
 // analogWrite(YELLOW_LEFT,100);
 // digitalWrite(YELLOW_RIGHT,HIGH);
  Serial.begin(9600);
}

void loop() {

  if (HIGH == digitalRead(SB3))
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
  else if (0 == analogRead(SB1))
       {
        leftState = timer(YELLOW_LEFT,leftState);
       }
  else if (1023 == analogRead(SB1))
       {
        rightState = timer(YELLOW_RIGHT,rightState);
       }
  else 
  {
   digitalWrite(YELLOW_LEFT,LOW);
   digitalWrite(YELLOW_RIGHT,LOW);
  }
  Serial.println(analogRead(SB1));
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
