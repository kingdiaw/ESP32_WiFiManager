/*
  ESP32_WiFiManager.h Library for autoconnect WiFi or setup
  using ConfigPortal
  Modifed from  https://github.com/tzapu/WiFiManager
*/
#ifndef ESP32_WiFiManager_h
#define ESP32_WiFiManager_h

#include "Arduino.h"
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

class ESP32_WiFiManager
{
  public:
    ESP32_WiFiManager(const char* name_AP, int pinLed = 2, int pinTrigger = 15);
    void begin();
    bool isAutoConnect();
    void blinkStatus(int interval);
    void running();
  private:
    int _pinLed;
    int _pinTrigger;
    bool _isConfigPortal;
    const char* _name_AP;
    const int _timeout = 120;
    const int _fast = 50;
    const int _medium = 250;
    const int _slow = 2500;
};
#endif
