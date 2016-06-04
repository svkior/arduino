#include <Servo.h>
#include <LiquidCrystal.h>
#include <DMXSerial.h>

#define POT_MAX_ANGLE 180.0

Servo myServo;
int val;
int direct;

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

unsigned long lp;

void setup() {
  // put your setup code here, to run once:
  DMXSerial.init(DMXReceiver);
  myServo.attach(3);
  val = 0;
  direct = 0;
  lcd.begin(16,2);
  lcd.print("Servo angle:");
  lp = 0;
}

void printVal(int val){
  if(val < 10)
    lcd.print("0");
  if(val < 100)
    lcd.print("0");
  lcd.print(val);
  lcd.print(" ");
}

void loop() {
  unsigned long lastPacket = DMXSerial.noDataSince();
  
  if(lastPacket < 5000){
    val = DMXSerial.read(1);
    int angle = int(val / 255.0 * POT_MAX_ANGLE);
    angle = constrain(angle, 0, 180);
    myServo.write(angle);
    lcd.setCursor(0,0);
    printVal(DMXSerial.read(5));
    printVal(DMXSerial.read(6));
    printVal(DMXSerial.read(7));
    printVal(DMXSerial.read(8));
    lcd.setCursor(0 ,1);
    lcd.print(angle);
    lcd.print(" Gradus ");
    lcd.print(lastPacket);
    lcd.print("   ");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("NO DMX");
  }
  delay(1);
}
