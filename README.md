# 🩺 MedBand: Smart IoT Wearable for Health Monitoring

## 📌 Overview
MedBand is a smart IoT-based wearable system designed to monitor real-time health parameters such as heart rate (BPM), body temperature, and oxygen saturation (SpO₂). The system provides live data visualization, detects abnormal conditions, and sends alerts to healthcare providers.

---

## 🎯 Objectives
- Monitor vital health parameters in real-time  
- Detect abnormal conditions automatically  
- Provide early warning alerts to doctors  
- Enable remote patient monitoring  

---

## 🛠️ Technologies Used
- **Hardware:** ESP8266, MAX30102 Sensor, DHT11  
- **Software:** Arduino IDE, HTML, JavaScript  
- **Cloud:** ThingSpeak  
- **Alert System:** EmailJS  
- **Version Control:** GitHub  

---

## ⚙️ Features
- 📊 Real-time health monitoring dashboard  
- ❤️ Heart Rate (BPM) tracking  
- 🌡️ Body temperature monitoring  
- 🫁 SpO₂ level detection  
- 🧠 Disease prediction based on vitals  
- 🚨 Automatic alert system (Email to doctor)  
- 📥 Download patient data (CSV format)  
- 📈 Graphical visualization using charts  

---

## 🧠 Disease Detection Logic
The system predicts possible conditions based on thresholds:

| Parameter | Condition |
|----------|----------|
| BPM > 100 | Tachycardia |
| BPM < 60 | Bradycardia |
| Temp ≥ 37°C | Fever |
| SpO₂ < 95% | Hypoxia |
| Multiple issues | Respiratory Infection |

> ⚠️ Note: This system provides preliminary analysis and is not a substitute for medical diagnosis.

---

## 🏗️ System Architecture
1. Sensors collect physiological data  
2. ESP8266 processes and sends data to ThingSpeak  
3. Web dashboard fetches and displays data  
4. Alert system triggers email if abnormal values detected  

---

## 🚀 How to Run

### 🔹 Hardware Setup
- Connect MAX30102 and DHT11 to ESP8266  
- Upload Arduino code using Arduino IDE  

### 🔹 Dashboard Setup
- Open the HTML file in browser  
- Ensure internet connection for ThingSpeak  

### 🔹 Email Alert Setup
- Configure EmailJS  
- Add Service ID, Template ID, Public Key in code  

---

## 📊 Output
- Real-time graphs of BPM, Temperature, and SpO₂  
- Health status (Normal / Abnormal)  
- Disease prediction display  
- Email alerts for critical conditions  

---

## 🤝 Collaboration
This project is maintained using GitHub for version control and collaboration with the project supervisor.

---

## 🔮 Future Enhancements
- 📱 Mobile application integration  
- 🤖 AI-based disease prediction  
- 📍 GPS tracking for patients  
- 📲 SMS / WhatsApp alerts  
- ☁️ Cloud database (Thingspeak)  

---

## 👨‍💻 Author
**Gopichand**

---

## 📜 License
This project is for academic and research purposes.
