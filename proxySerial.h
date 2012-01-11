//
// μLCD-32PT(SGC) 3.2” Serial LCD Display Module
// Arduino & chipKIT Library
//
// Jan 11, 2012 release 23 - see README.txt
// © Rei VILO, 2010-2012
// CC = BY NC SA
// http://sites.google.com/site/vilorei/
// http://github.com/rei-vilo/Serial_LCD
//
//
// Based on
// 4D LABS PICASO-SGC Command Set
// Software Interface Specification
// Document Date: 1st March 2011 
// Document Revision: 6.0
// http://www.4d-Labs.com
//
//
#define PROXYSERIAL_RELEASE 23

#include "WProgram.h"
#include "Stream.h"

#define securityDelay 0

#ifndef proxy_Serial_h
#define proxy_Serial_h

// Utilities

String ftoa(float number, byte precision, byte size);


// Objects

class ProxySerial
{
public:
  ProxySerial(Stream * port0);

  void begin(uint16_t b);  // to be managed at serial port level
  void print(int8_t i);
  void print(uint8_t ui);
  void print(int16_t i);
  void print(uint16_t ui);
  void print(char c);
  void print(String s);

  uint8_t read();
  int8_t available();
  void flush();

private:
  uint16_t _millis;
  void _checkSpeed();

  Stream * _proxyPort;
};

#endif





