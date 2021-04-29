// Centipede Shield Library
// Controls MCP23017 16-bit digital I/O chips

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Centipede.h"
#include <Wire.h>

uint8_t CSDataArray[2] = {0};

#define CSAddress 0b0100000

Centipede::Centipede()
{
  // no constructor tasks yet
}

// Set device to default values
void Centipede::initialize()
{

  for (int j = 0; j < 7; j++) {

    CSDataArray[0] = 255;
    CSDataArray[1] = 255;

    WriteRegisters(j, 0x00, 2);

    CSDataArray[0] = 0;
    CSDataArray[1] = 0;

    for (int k = 2; k < 0x15; k+=2) {
      WriteRegisters(j, k, 2);
    }

  }

}


void Centipede::WriteRegisters(int port, int startregister, int quantity) {

  Wire.beginTransmission(CSAddress + port);
#if defined(ARDUINO) && ARDUINO >= 100
    Wire.write((byte)startregister);
    for (int i = 0; i < quantity; i++) {
        Wire.write((byte)CSDataArray[i]);
    }
#else
    Wire.send((byte)startregister);
    for (int i = 0; i < quantity; i++) {
        Wire.send((byte)CSDataArray[i]);
    }
#endif

  Wire.endTransmission();

}

void Centipede::ReadRegisters(int port, int startregister, int quantity) {

  Wire.beginTransmission(CSAddress + port);
#if defined(ARDUINO) && ARDUINO >= 100
    Wire.write((byte)startregister);
    Wire.endTransmission();
    Wire.requestFrom(CSAddress + port, quantity);
    for (int i = 0; i < quantity; i++) {
        CSDataArray[i] = Wire.read();
    }
#else
    Wire.send((byte)startregister);
    Wire.endTransmission();
    Wire.requestFrom(CSAddress + port, quantity);
    for (int i = 0; i < quantity; i++) {
        CSDataArray[i] = Wire.receive();
    }
#endif

}


void Centipede::WriteRegisterPin(int port, int regpin, int subregister, int level) {

  ReadRegisters(port, subregister, 1);

  if (level == 0) {
    CSDataArray[0] &= ~(1 << regpin);
  }
  else {
    CSDataArray[0] |= (1 << regpin);
  }

  WriteRegisters(port, subregister, 1);

}

void Centipede::pinMode(int pin, int mode) {

  int port = pin >> 4;
  int subregister = (pin & 8) >> 3;

  int regpin = pin - ((port << 1) + subregister)*8;

  WriteRegisterPin(port, regpin, subregister, mode ^ 1);

}

void Centipede::pinPullup(int pin, int mode) {

  int port = pin >> 4;
  int subregister = (pin & 8) >> 3;

  int regpin = pin - ((port << 1) + subregister)*8;

  WriteRegisterPin(port, regpin, 0x0C + subregister, mode);

}


void Centipede::digitalWrite(int pin, int level) {

  int port = pin >> 4;
  int subregister = (pin & 8) >> 3;

  int regpin = pin - ((port << 1) + subregister)*8;

  WriteRegisterPin(port, regpin, 0x12 + subregister, level);

}

int Centipede::digitalRead(int pin) {

  int port = pin >> 4;
  int subregister = (pin & 8) >> 3;

  ReadRegisters(port, 0x12 + subregister, 1);

  int returnval = (CSDataArray[0] >> (pin - ((port << 1) + subregister)*8)) & 1;

  return returnval;

}

void Centipede::portMode(int port, int value) {

  CSDataArray[0] = value;
  CSDataArray[1] = value>>8;

  WriteRegisters(port, 0x00, 2);

}

void Centipede::portWrite(int port, int value) {

  CSDataArray[0] = value;
  CSDataArray[1] = value>>8;

  WriteRegisters(port, 0x12, 2);

}

void Centipede::portInterrupts(int port, int gpintval, int defval, int intconval) {

  WriteRegisterPin(port, 6, 0x0A, 1);
  WriteRegisterPin(port, 6, 0x0B, 1);

  CSDataArray[0] = gpintval;
  CSDataArray[1] = gpintval>>8;

  WriteRegisters(port, 0x04, 2);

  CSDataArray[0] = defval;
  CSDataArray[1] = defval>>8;

  WriteRegisters(port, 0x06, 2);

  CSDataArray[0] = intconval;
  CSDataArray[1] = intconval>>8;

  WriteRegisters(port, 0x08, 2);

}

int Centipede::portCaptureRead(int port) {

  ReadRegisters(port, 0x10, 2);

  int receivedval = CSDataArray[0];
  receivedval |= CSDataArray[1] << 8;

  return receivedval;

}

void Centipede::portIntPinConfig(int port, int drain, int polarity) {

  WriteRegisterPin(port, 1, 0x0A, drain);
  WriteRegisterPin(port, 1, 0x0B, drain);
  WriteRegisterPin(port, 0, 0x0A, polarity);
  WriteRegisterPin(port, 0, 0x0B, polarity);

}

void Centipede::portPullup(int port, int value) {

  CSDataArray[0] = value;
  CSDataArray[1] = value>>8;

  WriteRegisters(port, 0x0C, 2);

}

int Centipede::portRead(int port) {

  ReadRegisters(port, 0x12, 2);

  int receivedval = CSDataArray[0];
  receivedval |= CSDataArray[1] << 8;

  return receivedval;

}




