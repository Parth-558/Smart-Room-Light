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

>(Smart-Room-Light/Smart_room_light.png)

```
LDR       --> A0 + 5V (via 10k resistor to GND)
PIR OUT   --> D2
LED       --> D9 with 220Ω resistor
Status LED --> D7 with 220Ω resistor
Button    --> D4 + GND (use INPUT_PULLUP)
Buzzer    --> D5
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
