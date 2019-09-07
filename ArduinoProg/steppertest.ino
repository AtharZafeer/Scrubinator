
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); 
const int strokeSwitch = 5, enter = 2;
int stroke=0, ok=0,totalStrokes=0;
int count = 0;
const int pulsepin = 6;
void setup() {
  // set up the LCD's number of columns and rows:
  pinMode(strokeSwitch,INPUT_PULLUP);
  pinMode(enter,INPUT_PULLUP);
  pinMode(pulsepin,OUTPUT);
  lcd.begin(16, 2);
  
  //Serial.begin(9600);
  // Print a message to the LCD.
  lcd.print("Welcome hooman:)");
  delay(2000);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.clear(); 
  lcd.setCursor(0,0);
  lcd.print("No of strokes");
  stroke = digitalRead(strokeSwitch);
  if(stroke == 0) {
      totalStrokes+=50;
    }
  //Serial.println(stroke);
  lcd.setCursor(0, 1 );
  
  // print the number of seconds since reset:
  ok = digitalRead(enter);
  lcd.print(totalStrokes);
   if(ok == 0) {
      stepper(totalStrokes);
    }
  delay(200);
  
}

void stepper(int NoofStrokes) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("strokes: ");
  lcd.print(NoofStrokes);
  while(count*2 < NoofStrokes) {
     for(int i = 0; i<200; i++) {
        digitalWrite(pulsepin, HIGH);
        delayMicroseconds(2500);
        digitalWrite(pulsepin,LOW);
        delayMicroseconds(2500);
        }
    count++;
    
   lcd.setCursor(0,1);
   lcd.print("count: ");
   lcd.print(count*2); 
   }
   if(count*2 == NoofStrokes) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(count*2);
      lcd.print(" strokes");
      lcd.setCursor(0,1);
      lcd.print("COMPLETED!");
    }
   delay(10000);
   count =0;
 }
