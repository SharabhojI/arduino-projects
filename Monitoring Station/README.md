# Monitoring Station Project

This is a simple monitoring station using an Arduino Uno, various sensors, and a TFT SPI display.
The station monitors temperature, humidity, light level, and flame detection, displaying the results on the TFT screen.

## Components

- **Arduino Uno (R4 with WiFi)**
  - Microcontroller board used to interface with sensors and the display.
- **Temperature and Humidity Sensor (DHT11)**
  - Measures temperature and humidity.
- **Photoresistor (KY-018)**
  - Measures light intensity.
- **Flame Sensor (KY-026)**
  - Detects the presence of flame.
- **2.0 inch TFT Display (ST7789)**
  - Displays sensor readings.

## Connections

1. **DHT11 Sensor**
   - **VCC**: 5V
   - **GND**: GND
   - **Data**: Digital Pin 4
2. **Photoresistor (KY-018)**
   - **VCC**: 5V
   - **GND**: GND
   - **Analog Output**: Analog Pin A0
3. **Flame Sensor (KY-026)**
   - **VCC**: 5V
   - **GND**: GND
   - **Digital Output**: Digital Pin 3
4. **TFT Display (ST7789)**
   - **GND**: GND
   - **VCC**: 3.3V
   - **SCK**: Digital Pin 13
   - **MOSI**: Digital Pin 11
   - **RST**: Digital Pin 8
   - **DC**: Digital Pin 9
   - **CS**: Digital Pin 10

## Functionality

- **Temperature and Humidity Monitoring**
  - The DHT11 sensor measures the ambient temperature and humidity.
- **Light Level Monitoring**
  - The photoresistor measures the ambient light intensity.
- **Flame Detection**
  - The flame sensor detects the presence of a flame and outputs a signal.
- **Display Output**
  - The ST7789 TFT display shows the measured temperature, humidity, light level, and flame detection status.

## Setup

1. Connect the components as described in the Connections section.
2. Upload the provided `.ino` file to your Arduino using the Arduino IDE.
3. Ensure the libraries `Adafruit_GFX`, `Adafruit_ST7789`, and `DHT` are installed in the Arduino IDE.

## Usage

Once the setup is complete, the monitoring station will display the sensor readings on the TFT display, refreshing every 5 seconds.