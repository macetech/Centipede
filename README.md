# Centipede Shield Library

## Reference

The main documentation is reported in [macetech wiki](https://docs.macetech.com/doku.php/centipede_shield)

Nevertheless this could be outdated (eg .getIntF is missing in the wiki currently).

## Methods

* .digitalWrite([0...127], [LOW...HIGH]) - Acts like normal digitalWrite
* .digitalRead([0...127]) - Acts like normal digitalRead
* .pinMode([0...127], [INPUT...OUTPUT]) - Acts like normal pinMode
* .pinPullup([0...127], [LOW...HIGH]) - Activates internal 100K pullups on inputs when HIGH.
* .portWrite([0...7], [0...65535]) - Writes 16-bit value to one port (chip). Useful for writing 16 outputs at the same time.
* .portRead([0...7]) - Reads 16-bit value from one port (chip)
* .portMode([0...7], [0...65535]) - Write I/O mask to one port (chip). In binary, a 0 means output and a 1 means input. Easier to use than a long list of pinMode() commands.
* .portPullup([0...7], [0...65535]) - Sets pullups on one port (chip). In binary, a 0 means no pullup and a 1 means pullup is active.
* .portInterrupts([0...7],[0...65535],[0...65535],[0...65535]) - Configure interrupts
*                 [device number],[use interrupt on pin],[default value],[interrupt when != default]
* .portCaptureRead(0...7) - Reads 16-bit value registers as they were when interrupt occurred
* .getIntF(0..7) - These return an interrupt flag state that allows you to determine which port (device) produced an interrupt (and it could be more than one device).
* .init() - Sets all registers to initial values

