/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
  
  modified 8 Sep 2016
  by Colby Newman
*/


int LEFT_WHEEL = 5;
int RIGHT_WHEEL = 3;

int RIGHT_RECEIVER = A7;
int MIDDLE_RECEIVER = A4;
int LEFT_RECEIVER = A1;

int BLUE_LED = 7;
int GREEN_LED = 8; 
int RED_LED = 4;

int LEFT_WHITE = 83;
int MIDDLE_WHITE = 85;
int RIGHT_WHITE = 60;

int LEFT_BLACK = 40;
int MIDDLE_BLACK = 25;
int RIGHT_BLACK = 10;

int LEFT_NORM = LEFT_WHITE - LEFT_BLACK;
int MIDDLE_NORM = MIDDLE_WHITE - MIDDLE_BLACK;
int RIGHT_NORM = RIGHT_WHITE - RIGHT_BLACK;


byte right_high = 0;
byte middle_high = 0;
byte left_high = 0;

float right_val;
float middle_val;
float left_val;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize analog pins left n right wheels as an output.
  pinMode(LEFT_WHEEL, OUTPUT);
  pinMode(RIGHT_WHEEL, OUTPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  

  analogWrite(LEFT_WHEEL, 205); //out of 255
  analogWrite(RIGHT_WHEEL, 255);
  
}

void STOP(){
  analogWrite(LEFT_WHEEL, 0); //out of 255
  analogWrite(RIGHT_WHEEL, 0);

  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
 /* delay(50);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  delay(50);  */
  
}

void START(){
  analogWrite(LEFT_WHEEL, 200); //out of 255
   analogWrite(RIGHT_WHEEL, 200);
   Serial.print("START");
 }

void TURN_LEFT(){
  analogWrite(LEFT_WHEEL, 40); //out of 255
   analogWrite(RIGHT_WHEEL, 60);
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
   
  }

void TURN_RIGHT(){
  analogWrite(LEFT_WHEEL, 70); //out of 255
   analogWrite(RIGHT_WHEEL, 40);
 digitalWrite(RED_LED, HIGH);
 digitalWrite(GREEN_LED, LOW);
 digitalWrite(BLUE_LED, LOW);
  }

void GO_STRAIGHT(){
  analogWrite(RIGHT_WHEEL, 60);
  analogWrite(LEFT_WHEEL, 60);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  }

int t = 0;

// the loop function runs over and over again forever
void loop() {
  
  
  left_val = (analogRead(LEFT_RECEIVER)-LEFT_BLACK)*1.0/LEFT_NORM;
  middle_val = (analogRead(MIDDLE_RECEIVER)-MIDDLE_BLACK)*1.0/MIDDLE_NORM;
  right_val = (analogRead(RIGHT_RECEIVER)-RIGHT_BLACK)*1.0/RIGHT_NORM;
  
  
   Serial.print(left_val);
   Serial.print(" ");
   Serial.print(middle_val);
   Serial.print(" ");
   Serial.print(right_val);
   Serial.print(" ");
   
  


  float left_bias = left_val - middle_val;
  float right_bias = right_val - middle_val;

  int bias = (int)(40*(left_bias-right_bias));

Serial.print(bias);
Serial.println();
if((left_val+middle_val+right_val) > 1.4)
  if (t<20){
    if(bias < -12) TURN_LEFT();
    else if(bias > 8) TURN_RIGHT();
    else  GO_STRAIGHT();
  }
  else {
    t=0; 
    START();
    }
    
  t++;

    delay(30);

 /* analogWrite(LEFT_WHEEL, 60+bias); //out of 255
  analogWrite(RIGHT_WHEEL, 60-bias); */

  

 
  if((left_val+middle_val+right_val) < 1.4){
    STOP();
  } else {
    digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  }

 
   
}
