// defines pins numbers
const int trigPin =2;
const int echoPin = 7;
const int ledPin = 13;

// defines variables
long duration;
int distance;
int safetyDistance;
#include <SoftwareSerial.h> // for GSM
SoftwareSerial mySerial(9, 10); //(5VT, 5VR)
char call;
boolean sndMsg = false;

void setup() {
  // Must be a PWM pin
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(ledPin, OUTPUT);
Serial.begin(9600); // Starts the serial communication
mySerial.begin(9600);
}


void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

safetyDistance = distance;
if (safetyDistance <= 20 && sndMsg==true){ 
  digitalWrite(ledPin, HIGH);
  SendMessage();
    sndMsg=false;
   
}
else{
  digitalWrite(ledPin, LOW);
    sndMsg=true;
}

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}

void SendMessage(){
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+9779860147514\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Motion Detected");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
