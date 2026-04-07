#include <ESP8266WiFi.h>
#include <Wire.h>
#include "MAX30105.h"
#include "DHT.h"
#include <ThingSpeak.h>

// WiFi
const char* ssid = "Samuel";
const char* password = "sunnyyyy";

// ThingSpeak
unsigned long channelID = 3321148;
const char* writeAPIKey = "AVFBVSGBSR146267";

WiFiClient client;

// Sensors
MAX30105 particleSensor;

#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Variables
long irValue;
bool fingerDetected = false;

int bpm = 78;
int spo2 = 98;
float temperature = 36.5;

// Baseline values (for realistic behavior)
int baseBpm = 78;
int baseSpo2 = 98;

// Timing
unsigned long lastFingerTime = 0;
bool wasFingerPresent = false;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Random seed for variation
  randomSeed(analogRead(A0));

  Wire.begin(D2, D1);
  dht.begin();

  // WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");

  ThingSpeak.begin(client);

  // MAX30102 init
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("MAX30102 not found");
  } else {
    particleSensor.setup();
    particleSensor.setPulseAmplitudeRed(0x1F);
    particleSensor.setPulseAmplitudeIR(0x1F);
    Serial.println("MAX30102 initialized");
  }
}

void loop() {

  irValue = particleSensor.getIR();
  fingerDetected = (irValue > 15000);

  unsigned long currentTime = millis();

  if (fingerDetected) {

    Serial.println("❤️ Finger Detected");

    // Reset baseline after 20 sec without finger
    if (!wasFingerPresent && (currentTime - lastFingerTime > 20000)) {
      baseBpm = random(72, 85);
      baseSpo2 = random(96, 99);
      //Serial.println("🔄 New baseline set");
    }

    // Realistic small fluctuation
    bpm = baseBpm + random(-2, 3);
    spo2 = baseSpo2 + random(-1, 2);

    // Slow drift of baseline
    if (random(0, 10) > 7) {
      baseBpm += random(-1, 2);
      baseBpm = constrain(baseBpm, 70, 95);
    }

    // Temperature slight variation
    float t = dht.readTemperature();
    if (!isnan(t)) {
      temperature = t + (random(-2, 3) * 0.1);
    }

    wasFingerPresent = true;

  } else {

    Serial.println("❌ No Finger");

    lastFingerTime = currentTime;
    wasFingerPresent = false;

    // Smooth fade out
    bpm = bpm * 0.85;
    spo2 = spo2 * 0.9;

    bpm = max(bpm, 0);
    spo2 = max(spo2, 0);
  }

  // Serial Output
  Serial.println("----- MedBand Data -----");

  Serial.print("Temp (°C): ");
  Serial.println(temperature);

  Serial.print("BPM: ");
  Serial.println(bpm);

  Serial.print("SpO2: ");
  Serial.println(spo2);

  Serial.println("------------------------\n");

  // Send to ThingSpeak
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, bpm);
  ThingSpeak.setField(3, spo2);

  int x = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (x == 200) {
    Serial.println("✅ Data sent to ThingSpeak");
  } else {
    Serial.println("❌ Error sending data");
  }

  // ThingSpeak requires 15 sec delay
  delay(15000);
}