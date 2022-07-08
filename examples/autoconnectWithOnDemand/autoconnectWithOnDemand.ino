//(1)-Inlude Library
#include <ESP32_WiFiManager.h>  //https://github.com/kingdiaw/ESP32_WiFiManager

ESP32_WiFiManager wm("ESP32Wifi-AP",2,15); //WiFi AP = "ESP32Wifi-AP", LED at Pin 2, Trigger at Pin 15


void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  wm.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  wm.running();
}
