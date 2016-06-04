#include <DMXSerial.h>

const int RedPin =    9;  // PWM output pin for Red Light.
const int GreenPin =  6;  // PWM output pin for Green Light.
const int BluePin =   5;  // PWM output pin for Blue Light.

// The color fading pattern

int RedList[]   = {255, 128,   0,   0,   0, 128};
int GreenList[] = {  0, 128, 255, 128,   0,   0};
int BlueList[]  = {  0,   0,   0, 128, 255, 128};

int RedLevel, GreenLevel, BlueLevel;

int RedNow = 0;
int GreenNow = 0;
int BlueNow = 0;

int state = 0;

void setup() {
  DMXSerial.init(DMXController);

  pinMode(RedPin,   OUTPUT); // sets the digital pin as output
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin,  OUTPUT);
} // setup

void loop() {
  // put your main code here, to run repeatedly:
  RedLevel = RedList[state];
  GreenLevel = GreenList[state];
  BlueLevel = BlueList[state];
  
  if ((RedLevel == RedNow) && (GreenLevel == GreenNow) && (BlueLevel == BlueNow)) {
    state += 1;
    if (state == 6)
      state = 0;

  } else {
    DMXSerial.write(1, 64);
    DMXSerial.write(2, 0);
    DMXSerial.write(3, 0);
    DMXSerial.write(4, 0);
    if (RedNow < RedLevel)  RedNow++; 
    if (RedNow > RedLevel)  RedNow--; 
    DMXSerial.write(5, RedNow);
    analogWrite(RedPin,   RedNow); 

    if (GreenNow < GreenLevel)  GreenNow++; 
    if (GreenNow > GreenLevel)  GreenNow--; 
    DMXSerial.write(6, GreenNow);
    analogWrite(GreenPin, GreenNow); 

    if (BlueNow < BlueLevel)  BlueNow++; 
    if (BlueNow > BlueLevel)  BlueNow--; 
    DMXSerial.write(7, BlueNow);
    analogWrite(BluePin,  BlueNow); 
  } // if

  delayMicroseconds(10000); // wait a little bit was 2000
}
