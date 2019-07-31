/*
Controlling an BLDC using Serial Monitor
Created on 26th July 2019
by Anil Kumar Chavali

100% sure it works!! ;;;;; )))))
WARNING!!!! : Dont attach the live wire from the BEC only grd and signal to arduino, I just burnt an ESC (indirectly because of this)
*/

#include <Servo.h>

Servo Esc;  // create servo object to control a servo

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

int integerFromPC = 0;          //Idea is to send a value between 0 to 100 signifying percent of motor speed
boolean newData = false;


int serialVal =0;    // variable to map the percent between 0 to 180

//-----------------------------
//
void setup() 
{
  //Serial
  Serial.begin(9600);
  Serial.println("Expecting 1 piece of data - an integer between 0-100");
  Serial.println("Enter data in this style <45;>  ");
  Serial.println();

  //Servo
  Esc.attach(9,1000,2000);  // attaches the servo on pin 9 to the servo object and min max pulse width is defined in ms
}


//-----------------------------
//

void loop() 
{
    //Read the value from serial (value between 0 and 100)
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        
        newData = false;
    }
           
  Esc.write(serialVal);                  // sets the servo position according to the scaled value
  Serial.println(serialVal);
  
                          
}



//-----------------------------
//

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
        
    }
}

 
//-----------------------------
//

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,";");      // get the first part - the string
    integerFromPC = atoi(strtokIndx);     // convert this part to an integer
   
    if(integerFromPC<=100)
    {
      serialVal = map(integerFromPC, 0,100,0,180);
    }
    else
    {
      serialVal = 0;
      Serial.print("Invalid Char");
      delay(2000);
    }

 

}
