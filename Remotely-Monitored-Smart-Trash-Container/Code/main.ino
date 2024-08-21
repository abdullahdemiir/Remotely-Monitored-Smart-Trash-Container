
#include <DHT.h>
#include <BlynkSimpleSIM800.h>
#include <TinyGPS++.h>
#include <Ultrasonic.h> // HC-SR04 for distance
#include <MQUnifiedsensor.h> // MQ-4 for gas

// Pin definitions
#define DHTPIN 2
#define DHTTYPE DHT11
#define TRIG_PIN 3
#define ECHO_PIN 4
#define MQ_PIN A0

// Initialize sensors
DHT dht(DHTPIN, DHTTYPE);
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);
MQUnifiedsensor MQ4("Arduino", 5.0, 10, MQ_PIN, "MQ-4");

// Blynk Auth Token
char auth[] = "YourAuthToken";

// Initialize GSM and GPS
#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
TinyGsm modem(Serial);
TinyGPSPlus gps;
BlynkTimer timer;

// Thresholds for notifications
float distanceThreshold = 10.0; // 10 cm threshold for trash fullness
float gasThreshold = 200.0; // Example threshold for gas concentration in PPM
float temperatureThreshold = 40.0; // Example threshold for temperature

void setup() {
  // Setup Serial, sensors, and Blynk
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(auth, modem, "YourAPN", "YourAPNuser", "YourAPNpass");

  // Initialize MQ-4
  MQ4.init();

  // Calibrate MQ-4 sensor
  Serial.print("Calibrating MQ-4...");
  MQ4.setRegressionMethod(1); // Use default regression method
  MQ4.setR0(10); // Set R0 value based on calibration
  Serial.println("Calibration done!");

  // Set timers for sending sensor data
  timer.setInterval(2000L, sendSensorData);
  timer.setInterval(5000L, sendGPSData);
}

void loop() {
  Blynk.run();
  timer.run();
  while (Serial.available() > 0) {
    gps.encode(Serial.read());
  }
}

void sendSensorData() {
  // Read data from DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Read distance from HC-SR04
  float distance = ultrasonic.Ranging(CM);
  
  // Read gas concentration from MQ-4
  float gasPPM = MQ4.readSensor();
  
  // Send data to Blynk app
  Blynk.virtualWrite(V5, humidity);
  Blynk.virtualWrite(V6, temperature);
  Blynk.virtualWrite(V7, distance);
  Blynk.virtualWrite(V8, gasPPM);

  // Print data to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %	");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C	");
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm	");
  Serial.print("Gas PPM: ");
  Serial.println(gasPPM);

  // Check thresholds and send notifications if necessary
  if (distance < distanceThreshold) {
    Blynk.notify("Warning: Trash container is almost full!");
  }

  if (gasPPM > gasThreshold) {
    Blynk.notify("Danger: High gas concentration detected!");
  }

  if (temperature > temperatureThreshold) {
    Blynk.notify("Alert: High temperature detected in the container!");
  }
}

void sendGPSData() {
  if (gps.location.isUpdated()) {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();
    
    // Send GPS data to Blynk
    Blynk.virtualWrite(V9, latitude);
    Blynk.virtualWrite(V10, longitude);
    
    // Print GPS data to Serial Monitor
    Serial.print("Latitude: ");
    Serial.print(latitude, 6);
    Serial.print(", Longitude: ");
    Serial.println(longitude, 6);
    
    // Notify with GPS data if certain conditions are met (e.g., gas threshold exceeded)
    if (MQ4.readSensor() > gasThreshold) {
      String gpsMessage = "High gas concentration detected! Location: " + String(latitude, 6) + ", " + String(longitude, 6);
      Blynk.notify(gpsMessage);
    }
  }
}
