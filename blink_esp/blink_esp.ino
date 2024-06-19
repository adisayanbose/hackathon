#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  myservo.writeMicroseconds(1000);  // sets the servo position to 0 degrees
  delay(1000);                       // waits for 1 second
  myservo.writeMicroseconds(1500);  // sets the servo position to 90 degrees
  delay(1000);                       // waits for 1 second
  myservo.writeMicroseconds(2000);  // sets the servo position to 180 degrees
  delay(1000);                       // waits for 1 second
}
