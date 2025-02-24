/* Connections:
   Soil Moisture Sensor: A0
   PIR Motion Sensor:    D6
   Relay Module:         D7
   Push Button:          D5
   DHT Sensor:           D4
*/

#define BLYNK_TEMPLATE_ID "TMPL6b-B2x9Vj"
#define BLYNK_TEMPLATE_NAME "Smart plant monitoring system"

// Include libraries
#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Initialize LCD and DHT sensor
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Wi-Fi and Blynk credentials
char auth[] = "bog1VV5PcXgp7dJNaiEh49_MzjOguWgS";
char ssid[] = "Galaxy M519904";
char pass[] = "ashuashu";

// Define pins for components
#define SOIL_PIN A0
#define PIR_PIN D6
#define RELAY_PIN D7
#define BUTTON_PIN D5
#define DHT_PIN D4

DHT dht(DHT_PIN, DHT11);
BlynkTimer timer;

void checkPhysicalButton();
int pirToggleValue = 0;
int relayState = LOW;
int buttonState = HIGH;

// Virtual pin assignments
#define VPIN_BUTTON V12
#define VPIN_TEMP V0
#define VPIN_HUMIDITY V1
#define VPIN_SOIL V3
#define VPIN_PIR_LED V5

// Initializing DHT in setup
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  digitalWrite(RELAY_PIN, relayState);
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);


  
  // Display initializing message
  lcd.setCursor(0, 0);
  lcd.print("  Initializing  ");
  for (int i = 5; i <= 10; i++) {
    lcd.setCursor(i, 1);
    lcd.print(".");
    delay(250);  // Adjusted delay for smoother loading
  }
  lcd.clear();
  lcd.setCursor(11, 1);
  lcd.print("W:OFF");

  // Set up Blynk timers
  timer.setInterval(2000L, updateSoilMoisture); // Soil sensor update every 2 seconds
  timer.setInterval(2000L, updateDHTSensor);    // DHT sensor update every 2 seconds
  timer.setInterval(500L, checkButtonState);    // Button check every 500ms
}

// Function to read temperature and humidity from DHT11
void updateDHTSensor() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Print to serial for debugging
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0, 0);
    lcd.print("DHT Error      ");  // Clear previous values
    delay(250); // Shorter delay to retry quickly
    return;
  }
  
  Blynk.virtualWrite(VPIN_TEMP, temperature);
  Blynk.virtualWrite(VPIN_HUMIDITY, humidity);
  
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temperature);

  lcd.setCursor(8, 0);
  lcd.print(" H: ");
  lcd.print(humidity);
}


// Function to read soil moisture
void updateSoilMoisture() {
  int soilValue = analogRead(SOIL_PIN);
  soilValue = map(soilValue, 0, 1024, 0, 100);
  soilValue = (soilValue - 100) * -1; // Adjust for inverted values
  
  Blynk.virtualWrite(VPIN_SOIL, soilValue);
  
  lcd.setCursor(0, 1);
  lcd.print("S: ");
  lcd.print(soilValue);
  lcd.print("%");
}

// Function to check PIR sensor and control virtual LED
void updatePIRSensor() {
  bool pirValue = digitalRead(PIR_PIN);
  
  if (pirValue) {
    Blynk.logEvent("PIRmotion", "WARNING! Motion Detected!");
    Blynk.virtualWrite(VPIN_PIR_LED, 255); // Turn on LED in Blynk app
    lcd.setCursor(5, 1);
    lcd.print("M: ON ");
  } else {
    Blynk.virtualWrite(VPIN_PIR_LED, 0); // Turn off LED in Blynk app
    lcd.setCursor(5, 1);
    lcd.print("M: OFF");
  }
}

// Blynk write for PIR toggle control
BLYNK_WRITE(V6) {
  pirToggleValue = param.asInt();
}

// Blynk write for button relay control
BLYNK_WRITE(VPIN_BUTTON) {
  relayState = param.asInt();
  digitalWrite(RELAY_PIN, relayState);
  updateRelayDisplay();
}

// Check physical button and update relay state
void checkButtonState() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (buttonState != LOW) {
      relayState = !relayState;
      digitalWrite(RELAY_PIN, relayState);
      Blynk.virtualWrite(VPIN_BUTTON, relayState);
      updateRelayDisplay();
    }
    buttonState = LOW;
  } else {
    buttonState = HIGH;
  }
}

// Display relay state on LCD
void updateRelayDisplay() {
  lcd.setCursor(11, 1);
  if (relayState == HIGH) {
    lcd.print("W: ON ");
  } else {
    lcd.print("W: OFF");
  }
}

void loop() {
  Blynk.run();
  timer.run();
  
  // Check PIR if enabled
  if (pirToggleValue == 1) {
    updatePIRSensor();
  } else {
    lcd.setCursor(5, 1);
    lcd.print("M: OFF");
  }
}
