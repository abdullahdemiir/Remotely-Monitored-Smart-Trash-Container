
# Installation Guide

## Prerequisites
- Arduino IDE [Download here](https://www.arduino.cc/en/software)
- Blynk App [Available on iOS and Android]

## Hardware Setup
1. Connect the sensors (DHT11, HC-SR04, MQ-4) to the Arduino Uno as per the circuit diagrams provided.
2. Attach the SIM808 module for GSM/GPRS and GPS functionalities.
3. Connect the solar panel to the battery and voltage regulator.
4. Assemble the components into the project box.

## Software Setup
1. Clone this repository to your local machine.
2. Open the Arduino IDE and load the provided `.ino` files.
3. Install the necessary libraries:
   - Blynk
   - TinyGPSPlus
   - DHT Sensor Library
4. Upload the code to the Arduino Uno.
5. Configure the Blynk app with the provided Auth Token and connect your project.

## Testing
- Ensure the system is powered by the solar setup and monitor the sensors through the Blynk app.
- Check the real-time notifications and location tracking features.
