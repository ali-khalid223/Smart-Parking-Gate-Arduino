# Smart Parking Gate System 🚗🚧

A smart and automated parking gate system built with Arduino. The system uses a 4x4 Keypad for password entry, an LCD for user feedback, and two Ultrasonic sensors to detect vehicles at the entry and exit points, ensuring the gate stays open until the vehicle safely passes.

## 🌟 Features
* **Password Protection:** Requires a 4-digit code (`1234` by default) for entry and exit.
* **Smart Vehicle Detection:** The gate will NOT close if a vehicle is still passing through, preventing accidents.
* **Interactive LCD:** Displays real-time status (Code entry, Gate Opening, Please Pass, Gate Closed).
* **Audio Feedback:** Buzzer sounds for key presses, correct passwords, and wrong entries.

## 🛠️ Components Used
* Arduino UNO
* 16x2 LCD Display
* 4x4 Membrane Keypad
* 2x Ultrasonic Sensors (HC-SR04)
* Micro Servo Motor
* Buzzer
* Jumper Wires & Breadboard

## 🔌 Pin Mapping (Circuit Connection)

| Component | Arduino Pin |
| :--- | :--- |
| **LCD RS, EN, D4, D5, D6, D7** | 12, 11, 5, 4, 3, 2 |
| **Keypad Rows (1, 2, 3, 4)** | A0, A1, A2, A3 |
| **Keypad Cols (1, 2, 3, 4)** | A4, A5, 7, 9 |
| **Entry Ultrasonic Sensor** | 6 |
| **Exit Ultrasonic Sensor** | 8 |
| **Servo Motor** | 10 |
| **Buzzer** | 13 |

## 🚀 How It Works
1. The system displays `System Ready`.
2. When a car approaches the entry or exit sensor (distance < 20cm), the LCD prompts for a code.
3. The user enters the 4-digit code using the keypad.
4. If correct, the servo opens the gate (90 degrees) and displays `Please Pass...`.
5. The system continuously monitors both sensors. The gate **will only close** when both sensors read a distance > 25cm, ensuring the car has completely cleared the gate area.
6. The gate closes, and the system resets.
7. <img width="1341" height="735" alt="Screenshot 2026-03-28 205420" src="https://github.com/user-attachments/assets/f227e346-7e30-49bb-b5a8-322ce5fa1145" />

