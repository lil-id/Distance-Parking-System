#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
  
const byte Echo = 2;//kaki ultrasonik
const byte Trig = 3;//kaki ultrasonik
long duration;
int distance; 
byte alarm = 9; //buzzer
int jarak;
String line1, line2;
unsigned long old_time;
  
void setup() {
   lcd.init();
   lcd.backlight();
   pinMode(4, OUTPUT);  //LED lamp
   pinMode(Echo, INPUT);
   pinMode(Trig, OUTPUT);
}

void baca_sensor(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2; 
}

void get_data(){
  baca_sensor(Trig,Echo);
  jarak = distance;
  line1 = "Hitung Jarak";
  line2 = String("Jarak: ") + jarak + (" cm");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
}

void loop() {
   if( millis() - old_time >= 250 ){
    get_data();
    old_time = millis();
   }
   if (jarak <= 3) {
    digitalWrite(4, HIGH);
    delay(2000);
    tone(alarm, 2000);
    delay(100);
    noTone(alarm);
   }
   else if (jarak <= 9) {
    digitalWrite(4, HIGH);
    delay(100);
    tone(alarm, 2000);
    delay(100);
    noTone(alarm);
    delay(100);
    digitalWrite(4, LOW);
    delay(100);
    
    digitalWrite(4, HIGH);
    delay(100);
    tone(alarm, 2000);
    delay(100);
    noTone(alarm);
    digitalWrite(4, LOW);
    delay(100);
   }
   else {
    delay(100);
    noTone(alarm);
   }
}
