#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo gate;

const byte ROWS = 4; 
const byte COLS = 4; 

char keys[ROWS][COLS] = {
  {'1','2','3','A'}, 
  {'4','5','6','B'}, 
  {'7','8','9','C'}, 
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3}; 
byte colPins[COLS] = {A4, A5, 7, 9};   

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

#define SENSOR_ENTRY 6 // Entry sensor
#define SENSOR_EXIT 8  // Exit sensor
#define SERVO_PIN 10
#define BUZZER_PIN 13

String correctCode = "1234"; 
String inputCode = "";

void setup() {
  lcd.begin(16, 2);
  gate.attach(SERVO_PIN);
  gate.write(0);
  delay(500);
  gate.detach(); 

  pinMode(BUZZER_PIN, OUTPUT);
  lcd.print("System Ready");
  delay(1000);
  lcd.clear();
}

long getDistance(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW); delayMicroseconds(2);
  digitalWrite(pin, HIGH); delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  return pulseIn(pin, HIGH, 15000); 
}

void openTheGate() {
  lcd.clear();
  lcd.print("Gate Opening...");
  
  gate.attach(SERVO_PIN);
  for (int i = 0; i <= 90; i += 3) {
    gate.write(i);
    delay(15);
  }
  
  lcd.clear();
  lcd.print("Please Pass...");
  
  delay(2000); // Give the driver a chance to move
  
  // The gate monitors and waits until the car completely passes
  while (true) {
    long durEn = getDistance(SENSOR_ENTRY);
    float distEn = (durEn == 0) ? 999 : 0.01723 * durEn;
    
    long durEx = getDistance(SENSOR_EXIT);
    float distEx = (durEx == 0) ? 999 : 0.01723 * durEx;

    // If the distance in both sensors is greater than 25 cm, it means the car has passed
    if (distEn > 25 && distEx > 25) {
      break; 
    }
    delay(150); // Quick and continuous check
  }

  delay(1000); // Additional safety delay before closing
  
  lcd.clear();
  lcd.print("Gate Closing...");
  for (int i = 90; i >= 0; i -= 3) {
    gate.write(i);
    delay(15);
  }
  
  gate.detach(); 
  
  lcd.clear();
  lcd.print("Gate Closed!");
  delay(1500); 

  inputCode = ""; 
  lcd.clear();
}

void loop() {
  long durationEntry = getDistance(SENSOR_ENTRY);
  float dEntry = (durationEntry == 0) ? 999 : 0.01723 * durationEntry;
  
  long durationExit = getDistance(SENSOR_EXIT);
  float dExit = (durationExit == 0) ? 999 : 0.01723 * durationExit;

  bool isCarPresent = (dEntry < 20 || dExit < 20);

  // Read keypad input continuously without complex conditions
  char key = keypad.getKey();
  if (key) {
    tone(BUZZER_PIN, 1000, 50);
    inputCode += key;
    
    lcd.clear();
    lcd.print("Code: ");
    lcd.setCursor(0, 1);
    lcd.print(inputCode); 
    
    if (inputCode.length() == correctCode.length()) {
      if (inputCode == correctCode) {
        lcd.clear();
        lcd.print("Access Granted");
        tone(BUZZER_PIN, 2000, 200); 
        delay(500);
        openTheGate();
      } else {
        lcd.clear();
        lcd.print("Wrong Code!");
        tone(BUZZER_PIN, 300, 800); 
        delay(1500);
        inputCode = ""; 
        lcd.clear();
      }
    }
  }

  // Manage the default screen state if the user is not typing anything
  if (inputCode == "") {
    if (isCarPresent) {
      lcd.setCursor(0, 0);
      lcd.print("Enter Code:     ");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("System Ready    ");
    }
  }

  delay(50); 
}
