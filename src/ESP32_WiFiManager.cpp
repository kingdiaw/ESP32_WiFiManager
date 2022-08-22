#include "Arduino.h"
#include <WiFiManager.h>
#include "ESP32_WiFiManager.h"

WiFiManager _wm;

ESP32_WiFiManager::ESP32_WiFiManager(const char* name_AP, int pinLed , int pinTrigger, int trigState)
{
  pinMode(pinLed, OUTPUT);
  pinMode (pinTrigger, INPUT_PULLUP);
  _pinLed = pinLed;
  _pinTrigger = pinTrigger;
  _name_AP = name_AP;
  _trigState = trigState;
}

void ESP32_WiFiManager::begin() {
  _wm.setConfigPortalBlocking(false);
  _wm.setConfigPortalTimeout(_timeout);
  if (_wm.autoConnect(_name_AP)) {
    Serial.println("connected...yeey :)");
    _isConfigPortal = false;
  }
  else {
    Serial.println("Configportal running");
    _isConfigPortal = true;
  }
}

bool ESP32_WiFiManager::isAutoConnect() {
  _wm.setConfigPortalBlocking(false);
  _wm.setConfigPortalTimeout(_timeout);
  if (_wm.autoConnect(_name_AP)) {
    Serial.println("connected...yeey :)");
    _isConfigPortal = false;
  }
  else {
    Serial.println("Configportal running");
    _isConfigPortal = true;
  }
  return !_isConfigPortal;
}

void ESP32_WiFiManager::blinkStatus(int interval) {
  static uint32_t __tick;
  if (__tick < millis()) {
    __tick = millis() + interval;
    digitalWrite (_pinLed, digitalRead(_pinLed) ^ 1);
  }
}

void ESP32_WiFiManager::running() {
  static uint16_t __interval_ms;
  _wm.process();

  if (WiFi.status() == WL_CONNECTED) {
    __interval_ms = _medium;
    _isConfigPortal = false;
  }
  else if (WiFi.status() != WL_CONNECTED) {
    __interval_ms = _slow;
  }
  
  if (_isConfigPortal) {
    __interval_ms = _fast;
  }

  if (digitalRead (_pinTrigger) == _trigState) {
    //reset settings - for testing
    _wm.resetSettings();

    // set configportal timeout
    _wm.setConfigPortalTimeout(_timeout);

    if (!_wm.startConfigPortal(_name_AP)) {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.restart();
      delay(5000);
    }
  }
  blinkStatus (__interval_ms);
}
