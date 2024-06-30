/** Includes **/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <DHT.h>

/** Macro Definitions **/
#define DHT_PIN 2 
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

#define TFT_CS 10 // Chip Select Pin
#define TFT_RST 9 // Reset Pin
#define TFT_DC 8 // Data/Command Pin
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);
  dht.begin(); // Initialize Humidity and Temp sensor
  
  tft.initR(INITR_BLACKTAB); // Initialize Display
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK); // Fill black screen

  pinMode(3, INPUT); // Set Digital Pin 3 to from Flame Sensor
  pinMode(A0, INPUT); // Set Analog Pin 0 to Photo Resistor
}

void loop() {
  delay(2000); // 2000ms -> 2s delay for loop
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  // If the temperature or humidity is not a number.
  if (isnan(hum) || isnan(temp)) { 
    Serial.println(F("Failed to read from HT Sensor")); // F-> Flash memory.
    return; // Break out of the loop.
  }

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
  
  sprintf(buf, "Flame: %s", flameDetected == LOW ? "Detected" : "No");
  tft.setCursor(0, 90);
  tft.println(String(buf)); // Print Whether a flame has been detected or not
}
