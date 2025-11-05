#include "SerialBLEInterface.h"

#include <cctype>
#include <cstdlib>
#include <cstring>

extern "C" void HardFault_Handler(void) {
  while (1) {
    Serial.println("HardFault!");
    delay(1000);
  }
}

void reboot() {
  NVIC_SystemReset();
  delay(1000);
}

#define MySerial SerialLP1

String readString(unsigned long timeout = 10000) {
  MySerial.setTimeout(timeout);
  String data = MySerial.readStringUntil('\n');
  data.trim();
  return data;
}

SerialBLEInterface::SerialBLEInterface() {
  MySerial.begin(115200);
}

void SerialBLEInterface::startAdv() {
  MySerial.println("&STA");
}

void SerialBLEInterface::stopAdv() {
  MySerial.println("&STP");
}

void SerialBLEInterface::begin(const char *device_name, uint32_t pin_code) {
  lockSerial();
  MySerial.println();
  MySerial.println("&BEG " + String(device_name) + " " + String(pin_code));
  releaseSerial();
}

void SerialBLEInterface::enable() {
  MySerial.println("&ENA");
}

void SerialBLEInterface::disable() {
  MySerial.println("&DIS");
}

bool SerialBLEInterface::isEnabled() const {
  MySerial.println("&ISE");
  bool is_enabled = readString() == "1";
  return is_enabled;
}

bool SerialBLEInterface::isConnected() const {
  MySerial.println("&ISC");
  bool is_connected = readString() == "1";
  return is_connected;
}

bool SerialBLEInterface::isWriteBusy() const {
  MySerial.println("&ISW");
  bool is_busy = readString() == "1";
  return is_busy;
}

size_t SerialBLEInterface::writeFrame(const uint8_t src[], size_t len) {
  lockSerial();
  MySerial.println("&WRI " + String(len));
  MySerial.flush();

  MySerial.find("RDY");

  MySerial.write(src, len);

  MySerial.flush();
  MySerial.println();
  releaseSerial();

  String resp = readString();

  if (resp.startsWith("REBOOT")) {
    reboot();
    return 0; // no bytes received
  }

  if (!resp.startsWith("ERR")) {
    return static_cast<size_t>(std::strtol(resp.c_str(), nullptr, 10));
  }

  MySerial.println("ERR: WRITE error: " + resp);
  return 0;
}

size_t SerialBLEInterface::checkRecvFrame(uint8_t dest[]) {
  delay(100);

  lockSerial();
  MySerial.println("&CHE");
  releaseSerial();

  String resp = readString();

  if (resp.startsWith("REBOOT")) {
    reboot();

    return 0; // no bytes received
  }

  if (!resp.startsWith("ERR")) {
    size_t len = static_cast<size_t>(std::strtol(resp.c_str(), nullptr, 10));

    if (len > 0) {
      MySerial.print("RDY");
      size_t bytesRead = MySerial.readBytes(dest, len);

      if (bytesRead != len) {
        MySerial.println("ERR: READ error, expected " + String(len) + " bytes, got " + String(bytesRead) +
                         " bytes");
      }

      return bytesRead;
    }

    return 0;
  }

  return 0; // no bytes received
}