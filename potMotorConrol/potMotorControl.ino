/*
Controlling an BLDC using a Potentiometer 
Creted on 20th July 2019
by Anil Kumar Chavali
*/

#include <Servo.h>

Servo Esc;  // create servo object to control a servo

int potpin = A0;  // analog pin used to connect the potentiometer
int potVal;    // variable to read the value from the analog pin

void setup() {
  Esc.attach(9,1000,2000);  // attaches the servo on pin 9 to the servo object and min max pulse width is defined in ms
}

void loop() {
  potVal = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  potVal = map(potVal, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  Esc.write(potVal);                  // sets the servo position according to the scaled value
                          
}
