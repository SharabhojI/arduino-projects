/** Includes **/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <DHT.h>

/** Macro Definitions **/
#define DHT_PIN 4 
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

#define TFT_CS 10 // Chip Select Pin
#define TFT_RST 8 // Reset Pin
#define TFT_DC 9 // Data/Command Pin
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);
  dht.begin(); // Initialize Humidity and Temp sensor
  
  tft.init(240, 320); // Initialize Display
  tft.setRotation(0);
  tft.fillScreen(ST77XX_BLACK); // Fill black screen

  pinMode(3, INPUT); // Set Digital Pin 3 to from Flame Sensor
  pinMode(A0, INPUT); // Set Analog Pin 0 to Photo Resistor
}

void loop() {
  delay(5000); // 5000ms -> 5s delay for loop
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  int lightLevel = analogRead(A0); // Read light level from pin A0
  int flameDetected = digitalRead(3); // Read flame sensor from D3
  
  char buf[128]; // Buffer for string formatting

  /* Clear the TFT Display Module */
  tft.fillScreen(ST77XX_BLACK); // Black Screen
  tft.setCursor(0, 0); // Cursor to top right
  tft.setTextColor(ST77XX_WHITE); // White Text
  tft.setTextSize(2);
  tft.println("Monitoring Station");
  tft.setTextSize(1);

  /* Printing to the Display */
  sprintf(buf, "Temperature: %.1f C", temp);
  tft.setCursor(0, 30);
  tft.println(String(buf)); // Print Temperature (rounded to the nearest Tenth)
    
  sprintf(buf, "Humidity: %.1f %%", hum);
  tft.setCursor(0, 50);
  tft.println(String(buf)); // Print Humidity (rounded to the nearest Tenth)
  
  sprintf(buf, "Light: %d", lightLevel);
  tft.setCursor(0, 70);
  tft.println(String(buf)); // Print Light Level
  
  sprintf(buf, "Flame Detected?: %s", flameDetected == HIGH ? "Yes" : "No");
  tft.setCursor(0, 90);
  tft.println(String(buf)); // Print Whether a flame has been detected or not
}
