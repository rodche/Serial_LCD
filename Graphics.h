// 
// μLCD-32PT(SGC) 3.2” Serial LCD Display Module
// Arduino & chipKIT Library
//
// Jan 28, 2012 release 104
// see README.txt
//
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
#define GRAPHICS_RELEASE 104

#include "WProgram.h"
#include "Serial_LCD.h"

// Test release
#if SERIAL_LCD_RELEASE < 119
#error required SERIAL_LCD_RELEASE 119
#endif

#ifndef Graphics_h
#define Graphics_h


class gClock {
public:
  gClock();

  void dDefine(Serial_LCD * lcd0, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t backColour=blackColour, uint16_t frontColour=greenColour, uint16_t hourColour=redColour, uint16_t minuteColour=blueColour, uint16_t secondColour=yellowColour);
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
  void dDefine(Serial_LCD * lcd0, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t backColour=blackColour, uint16_t frontColour=yellowColour);
  void define(Serial_LCD * lcd0, uint16_t x0, uint16_t y0, uint16_t radius, uint16_t backColour, uint16_t frontColour);
  void draw(float degrees);

private:
  Serial_LCD * _pscreen;
  uint16_t _x0, _y0, _radius;
  uint16_t _backColour, _frontColour;
  float _oldDegrees;
};


class gHistogram {
public:
  gHistogram();
  void dDefine(Serial_LCD * lcd0, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, float valueMin, float valueMax, uint16_t lapse=0, uint16_t memory=8, uint16_t gridX=4, uint16_t gridY=0, boolean continous=false, uint16_t backColour=blackColour, uint16_t frontColour=whiteColour, uint16_t gridColour=yellowColour, uint16_t valueColour=blueColour, uint16_t minColour=greenColour, uint16_t maxColour=redColour);
  void draw(float value);

private:
  Serial_LCD * _pscreen;
  uint16_t _x0, _y0, _dx, _dy;
  float _valueMin, _valueMax;
  uint16_t _min, _max;
  uint16_t _n, _amnesiaMin, _amnesiaMax;
  boolean _continous; 
  uint16_t _lapse, _memory, _gridX, _gridY, _gridC;
  uint16_t _backColour, _frontColour, _gridColour, _valueColour, _minColour, _maxColour;
  uint32_t _chrono;
};


#endif



