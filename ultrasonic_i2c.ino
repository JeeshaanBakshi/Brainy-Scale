#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 7
#define ECHO_PIN 6

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Using correct address and dimensions

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.init();        // Use lcd.init() instead of lcd.begin()
  lcd.backlight();   // Turn on the LCD backlight

  lcd.setCursor(0, 0);
  lcd.print("Distance Meter");
  delay(2000);
  lcd.clear();
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration / 2.0) / 29.1;

  // Print to LCD
  lcd.setCursor(0, 0);
  lcd.print("Distance:");

  lcd.setCursor(0, 1);
  lcd.print("                "); // Clear old value
  lcd.setCursor(0, 1);
  lcd.print(distance, 1); // Print with 1 decimal place
  lcd.print(" cm");

  // Also print to Serial
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}
