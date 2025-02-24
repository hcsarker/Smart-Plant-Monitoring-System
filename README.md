# 🌱 Smart Plant Monitoring System using NodeMCU ESP8266

## 📌 Project Description
Welcome to the **Smart Plant Monitoring System**, an IoT-based solution that uses the **NodeMCU ESP8266** to monitor and manage plant health. This project measures **soil moisture, temperature, and humidity** and automatically waters the plant when needed. The system displays real-time data on an **LCD display** and also features manual control via a **push button** for watering.

## 🚀 Features
- 📡 **IoT-enabled Monitoring**: Real-time data collection using **DHT11/DHT22** (for temperature & humidity) and **Soil Moisture Sensor**.
- 💧 **Automated Watering System**: Activates a water pump when soil moisture is low.
- 📊 **Live Data Display**: Displays **temperature**, **humidity**, and **soil moisture** levels on a **16x2 LCD display**.
- 🎛 **Manual Control**: Press the button to manually activate the watering system.
- 🌍 **Cloud Integration (Future Scope)**: Plan to integrate with **Blynk/ThingSpeak** for remote monitoring and control.

## 🛠️ Hardware Requirements
- **NodeMCU ESP8266**
- **DHT11/DHT22 Temperature & Humidity Sensor**
- **Soil Moisture Sensor**
- **Relay Module**
- **Water Pump**
- **16x2 LCD Display with I2C**
- **Push Button**
- **Jumper Wires & Breadboard**

## 📜 Software Requirements
- **Arduino IDE** (Download from [Arduino Official Website](https://www.arduino.cc/en/software))
- **ESP8266 Board Manager** in Arduino IDE
- **DHT Sensor Library** (by Adafruit)
- **LiquidCrystal_I2C Library** (by Marco Schwartz)
- **Blynk Library** (for cloud integration)

## 📌 Circuit Diagram

The circuit connects the sensors to the **NodeMCU** as follows:

- **Soil Moisture Sensor**: A0
- **PIR Motion Sensor**: D6
- **Relay Module**: D7
- **Push Button**: D5
- **DHT11 Sensor**: D4
Below is the circuit diagram:

## 🔧 Installation & Setup
### 1️⃣ **Set Up Arduino IDE**
- Install **Arduino IDE** from [Arduino Official Website](https://www.arduino.cc/en/software).
- Add **ESP8266 Board Manager**:
  - Open **Arduino IDE** → Go to **File > Preferences**
  - Add this URL in **Additional Board Manager URLs**:
    ```
    http://arduino.esp8266.com/stable/package_esp8266com_index.json
    ```
  - Install **ESP8266 by ESP8266 Community** from Board Manager.

### 2️⃣ **Install Required Libraries**
Go to **Sketch > Include Library > Manage Libraries**, then install:
- **DHT sensor library** by Adafruit
- **LiquidCrystal_I2C** by Marco Schwartz
- **Blynk Library** by Blynk

### 3️⃣ **Upload Code to NodeMCU**
- Connect **NodeMCU ESP8266** to your PC via USB.
- Select **Board: NodeMCU 1.0** in **Tools > Board**.
- Select the correct **COM Port**.
- Upload the `SmartPlant.ino` file.

### 4️⃣ **Configure Blynk App (Optional for Cloud Integration)**
- Download the **Blynk** app from **Google Play Store** or **App Store**.
- Create a new project in the app, select **NodeMCU** as the device, and note the **Auth Token**.
- Replace the `auth[]` variable in the code with your **Auth Token** from Blynk.

## 🎯 Usage Instructions
1. Power up the system.
2. The LCD will display **temperature, humidity, and soil moisture**.
3. If the soil moisture falls below the threshold, the **relay will activate** the water pump.
4. Press the **manual button** to water the plant manually.

## 📝 Code Overview

### Key Functions:
- `updateDHTSensor()`: Reads temperature and humidity from the **DHT11** sensor and displays them on the LCD and sends them to the **Blynk app**.
- `updateSoilMoisture()`: Reads the soil moisture level and displays it on the LCD.
- `updatePIRSensor()`: Detects motion via **PIR** sensor and triggers the LED in the **Blynk app**.
- `checkButtonState()`: Monitors the **push button** and toggles the relay for manual watering control.

### Code Snippet:
```cpp
void loop() {
  int moisture = analogRead(A0);  // Read soil moisture sensor
  float temp = dht.readTemperature();  // Read temperature from DHT sensor
  float humidity = dht.readHumidity();  // Read humidity from DHT sensor
  
  lcd.setCursor(0, 0);
  lcd.print("Temp: "); lcd.print(temp);
  lcd.setCursor(0, 1);
  lcd.print("Moisture: "); lcd.print(moisture);
  
  if (moisture < threshold) {
    digitalWrite(pump, HIGH);  // Activate pump if soil moisture is low
  } else {
    digitalWrite(pump, LOW);  // Deactivate pump if soil moisture is sufficient
  }
}

```

## 📷 Project Demo
(Attach images or a YouTube link of your project in action.)

## 🔗 Future Improvements
- 📡 Cloud Integration: Send data to Blynk/ThingSpeak for remote monitoring.
- 📱 Mobile App Support: Create an app for real-time monitoring and control.
- 🌿 AI-based Recommendations: Suggest optimal watering schedules based on weather data and plant type.
- 🤝 Contributing
- Contributions are welcome! Feel free to fork this repository, create a new branch, and submit a pull request.

## 📜 License
- This project is open-source and licensed under the MIT License.

## 📧 Contact
- For any questions or improvements, feel free to reach out!

- Email: hcsarker2002@gmail.com
- GitHub: hcsarker
