/** Includes **/
#include <WiFiS3.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

/** Pin Definitions **/
const int buttonPin = 2;
const int ledPin = 3;
const int TFT_CS = 10;
const int TFT_DC = 9;
const int TFT_RST = 8;
const int DOT_DELAY = 200;
const int DASH_DELAY = 600;
const int DOT_DASH_GAP = 200;

/** Wi-Fi Credentials **/
const char* ssid = "";
const char* password = "";
WiFiServer server(80);
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

/** Setup Function **/
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);
  tft.init(240, 320);
  tft.setRotation(0);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting To WiFi...");
  }
  Serial.println("Connected to WiFi!");
  server.begin();
}

/** Main Loop **/
void loop() {
  WiFiClient client = server.available();
  if(client) {
    String message = "";
    while(client.connected()) {
      if(client.available()) {
        char c = client.read();
        message += c;
        if(c == '\n') {
          String decodedMsg = decodeMorse(message);
          tft.fillScreen(ST77XX_BLACK);
          tft.setCursor(0, 0); // Cursor to top right of display
          tft.setTextColor(ST77XX_WHITE);
          tft.setTextSize(2);
          tft.println(decodedMsg);
          message = "";
        }
      }
    }
    client.stop();
  }

  // 
  if(digitalRead(buttonPin) == LOW) {
    String msg = "... --- ..."; // Example Message (SOS)
    sendMorse(msg);
    delay(1000); // debouncing delay
  }
}

/** Morse Transmission Function **/
void sendMorse(String message) {
  for(char c: message) {
    if(c == '.') {
      digitalWrite(ledPin, HIGH);
      delay(DOT_DELAY);
      digitalWrite(ledPin, LOW);
    } else if(c == '-') {
      digitalWrite(ledPin, HIGH);
      delay(DASH_DELAY);
      digitalWrite(ledPin, LOW);
    }
    delay(DOT_DASH_GAP);
  }
}

/** Morse Decoding Function **/
String decodeMorse(String message) {
  // @TODO: Implement!!
}
