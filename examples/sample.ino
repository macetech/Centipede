// Example code for Centipede Library
// Works with Centipede Shield or MCP23017 on Arduino I2C port
 
#include <Wire.h>
#include <Centipede.h>
 
 
/* Available commands
  .digitalWrite([0...127], [LOW...HIGH]) - Acts like normal digitalWrite
  .digitalRead([0...127]) - Acts like normal digitalRead
  .pinMode([0...127], [INPUT...OUTPUT]) - Acts like normal pinMode
  .portWrite([0...7], [0...65535]) - Writes 16-bit value to one port (chip)
  .portRead([0...7]) - Reads 16-bit value from one port (chip)
  .portMode([0...7], [0...65535]) - Write I/O mask to one port (chip)
  .pinPullup([0...127], [LOW...HIGH]) - Sets pullup on input pin
  .portPullup([0...7], [0...65535]) - Sets pullups on one port (chip)
  .portInterrupts([0...7],[0...65535],[0...65535],[0...65535]) - Configure interrupts
                  [device number],[use interrupt on pin],[default value],[interrupt when != default]
  .portCaptureRead(0...7) - Reads 16-bit value registers as they were when interrupt occurred
  .init() - Sets all registers to initial values
 
  Examples
  CS.init();
  CS.pinMode(0,OUTPUT);
  CS.digitalWrite(0, HIGH);
  int recpin = CS.digitalRead(0);
  CS.portMode(0, 0b0111111001111110); // 0 = output, 1 = input
  CS.portWrite(0, 0b1000000110000001); // 0 = LOW, 1 = HIGH
  int recport = CS.portRead(0);
  CS.pinPullup(1,HIGH);
  CS.portPullup(0, 0b0111111001111110); // 0 = no pullup, 1 = pullup
  CS.portInterrupts(0,0b0000000000000001,0b0000000000000000,0b0000000000000001);
*/
 
Centipede CS; // create Centipede object
 
 
void setup()
{
  Wire.begin(); // start I2C
 
  CS.initialize(); // set all registers to default
 
  CS.portMode(0, 0b0000000000000000); // set all pins on chip 0 to output (0 to 15)
  //CS.portMode(1, 0b0000000000000000); // set all pins on chip 1 to output (16 to 31)
 
  //TWBR = 12; // uncomment for 400KHz I2C (on 16MHz Arduinos)
 
}
 
 
void loop()
{  
  for (int i = 0; i < 16; i++) {
    CS.digitalWrite(i, HIGH);
    delay(10);
  }
 
  for (int i = 0; i < 16; i++) {
    CS.digitalWrite(i, LOW);
    delay(10);
  } 
}
