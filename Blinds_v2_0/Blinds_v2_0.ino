/*
  Blinds v2.0 - designed to work with an external wall timer.
  When power on, blind should open if they're closed and close if they're open.
 */
 
#include <EEPROM.h>
 
// Choose a pin for the signal pin on each relay module
int openPin = 7;
int closePin = 8;

// Chose a memory address to remember the blinds state
int stateAddress = 100;
// Define the states
byte closedState = 1;
byte openState = 0;

// Which pins should be used to determine timings?
// These should be connected to trimming potentiometers
int openTrimPin = 0;
int closeTrimPin = 1;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(openPin, OUTPUT); 
  digitalWrite(openPin, HIGH); // high is off
  pinMode(closePin, OUTPUT);
  digitalWrite(closePin, HIGH); // high is off
  delay(2000);              // wait a few seconds before doing anything
  if (EEPROM.read(stateAddress) == openState)
  {
    closeBlinds();
  }
  else
  {
    openBlinds();
  }
}

// the loop routine runs over and over again forever:
void loop() {
}

void openBlinds() {
  int openTrimVal = analogRead(openTrimPin);
  digitalWrite(openPin, LOW);
  delay(2000 + 2 * openTrimVal);             // wait for a few seconds
  digitalWrite(openPin, HIGH);
  EEPROM.write(stateAddress, openState);
}

void closeBlinds() {
  int closeTrimVal = analogRead(closeTrimPin);
  digitalWrite(closePin, LOW);
  delay(2000 + 2 * closeTrimVal);                  // wait for a few seconds
  digitalWrite(closePin, HIGH);
  EEPROM.write(stateAddress, closedState);
}
