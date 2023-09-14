# arduino-laser-communication
Repository featuring experiment regarding light based communication system with 2 independent Arduino devices by using laser.

**Research / experimental project**
Light based communication system which consists of:
- Arduino Uno R3 and Arduino Uno
- KY-008 laser module
- LDR (receiver) module

**How the system works?**
Arduino Uno (#1) listens on serial port for incoming message user wants to send.
When user typed message received, it transmits that same message bit by bit (not byte) by using OOK modulation 
over laser module. Laser pulses (bits) are transmitted in time interval of 10 miliseconds.

Speed: 80 bps (10 bytes / sec)

Arduino Uno R3 (#2) listens for incoming laser pulses (checks LDR analog value) 
and converts the value into binary value regarding of the set threshold.
Bits are then converted back by using bitwise operation to reconstruct the character.

**Laser modulation method**
System implements basic modulation called OOK (on/off keying) since laser module is not capable doing 
other types of modulations.

**Synchronization method**
As we are using 2 independent devices without external RTC or similar synchronization mechanism, synchronization over digital pin 
has been implemented. When Arduino #1 sends the message, is signals to the Arduino #2 that it could start receiving the data.

**Sender device**

![image](https://github.com/NightRider92/arduino-laser-communication/assets/10942663/26e358ea-abb7-4d4f-bb15-50c789c5f151)

**Receiver device**

![image](https://github.com/NightRider92/arduino-laser-communication/assets/10942663/a6926f9b-e4e0-43fc-8e63-ceacc34baa08)

**Setup**

![image](https://github.com/NightRider92/arduino-laser-communication/assets/10942663/3d5430d0-fd39-4df3-9448-b7821ebb6352)
