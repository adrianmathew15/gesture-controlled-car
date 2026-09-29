# Gesture-Controlled Car

An ESP8266-based car controlled by hand gestures. An MPU6050 motion sensor on
the sender measures tilt, and the sender transmits movement commands to the car
over ESP-NOW.

## Repository layout

```text
firmware/
  sender/                 Gesture controller and MPU6050 code
  receiver/               Car motor-control receiver
examples/
  blink/                  Basic board/LED test
  esp32-mac-address/      Utility sketch that prints an ESP32 MAC address
docs/
  gesture-controlled-car-report.docx  Original technical project report
  demo.mp4                Video demonstration of the completed car
```

## Hardware

- Two ESP8266-compatible boards for the sender and receiver
- MPU6050 accelerometer/gyroscope
- Motor driver and two DC motors
- Suitable power supplies for the controller and car

## Arduino setup

1. Install ESP8266 board support in the Arduino IDE.
2. Install **Adafruit MPU6050** through the Arduino Library Manager. Its
   dependencies include **Adafruit Unified Sensor** and **Adafruit BusIO**.
3. Open `firmware/receiver/receiver.ino`, select the receiver's ESP8266 board,
   and upload it.
4. Set `broadcastAddress` near the top of
   `firmware/sender/sender.ino` to the receiver board's MAC address.
5. Open the sender sketch, select the sender's ESP8266 board, and upload it.

The `examples/esp32-mac-address` sketch uses the ESP32 `WiFi.h` API. For an
ESP8266, obtain its station MAC address using `ESP8266WiFi.h` instead.

## Notes

- The ESP-NOW message structure in the sender and receiver must remain
  identical.
- Motor GPIO assignments are declared at the top of the receiver sketch.
- The repository does not vendor Arduino libraries. Install dependencies using
  the Arduino Library Manager so library versions can be managed separately.

