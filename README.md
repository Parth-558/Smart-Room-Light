# Smart-Room-Light
An intelligent LED light control system using Arduino, LDR, PIR, and smooth fading.
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
