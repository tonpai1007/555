#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


#define FIREBASE_HOST "ledesp-a504c.firebaseio.com"
#define FIREBASE_AUTH "sYDADpft1w4oF9gkwgFbmdBeoELvsxR7Dzynq9zt "

// Config connect WiFi
#define WIFI_SSID "SMTE"
#define WIFI_PASSWORD "smatsppk"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
Adafruit_SSD1306 OLED(OLED_RESET);




int i = 0;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3c);
}

void loop() {

  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setCursor(15,0);
  OLED.setTextSize(0.5);
  OLED.println("set /number to ");
 OLED.println(Firebase.getInt("number"));
  OLED.display();
  Firebase.setInt("number", i);
  if (Firebase.failed()) {
      Serial.print("set /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("set /number to ");
  Serial.println(Firebase.getInt("number"));
  
  i++;
  delay(5);
}
