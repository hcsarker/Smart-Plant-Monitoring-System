# 🌱 Smart Plant Monitoring System using NodeMCU ESP8266

## 📌 Project Description
This project is an IoT-based **Smart Plant Monitoring System** that uses the **NodeMCU ESP8266** to monitor and manage plant health. It measures **soil moisture, temperature, and humidity**, and automates watering when needed. The system displays real-time data on an **LCD** and allows manual control through a **push button**.

## 🚀 Features
- 📡 **IoT-enabled Monitoring**: Real-time data collection using **DHT11/DHT22** and **Soil Moisture Sensor**.
- 💧 **Automated Watering System**: Activates a water pump when soil moisture is low.
- 📊 **Live Data Display**: Shows temperature, humidity, and soil moisture levels on an **LCD display**.
- 🎛 **Manual Control**: Push button for manual irrigation.
- 🌍 **Cloud Integration (Future Scope)**: Possible integration with **Blynk/ThingSpeak** for remote monitoring.

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
- **Arduino IDE**
- **ESP8266 Board Manager**
- **DHT Sensor Library**
- **LiquidCrystal_I2C Library**

## 📌 Circuit Diagram
(Upload an image of your circuit here or provide Fritzing/Proteus design.)

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

### 3️⃣ **Upload Code to NodeMCU**
- Connect **NodeMCU ESP8266** to your PC via USB.
- Select **Board: NodeMCU 1.0** in **Tools > Board**.
- Select the correct **COM Port**.
- Upload the `SmartPlant.ino` file.

## 🎯 Usage Instructions
1. Power up the system.
2. The LCD will display **temperature, humidity, and soil moisture**.
3. If soil moisture is below the threshold, the **relay will activate** and start the water pump.
4. Press the **manual button** to start watering manually.

## 📝 Code Overview
```cpp
void loop() {
  int moisture = analogRead(A0);
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  lcd.setCursor(0, 0);
  lcd.print("Temp: "); lcd.print(temp);
  lcd.setCursor(0, 1);
  lcd.print("Moisture: "); lcd.print(moisture);
  
  if (moisture < threshold) {
    digitalWrite(pump, HIGH);
  } else {
    digitalWrite(pump, LOW);
  }
}
```

## 📷 Project Demo
(Attach images or a YouTube link of your project in action.)

## 🔗 Future Improvements
- 📡 **Cloud Integration**: Send data to **Blynk/ThingSpeak** for remote monitoring.
- 📱 **Mobile App Support**: Create an app for real-time monitoring.
- 🌿 **AI-based Recommendations**: Suggest optimal watering schedules based on weather data.

## 🤝 Contributing
Contributions are welcome! Feel free to **fork** this repository, create a new branch, and submit a **pull request**.

## 📜 License
This project is **open-source** and licensed under the **MIT License**.

## 📧 Contact
For any questions or improvements, feel free to reach out!
- **Email**: your-email@example.com
- **GitHub**: [Your GitHub Profile](https://github.com/your-username)
