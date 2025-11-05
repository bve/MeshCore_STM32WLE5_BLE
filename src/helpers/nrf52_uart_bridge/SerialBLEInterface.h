#pragma once

#include "../BaseSerialInterface.h"

#ifndef BLE_TX_POWER
#define BLE_TX_POWER 4
#endif

class SerialBLEInterface : public BaseSerialInterface {
  bool serialLock = false;

public:
  SerialBLEInterface();

  void startAdv();
  void stopAdv();
  void begin(const char *device_name, uint32_t pin_code);

  // BaseSerialInterface methods
  void enable() override;
  void disable() override;
  bool isEnabled() const override;

  bool isConnected() const override;

  bool isWriteBusy() const override;
  size_t writeFrame(const uint8_t src[], size_t len) override;
  size_t checkRecvFrame(uint8_t dest[]) override;
  
  void lockSerial() {
    while (serialLock) {
      delay(1);
    }
    serialLock = true;
  }

  void releaseSerial() {
    serialLock = false;
  }
};

#if BLE_DEBUG_LOGGING && ARDUINO
#include <Arduino.h>
#define BLE_DEBUG_PRINT(F, ...)   Serial.printf("BLE: " F, ##__VA_ARGS__)
#define BLE_DEBUG_PRINTLN(F, ...) Serial.printf("BLE: " F "\n", ##__VA_ARGS__)
#else
#define BLE_DEBUG_PRINT(...) \
  {                          \
  }
#define BLE_DEBUG_PRINTLN(...) \
  {                            \
  }
#endif
