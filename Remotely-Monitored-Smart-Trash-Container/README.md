
# Remotely Monitored Smart Trash Container

This project was developed as part of a graduation project at Karadeniz Technical University by Abdullah Demir, Abdullah Aydın, and Yasin Dağlı under the supervision of Dr. Mustafa Şinasi Ayas. The project focuses on a smart trash container that can be remotely monitored using IoT technologies.

## Project Overview
The system monitors trash container fill levels, detects temperature changes, and identifies harmful gases, all powered by solar energy. It sends notifications through a mobile application using GSM/GPRS and GPS technologies.

## Features
- **Remote Monitoring:** Real-time tracking of container fill levels.
- **Safety Alerts:** Temperature and gas sensors to prevent hazards.
- **GPS Tracking:** Location tracking and route optimization for waste collection.
- **Solar-Powered:** The system runs entirely on solar energy.

## Components
- **Sensors:** DHT11 (Temperature and Humidity), HC-SR04 (Ultrasonic Distance), MQ-4 (Gas Sensor)
- **Microcontroller:** Arduino Uno
- **Communication Modules:** SIM808 (GSM/GPRS + GPS)

## Installation
1. Clone this repository.
2. Install the Arduino IDE and necessary libraries.
3. Load the code onto your Arduino Uno.
4. Assemble the hardware according to the design schematics.
5. Connect the system to the solar power setup and test the sensors.

## Usage
Once installed and powered, the system will monitor the trash container's status and send updates via the mobile app. Use the Blynk app for real-time monitoring and alerts.
