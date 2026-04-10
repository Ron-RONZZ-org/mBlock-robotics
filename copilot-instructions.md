# Copilot instructions for this repository

- Target platform: mBot Ranger / Me Auriga with `MeAuriga.h` and `Wire.h`.
- Follow repository naming: `<NN>-<short-kebab-name>/<NN>-<short-kebab-name>.ino`.
- Start from `template.ino` structure: global section, `setup()`, `loop()`, short intervals with `millis()`.
- Keep Serial output clear and educational (used as mBlock "say"/debug feedback).
- Reuse common ports used in this repo:
  - Ultrasonic: port `10`
  - Light sensors: `12` and `11`
  - Sound sensor: `14`
  - RGB LED ring: `MeRGBLed led(0, 12)` with `led.setpin(44)`
  - Gyroscope: `MeGyro gyroSensor(0, 0x69)` then `gyroSensor.begin()` + `gyroSensor.update()`
- Keep code simple and student-friendly; avoid unnecessary abstractions.
