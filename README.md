# MP3 & Blynk-Controlled Ultrasonic Sensor System

This project combines an ultrasonic sensor, an MP3 audio module, and Blynk integration to detect motion and trigger audio responses remotely via a mobile app.

## Features

- Measures distance using an ultrasonic sensor (HC-SR04 or equivalent).
- Plays audio feedback (Yes/No) via MP3 module (e.g., DFPlayer or compatible).
- Integrates with Blynk IoT platform for real-time monitoring and control.
- Sends detection status (movement or no movement) to Blynk app.
- Allows the user to trigger pre-recorded responses through Blynk buttons.

## Hardware Requirements

- ESP32 board
- Ultrasonic Sensor (e.g., HC-SR04)
- MP3 Module (e.g., DFPlayer Mini or RedMP3)
- MicroSD card with audio files named 01/01.mp3 (Yes) and 01/02.mp3 (No)
- Power supply for ESP32 and MP3 module
- Breadboard and jumper wires

## Pin Configuration

| Component          | ESP32 Pin       |
|--------------------|-----------------|
| Ultrasonic Trigger | 5               |
| Ultrasonic Echo    | 18              |
| MP3 RX             | 22              |
| MP3 TX             | 21              |

## How It Works

1. The ultrasonic sensor continuously measures the distance to nearby objects.
2. If an object is detected within 100 cm, it updates virtual pin `V0` in the Blynk app to indicate motion.
3. The Blynk app provides two buttons:
   - `V1` (Yes): Plays audio file `01/01.mp3`.
   - `V2` (No): Plays audio file `01/02.mp3`.
4. Audio is played through the MP3 module, and playback is stopped after the file duration.

## Software Requirements

- [Blynk library](https://github.com/blynkkk/blynk-library)
- RedMP3 or compatible MP3 library
- ESP32 board package in Arduino IDE
- Correct WiFi credentials and Blynk Auth Token

## WiFi & Blynk Setup

Make sure to replace the following in the code:
```cpp
Blynk.begin(BLYNK_AUTH_TOKEN, "YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD");
