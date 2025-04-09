#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo myservo;

const int pHSensorPin = A0;
const int turbiditySensorPin = A1;
const int servoPin = 9;

void setup() {
  lcd.begin(16, 2);
  myservo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  int pHValue = analogRead(pHSensorPin);
  int turbidityValue = analogRead(turbiditySensorPin);

  float pH = pHValue * (5.0 / 1023.0) * 3.5;
  float turbidity = turbidityValue * (5.0 / 1023.0);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pH: ");
  lcd.print(pH);
  lcd.setCursor(0, 1);
  lcd.print("Turb: ");
  lcd.print(turbidity);

  if (pH < 6.5 || pH > 8.5 || turbidity > 1.0) {
    myservo.write(90); // Open valve
    lcd.setCursor(8, 1);
    lcd.print("BAD");
  } else {
    myservo.write(0); // Close valve
    lcd.setCursor(8, 1);
    lcd.print("GOOD");
  }

  delay(2000);
}