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
