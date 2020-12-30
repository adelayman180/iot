#include <Servo.h>
#include <NewPing.h>

//L298N control pins
#define LeftMotorForward 7
#define LeftMotorBackward 6
#define RightMotorForward 5
#define RightMotorBackward 4

//UltraSonic sensor pins
#define trig_pin A1 //trig
#define echo_pin A2 //echo

int maximum_distance = 200;
boolean goForward = false;
int distance = 100;
char turnOn = 0;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //servo name


void setup(){
  
  Serial.begin(9600);

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  servo_motor.attach(10); //our servo pin

  servo_motor.write(90);
  
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){
  if(Serial.available()){

    turnOn = Serial.read();
   if(turnOn == '1'){

      int distanceRight = 0;
      int distanceLeft = 0;
      delay(50);
    
      if (distance <= 35){
        moveStop();
        delay(300);
        moveBackward();
        delay(400);
        moveStop();
        delay(300);
        distanceRight = lookRight();
        delay(300);
        distanceLeft = lookLeft();
        delay(300);
    
        if (distance >= distanceLeft){
          turnRight();
          moveStop();
        }
        else{
          turnLeft();
          moveStop();
        }
      }
      else{
        moveForward(); 
      }
        distance = readPing();
  }else if(turnOn == '0'){
    moveStop();
    delay(200);
    goForward = false;
    distance = 100;
    }
  }
}

int lookRight(){
  servo_motor.write(20);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){

  if(!goForward){

    goForward=true;
    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
  }
}

void moveBackward(){

  goForward=false;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}

void turnRight(){

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(250);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
 
  
  
}

void turnLeft(){

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(250);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
