// Pin Definitions
const int LDR_PIN = A0;
const int PIR_PIN = 2;
const int LED_PIN = 9;
const int STATUS_LED = 7;
const int BUZZER_PIN = 5;
const int BUTTON_PIN = 4;

// Variables
int brightness = 0;
int fadeAmount = 5;
bool ledOn = false;
bool manualOverride = false;

unsigned long lastFadeTime = 0;
unsigned long ledOnTime = 0;
unsigned long noMotionSince = 0;
unsigned long currentMillis = 0;

unsigned long fadeInterval = 30;
unsigned long ledHoldTime = 5000;         // Keep LED ON for 5 sec after full brightness
unsigned long noMotionTimeout = 120000;   // 2 minutes auto shutoff

int lastPIR = LOW;
int lastLDRValue = 0;

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
  currentMillis = millis();

  int ldrValue = analogRead(LDR_PIN);
  int pirValue = digitalRead(PIR_PIN);
  int buttonState = digitalRead(BUTTON_PIN);

  // Manual override if button is pressed
  if (buttonState == LOW) {
    manualOverride = true;
    brightness = 255;
    analogWrite(LED_PIN, brightness);
    ledOn = true;
    ledOnTime = currentMillis;
  }

  // LED fade-in on motion + darkness
  if (!manualOverride && ldrValue > 600 && pirValue == HIGH) {
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

  // Status LED glow when idle
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

  // Auto shutoff if no motion for 2 mins
  if (!manualOverride && pirValue == LOW && (currentMillis - noMotionSince > noMotionTimeout)) {
    brightness = 0;
    analogWrite(LED_PIN, 0);
    ledOn = false;
  }

  // Intrusion detection (light drop + motion)
  if ((lastLDRValue - ldrValue) > 500 && pirValue == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
  }

  lastLDRValue = ldrValue;

  // Serial monitor for debugging
  Serial.print("LDR: ");
  Serial.print(ldrValue);
  Serial.print(" | PIR: ");
  Serial.print(pirValue);
  Serial.print(" | Brightness: ");
  Serial.print(brightness);
  Serial.print(" | Manual: ");
  Serial.println(manualOverride ? "YES" : "NO");
}

