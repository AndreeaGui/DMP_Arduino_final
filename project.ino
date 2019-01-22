#include <Servo.h>

#include <SoftwareSerial.h>

#include <NewPing.h>
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200

// Pins of motor 1
#define mpin00 5
#define mpin01 6
// Pins of motor 2
#define mpin10 3
#define mpin11 11

#define txPin 12
#define rxPin A5
SoftwareSerial mySerial(rxPin, txPin);

Servo srv;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int a;

void setup() {
  // configuration of motor pins as output, initially 0
  digitalWrite(mpin00, 0);
  digitalWrite(mpin01, 0);
  digitalWrite(mpin10, 0);
  digitalWrite(mpin11, 0);
  pinMode (mpin00, OUTPUT);
  pinMode (mpin01, OUTPUT);
  pinMode (mpin10, OUTPUT);
  pinMode (mpin11, OUTPUT);
  // LED pin
  pinMode(13, OUTPUT);

  Serial.begin(9600);
  mySerial.begin(9600);
}


// Function to control a motor
// Input: pins m1 and m2, direction and speed
void StartMotor (int m1, int m2, int forward, int speed)
{

  if (speed == 0) // stop
  {
    digitalWrite(m1, 0);
    digitalWrite(m2, 0);
  }
  else
  {
    if (forward)
    {
      digitalWrite(m2, 0);
      analogWrite (m1, speed); // use PWM
    }
    else
    {
      digitalWrite(m1, 0);
      analogWrite(m2, speed);
    }
  }
}


// Safety function
// Commands motors to stop, then delays
void delayStopped(int ms)
{
  StartMotor (mpin00, mpin01, 0, 0);
  StartMotor (mpin10, mpin11, 0, 0);
  delay(ms);
}


// Use of servo
// Set three angles
// When finished, the servo remains in the middle (90 degrees)

void playWithServo(int pin)
{
  srv.attach(pin);
  srv.write(10);
  delay(1000);
  srv.write(170);
  delay(1000);
  srv.write(90);
  delay(1000);
  srv.detach();
}

void playWithServoMyAngle(int pin, int angle)
{
  srv.attach(pin);
  srv.write(angle);
  delay(1000);
  srv.write(180-angle);
  delay(1000);
  srv.write(90);
  delay(1000);
  srv.detach();
}

void PlayWithServoInterrupted(int pin)
{
  srv.attach(pin);
  for(int i = 0; i<180; i = i+10){
    srv.write(i);
    delay(1000);
  }
  srv.write(90);
  delay(1000);
  srv.detach();
}

void PlayWithServoLeftRight(int pin)
{
  srv.attach(pin);
  for(int i = 15; i<90; i = i+15){
    srv.write(i);
    delay(1000);
    srv.write(180-i);
    delay(1000);
  }
  srv.write(90);
  delay(1000);
  srv.detach();
}

void loop() {

  int a;
  char myChar;
  while (mySerial.available())
  {
    myChar = mySerial.read();
    Serial.print(myChar);
    Serial.print('\n');
  }

  if (myChar == 'R') {
    StartMotor(mpin00, mpin01, 1, 128);
    StartMotor(mpin10, mpin11, 0, 128);
  }
  else if (myChar == 'F') {
    StartMotor(mpin00, mpin01, 1, 128);
    StartMotor(mpin10, mpin11, 1, 128);
    /*
    //delay(300);
    Serial.print("Ping: ");
    Serial.print(a);
    Serial.println("cm");
    if (a <= 25 && a > 0) {
      delayStopped(1);
    }*/

  }

  else if (myChar == 'L') {
    StartMotor(mpin00, mpin01, 0, 128);
    StartMotor(mpin10, mpin11, 1, 128);
  }

  else if (myChar == 'B') {
    StartMotor(mpin00, mpin01, 0, 128);
    StartMotor(mpin10, mpin11, 0, 128);
  }

  else if (myChar == 'S') {
    delayStopped(1);
  }

  //asa se opreste dar si cand vrea sa mearga in spate
  delay(300);
  //Serial.print("Ping: ");
  //Serial.print(sonar.ping_cm());
  //Serial.println("cm");
  a = sonar.ping_cm();
  
  if (sonar.ping_cm() <= 25 && sonar.ping_cm() > 0) {
    //delayStopped(1);
    myChar = 'S';
  }


  //servo motor
  //playWithServo(8);
  //playWithServoMyAngle(8, 30);
  PlayWithServoInterrupted(8);
  //PlayWithServoLeftRight(8);
  

}

void testB() {
  while (mySerial.available())
  {
    char myChar = mySerial.read();
    Serial.print(myChar);
  }
}