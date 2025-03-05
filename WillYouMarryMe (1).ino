/*
  Smart Marriage Proposal

  This sketch is designed for a smart marriage proposal. It detects movement in a room using an ultrasonic sensor.
  If movement is detected, a "Will you marry me?" message appears in the Blynk app.
  The partner then needs to respond by pressing either "Yes" or "No" on the dashboard.
  Based on the response, different music will be played.

  The circuit:
  * Ultrasonic Sensor (HC-SR04):
    - TRIGGER_PIN (GPIO 5) -> Trigger input
    - ECHO_PIN (GPIO 18) -> Echo output

  * MP3 Module (RedMP3 or DFPlayer Mini):
    - MP3_RECIVE_PIN (GPIO 22) -> MP3 Rx
    - MP3_TRANSMIT_PIN (GPIO 21) -> MP3 Tx

  * ESP32 Board:
    - Connected to WiFi and Blynk cloud

  Video link: https://www.youtube.com/watch?v=WXQfzwyf47M
  Created By:
  Rony Rabinovitz 314834425
  Assaf Ramati 209252154
*/
#include "RedMP3.h"
// #include <SoftwareSerial.h> // NEED EspSoftwareSerial !!!

#define TRIGGER_PIN 5  // Pin for the ultrasonic sensor trigger
#define ECHO_PIN 18    // Pin for receiving the echo signal

#define MP3_RECIVE_PIN 22  // MP3 module RX pin
#define MP3_TRANSMIT_PIN 21 // MP3 module TX pin

// Initialize MP3 module with specified Rx and Tx pins
MP3 mp3(MP3_RECIVE_PIN, MP3_TRANSMIT_PIN);

#define BLYNK_TEMPLATE_ID "TMPL6JJBkqVhL"
#define BLYNK_TEMPLATE_NAME "Rony"
#define BLYNK_AUTH_TOKEN "JIEVsuwt15-GdLlnPriIQ5yXvpBkK3vU"

#include <BlynkSimpleEsp32.h>

long duration;  // Stores duration of echo pulse
float distance; // Stores calculated distance in cm

void setup() {
  Serial.begin(115200); // Start serial communication

  Blynk.begin(BLYNK_AUTH_TOKEN, "rembar", "15280619"); // Connect ESP32 to Blynk cloud

  pinMode(TRIGGER_PIN, OUTPUT); // Set ultrasonic sensor trigger pin as output
  pinMode(ECHO_PIN, INPUT);     // Set ultrasonic sensor echo pin as input

  delay(50);
  mp3.setVolume(25); // Set initial volume for MP3 module
  delay(50);
}

void loop() {
  Blynk.run();       // Run Blynk process to keep connection alive
  handlaDistance();  // Measure distance using ultrasonic sensor
  Handle_BLYNK();    // Send distance status to Blynk app
}

void handlaDistance() {
  // Send a 10µs pulse to trigger pin to start measurement
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Read echo pin duration (timeout at 500ms to avoid hanging)
  duration = pulseIn(ECHO_PIN, HIGH, 500000);

  // Convert duration to distance in cm (speed of sound used for calculation)
  distance = (duration * 0.0343) / 2;

  // Print distance to Serial Monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100);  // Small delay before the next measurement
}

void Handle_BLYNK() {
  // If an object is detected within 100cm, send "1" to Blynk app (movement detected)
  if (distance < 100) {
    Blynk.virtualWrite(V0, 1); // Update virtual pin V0 with detected status
    Serial.println("  1  "); // Print status to serial monitor
  }
  else {
    Blynk.virtualWrite(V0, 0); // Update virtual pin V0 with no movement status
    Serial.println("  0  "); // Print status to serial monitor
  }
}

// Function triggered when "Yes" button is pressed in Blynk app
BLYNK_WRITE(V1) {
  if (param.asInt() == 1) {
    Serial.println("                YYYEEESSSSSSSS  "); // Confirmation message for Yes
    mp3.playWithFileName(01, 01); // Play positive response audio
    delay(10000);  // Wait for the audio to finish playing
    mp3.stopPlay(); // Stop playback
  }
}

// Function triggered when "No" button is pressed in Blynk app
BLYNK_WRITE(V2) {
  if (param.asInt() == 1) {
    Serial.println("                  NNNNNOOOOOO  "); // Confirmation message for No
    mp3.playWithFileName(01, 02); // Play rejection audio
    delay(2000);  // Wait for the audio to finish playing
    mp3.stopPlay(); // Stop playback
  }
}
