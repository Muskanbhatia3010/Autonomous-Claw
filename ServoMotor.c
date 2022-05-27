#include <Servo.h>        // include the Servo library for this program

// symbolic constants
#define VCC_PIN 13
#define TRIGGER_PIN 12    // sonar trigger pin will be attached to Arduino pin 12
#define ECHO_PIN 11       // sonar echo pint will be attached to Arduino pin 11
#define GROUND_PIN 10
#define DISTANCE_THRESHOLD 20  // set to 20 cm

// initializations
Servo myservo;  // create servo object to control a servo

// variables
float duration_us, distance_cm;

void setup()
{
  // sonar set up
  Serial. begin(9600);            // set data transmission rate to communicate with computer
  pinMode(ECHO_PIN, INPUT) ;  
  pinMode(TRIGGER_PIN, OUTPUT) ;
  pinMode(GROUND_PIN, OUTPUT);    // tell pin 10 it is going to be an output
  pinMode(VCC_PIN, OUTPUT);       // tell pin 13 it is going to be an output
  digitalWrite(GROUND_PIN,LOW);   // tell pin 10 to output LOW (OV, or ground)
  digitalWrite(VCC_PIN, HIGH) ;   // tell pin 13 to output HIGH (+5V)

  // servo set up
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
  // genrate 10 microsecond pulse to TRIGGER pin
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;

  if(distance_cm < DISTANCE_THRESHOLD)
  {
    myservo.write(180);
    delay(4000);
    myservo.write(90);
    delay(4000);
    myservo.write(180);
  }
  else if(distance_cm >= DISTANCE_THRESHOLD)
  {
    myservo.write(90);
  }

  // print the value to serial monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);


}
