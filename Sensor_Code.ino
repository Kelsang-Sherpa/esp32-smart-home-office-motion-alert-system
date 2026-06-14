#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define PIR_PIN 14
#define BUZZER_PIN 25

int lastMotion = -1;

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);   // I2C LCD: SDA=21, SCL=22

  lcd.init();
  lcd.backlight();

  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Motion System");
  lcd.setCursor(0, 1);
  lcd.print("Ready");

  Serial.println("System Ready");
  delay(3000);
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  Serial.print("PIR value: ");
  Serial.println(motion);

  if (motion != lastMotion) {
    lcd.clear();

    if (motion == HIGH) {
      lcd.setCursor(0, 0);
      lcd.print("Motion Detected");
      lcd.setCursor(0, 1);
      lcd.print("Buzzer ON");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("No Motion");
      lcd.setCursor(0, 1);
      lcd.print("System Active");
    }

    lastMotion = motion;
  }

  if (motion == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(300);
    digitalWrite(BUZZER_PIN, LOW);
    delay(300);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);
  }
}