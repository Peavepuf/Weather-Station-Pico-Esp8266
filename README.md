# Raspberry Pi Pico Sensor Data Transmission to Thingspeak via ESP8266

This repository demonstrates a project where sensor data collected from sensors connected to a Raspberry Pi Pico is transmitted to an ESP8266, which then sends this data to the Thingspeak platform for storage and visualization.

## Overview

The project includes two main components:

1. **Raspberry Pi Pico (Sensor Data Provider)**
    - Collects sensor data (temperature and humidity from DHT11 sensor, pressure and altitude from BMP180 sensor).
    - Transmits this data to the ESP8266 via serial communication.

2. **ESP8266 (Data Transmitter to Thingspeak)**
    - Receives sensor data from Raspberry Pi Pico via serial communication.
    - Sends this data to the Thingspeak platform using Wi-Fi connectivity.

## Instructions

1. **Setup Raspberry Pi Pico:**
   - Connect the DHT11 and BMP180 sensors to the Raspberry Pi Pico as described in the code comments.
   - Upload the code in `RaspberryPiPicoCode/` to the Raspberry Pi Pico.

2. **Setup ESP8266:**
   - Upload the code in `ESP8266Code/` to the ESP8266 board.
   - Configure Wi-Fi credentials, Thingspeak API key, and channel settings in the ESP8266 code.

3. **Testing:**
   - Power up both Raspberry Pi Pico and ESP8266.
   - Check the Arduino Serial Monitor to confirm that sensor data is being transmitted from the Raspberry Pi Pico to the ESP8266.
   - Visit your Thingspeak channel to visualize and analyze the collected sensor data.

## Requirements

- Raspberry Pi Pico with appropriate pin connections for DHT11 and BMP180 sensors.
- ESP8266 board compatible with Arduino IDE.
- Thonny IDE for Raspberry Pico H
- DHT sensor library for Raspberry Pi Pico.
- BMP sensor library for Raspberry Pi Pico.
- ESP8266WiFi library for ESP8266.

Feel free to modify and adapt the code according to your sensor setup or additional requirements.

---
