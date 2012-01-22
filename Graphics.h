// 
// μLCD-32PT(SGC) 3.2” Serial LCD Display Module
// Arduino & chipKIT Library
//
// Jan 22, 2012 release 27 - see README.txt
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
#define GRAPHICS_RELEASE 27

#include "WProgram.h"
#include "Serial_LCD.h"

// Test release
#if SERIAL_LCD_RELEASE < 27
#error required SERIAL_LCD_RELEASE 27
#endif

#ifndef Graphics_h
#define Graphics_h

class gClock {
public:
  gClock();

  void define(Serial_LCD * lcd0, uint16_t x0, uint16_t y0, uint16_t radius, uint16_t backColour, uint16_t frontColour, uint16_t hourColour, uint16_t minuteColour, uint16_t secondColour);
  void draw(uint8_t hour, uint8_t minute, uint8_t second);

private:
  Serial_LCD * _pscreen;
  uint16_t _x0, _y0, _radius;
  uint16_t _backColour, _frontColour;
  uint16_t _hourColour, _minuteColour, _secondColour;
  uint8_t _oldHour, _oldMinute, _oldSecond;
};

class gDirection {
public:
  gDirection();
  void define(Serial_LCD * lcd0, uint16_t x0, uint16_t y0, uint16_t radius, uint16_t backColour, uint16_t frontColour);
  void draw(float degrees);

private:
  Serial_LCD * _pscreen;
  uint16_t _x0, _y0, _radius;
  uint16_t _backColour, _frontColour;
  float _oldDegrees;
};




#endif



