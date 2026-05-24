# ESP-Deauth-Simulator
A web-based educational simulator for Wi-Fi deauthentication attacks using ESP8266. Includes user interaction and data collection via a local access point.

# 🚨 ESP-Deauth-Simulator

This is an  simulation of a Wi-Fi deauthentication attack using an ESP8266 microcontroller. It sets up a local access point with a web interface where users can simulate a deauth trigger and send custom data to the ESP8266 for processing and future logging.


---

## 📦 Features

- Creates a local Wi-Fi Access Point (`Cypherr`)
- Hosts a web page with:
  - A "Start Deauth Simulation" button (fake trigger)
  - A data input form to send text to the ESP
- Receives and displays submitted data
- Real-time interaction over browser
- Serial monitor logs activity

---

## 🛠️ Requirements

- ESP8266 NodeMCU (or similar ESP8266 board)
- Arduino IDE installed
- ESP8266 board manager installed in Arduino IDE
- USB cable for flashing

---

## 🔧 Setup Instructions

1. Clone or download this repo:
   ```bash
   git clone https://github.com/Harsh-Khatri1001/Wi-Fi-Security-Testing-Simulator
