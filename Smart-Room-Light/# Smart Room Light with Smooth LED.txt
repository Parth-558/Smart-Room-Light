# Smart Room Light with Smooth LED Fade

An intelligent lighting system using **LDR**, **PIR**, **manual override**, and **millis()-based LED fading**. Built with Arduino Uno and simulated in Tinkercad.

---

## 🔧 Features

* **Automatic LED control** based on light level (LDR) and motion (PIR)
* **Smooth LED fade-in/out** using `analogWrite()` and `millis()`
* **Manual override** using push-button
* **Status LED** for idle state (dim glow)
* **Intrusion alert** via buzzer if sudden light drop + motion detected
* **Auto shutoff** after 2 minutes of no motion

---

## 🔌 Circuit Components

* Arduino Uno
* LDR (A0)
* PIR Motion Sensor (D2)
* LED with resistor (D9)
* Status LED (D7)
* Piezo Buzzer (D5)
* Push Button (D4)
* Resistors (10k for LDR, 220Ω for LEDs)

---

## 🖼️ Circuit Diagram

> Add the Tinkercad circuit image here (uploaded screenshot)

```
LDR       --> A0 + 5V (via 10k resistor to GND)
PIR OUT   --> D2
LED       --> D9 with 220Ω resistor
Status LED --> D7 with 220Ω resistor
Button    --> D4 + GND (use INPUT_PULLUP)
Buzzer    --> D5
```

---

## 📜 Code Explanation

```cpp
#include <Arduino.h>

#define LDR_PIN A0
#define PIR_PIN 2
#define LED_PIN 9
#define STATUS_LED 7
#define BUZZER_PIN 5
#define BUTTON_PIN 4

int brightness = 0;
int fadeAmount = 5;
unsigned long lastFadeTime = 0;
unsigned long fadeInterval = 30;
unsigned long ledOnTime = 0;
unsigned long ledHoldTime = 5000;

unsigned long noMotionSince = 0;
unsigned long noMotionTimeout = 120000; // 2 minutes
int lastPIR = LOW;
int lastLDRValue = 0;
bool ledOn = false;

void setup() {
  pinMode(LDR_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  int ldrValue = analogRead(LDR_PIN);
  int pirValue = digitalRead(PIR_PIN);

  // LED fade-in on motion + dark
  if (ldrValue > 600 && pirValue == HIGH) {
    if (currentMillis - lastFadeTime > fadeInterval) {
      brightness = min(brightness + fadeAmount, 255);
      analogWrite(LED_PIN, brightness);
      lastFadeTime = currentMillis;
    }
    if (brightness == 255 && !ledOn) {
      ledOn = true;
      ledOnTime = currentMillis;
    }
  }

  // LED fade-out after delay
  if (ledOn && currentMillis - ledOnTime >= ledHoldTime) {
    if (currentMillis - lastFadeTime > fadeInterval) {
      brightness = max(brightness - fadeAmount, 0);
      analogWrite(LED_PIN, brightness);
      lastFadeTime = currentMillis;
    }
    if (brightness == 0) ledOn = false;
  }

  // Status LED: dim when idle
  if (ldrValue < 600 || pirValue == LOW) {
    analogWrite(STATUS_LED, 30);
  } else {
    digitalWrite(STATUS_LED, LOW);
  }

  // Track motion status
  if (pirValue == LOW && lastPIR == HIGH) {
    noMotionSince = currentMillis;
  }
  lastPIR = pirValue;

  // Auto shutoff if no motion for 2 minutes
  if (pirValue == LOW && (currentMillis - noMotionSince > noMotionTimeout)) {
    brightness = 0;
    analogWrite(LED_PIN, 0);
  }

  // Intrusion alert
  if ((lastLDRValue - ldrValue) > 500 && pirValue == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
  }
  lastLDRValue = ldrValue;
}
```

---

## 📂 Files in Repo

* `Led_Fade_LDR.ino` → Main Arduino code
* `circuit.png` → Circuit image exported from Tinkercad
* `README.md` → This file

---

## ✅ Built With Love By

**Parth Pawar**

> Dream: To build intelligent, helpful robots that make life better 🧠⚙️
