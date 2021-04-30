// Centipede Shield Library
// Controls MCP23017 16-bit digital I/O chips

#ifndef Centipede_h
#define Centipede_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

extern uint8_t CSDataArray[2];

class Centipede
{
  public:
    Centipede();
    void pinMode(int pin, int mode);
    void pinPullup(int pin, int mode);
    void digitalWrite(int pin, int level);
    int digitalRead(int pin);
    void portMode(int port, int value);
    void portPullup(int port, int value);
    void portWrite(int port, int value);
    int portRead(int port);
    void portInterrupts(int port, int gpintval, int defval, int intconval);
    uint16_t getIntF(int port);
    int portCaptureRead(int port);
    void portIntPinConfig(int port, int drain, int polarity);
    void initialize();
  //private:
    void WriteRegisters(int port, int startregister, int quantity);
    void ReadRegisters(int port, int startregister, int quantity);
    void WriteRegisterPin(int port, int regpin, int subregister, int level);
};

#endif
