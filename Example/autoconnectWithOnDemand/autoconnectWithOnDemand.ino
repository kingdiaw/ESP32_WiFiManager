//(1)-Inlude Library
#include "ESP32_WiFiManager.h"

ESP32_WiFiManager wm("TestLib",2,15); //WiFi AP = "TestLib", LED at Pin 2, Trigger at Pin 15


void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  wm.isAutoConnect();
}

//====================== LOOP ===========================
void loop() {
  // put your main code here, to run repeatedly:
  wm.running();
}
