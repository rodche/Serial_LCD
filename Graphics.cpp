// 
// μLCD-32PT(SGC) 3.2” Serial LCD Display Module
// Arduino & chipKIT Library
//
// Jan 28, 2012 release 103 
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

#include "WProgram.h"
#include "Serial_LCD.h"
#include "Graphics.h"


gClock::gClock() {
  ;
}

void gClock::dDefine(Serial_LCD * lcd0, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t backColour, uint16_t frontColour, uint16_t hourColour, uint16_t minuteColour, uint16_t secondColour) {
  uint16_t radius = min(dx, dy)/2;
  define(lcd0, x0-radius, y0-radius, radius-2, backColour, frontColour, hourColour, minuteColour, secondColour);
}

void gClock::define(Serial_LCD * lcd0, uint16_t x0, uint16_t y0, uint16_t radius, uint16_t backColour, uint16_t frontColour, uint16_t hourColour, uint16_t minuteColour, uint16_t secondColour) {

  _pscreen = lcd0;

  _x0 = x0; 
  _y0 = y0; 
  _radius = radius;
  _backColour = backColour;
  _frontColour = frontColour;
  _hourColour = hourColour; 
  _minuteColour = minuteColour; 
  _secondColour = secondColour;

  _oldHour = 0;
  _oldMinute = 0;
  _oldSecond = 0;

  _pscreen->setPenSolid(true);
  _pscreen->circle(_x0, _y0, _radius, _backColour); 

  _pscreen->setPenSolid(false);
  _pscreen->circle(_x0, _y0, _radius, _frontColour); 

  _pscreen->setPenSolid(true);
  for (int8_t i=0; i<12; i++) {
    _pscreen->circle(_x0+(_radius-2)*cos(i*PI/6.0), _y0+(_radius-2)*sin(i*PI/6.0), 2, _frontColour); 
  }
}

void gClock::draw(uint8_t hour, uint8_t minute, uint8_t second) {
  uint16_t hX, hY, mX, mY, sX, sY;
  uint16_t _hX, _hY, _mX, _mY, _sX, _sY;

  hX  = uint16_t( _x0+_radius*0.6*cos( (hour+minute/60.0         -3.0)*2.0*PI/12.0 ) );
  hY  = uint16_t( _y0+_radius*0.6*sin( (hour+minute/60.0         -3.0)*2.0*PI/12.0 ) );
  mX  = uint16_t( _x0+_radius*0.8*cos( (     minute+second/60.0 -15.0)*2.0*PI/60.0 ) );
  mY  = uint16_t( _y0+_radius*0.8*sin( (     minute+second/60.0 -15.0)*2.0*PI/60.0 ) );
  sX  = uint16_t( _x0+_radius*0.8*cos( (            second      -15.0)*2.0*PI/60.0 ) );
  sY  = uint16_t( _y0+_radius*0.8*sin( (            second      -15.0)*2.0*PI/60.0 ) );

  _hX  = uint16_t( _x0+_radius*0.6*cos( (_oldHour+_oldMinute/60.0             -3.0)*2.0*PI/12.0 ) );
  _hY  = uint16_t( _y0+_radius*0.6*sin( (_oldHour+_oldMinute/60.0             -3.0)*2.0*PI/12.0 ) );
  _mX  = uint16_t( _x0+_radius*0.8*cos( (         _oldMinute+_oldSecond/60.0 -15.0)*2.0*PI/60.0 ) );
  _mY  = uint16_t( _y0+_radius*0.8*sin( (         _oldMinute+_oldSecond/60.0 -15.0)*2.0*PI/60.0 ) );
  _sX  = uint16_t( _x0+_radius*0.8*cos( (                    _oldSecond      -15.0)*2.0*PI/60.0 ) );
  _sY  = uint16_t( _y0+_radius*0.8*sin( (                    _oldSecond      -15.0)*2.0*PI/60.0 ) );

  // old time with _backColour
  if ( (sX!=_sX) || (sY!=_sY) ) {
    _pscreen->line(_x0, _y0, _sX, _sY, _backColour);

    if ( (mX!=_mX) || (mY!=_mY) ) {   
      _pscreen->line(_x0,   _y0,   _mX,   _mY,   _backColour);
      _pscreen->line(_x0,   _y0+1, _mX,   _mY+1, _backColour);
      _pscreen->line(_x0+1, _y0,   _mX+1, _mY,   _backColour);
      _pscreen->line(_x0+1, _y0+1, _mX+1, _mY+1, _backColour);


      if ( (hX!=_hX) || (hY!=_hY) ) {
        _pscreen->line(_x0-1, _y0-1, _hX-1, _hY-1, _backColour);
        _pscreen->line(_x0-1, _y0,   _hX-1, _hY,   _backColour);
        _pscreen->line(_x0-1, _y0+1, _hX-1, _hY+1, _backColour);
        _pscreen->line(_x0,   _y0-1, _hX,   _hY-1, _backColour);
        _pscreen->line(_x0,   _y0,   _hX,   _hY,   _backColour);
        _pscreen->line(_x0,   _y0+1, _hX,   _hY+1, _backColour);
        _pscreen->line(_x0+1, _y0-1, _hX+1, _hY-1, _backColour);
        _pscreen->line(_x0+1, _y0,   _hX+1, _hY,   _backColour);
        _pscreen->line(_x0+1, _y0+1, _hX+1, _hY+1, _backColour);

      }
    }
    // new time with _hourColour, _minuteColour, _secondColour
    _pscreen->line(_x0-1, _y0-1, hX-1, hY-1, _hourColour);
    _pscreen->line(_x0-1, _y0,   hX-1, hY,   _hourColour);
    _pscreen->line(_x0-1, _y0+1, hX-1, hY+1, _hourColour);
    _pscreen->line(_x0,   _y0-1, hX,   hY-1, _hourColour);
    _pscreen->line(_x0,   _y0,   hX,   hY,   _hourColour);
    _pscreen->line(_x0,   _y0+1, hX,   hY+1, _hourColour);
    _pscreen->line(_x0+1, _y0-1, hX+1, hY-1, _hourColour);
    _pscreen->line(_x0+1, _y0,   hX+1, hY,   _hourColour);
    _pscreen->line(_x0+1, _y0+1, hX+1, hY+1, _hourColour);

    _pscreen->line(_x0,   _y0,   mX,   mY,   _minuteColour);
    _pscreen->line(_x0,   _y0+1, mX,   mY+1, _minuteColour);
    _pscreen->line(_x0+1, _y0,   mX+1, mY,   _minuteColour);
    _pscreen->line(_x0+1, _y0+1, mX+1, mY+1, _minuteColour);

    _pscreen->line(_x0, _y0, sX, sY, _secondColour);

    _pscreen->setPenSolid(true);
    _pscreen->circle(_x0, _y0, 3, _frontColour); 
  }
  _oldSecond = second;
  _oldMinute = minute;
  _oldHour   = hour;
}


gDirection::gDirection() {
  ;
}

void gDirection::dDefine(Serial_LCD * lcd0, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t backColour, uint16_t frontColour) {
  uint16_t radius = min(dx, dy)/2;
  define(lcd0, x0-radius, y0-radius, radius-2, backColour, frontColour);
}

void gDirection::define(Serial_LCD * lcd0, uint16_t x0, uint16_t y0, uint16_t radius, uint16_t backColour, uint16_t frontColour) {
  _pscreen = lcd0;

  _x0 = x0; 
  _y0 = y0; 
  _radius = radius;
  _backColour = backColour;
  _frontColour = frontColour;

  _pscreen->setPenSolid(true);
  _pscreen->circle(_x0, _y0, _radius, _backColour); 

  _oldDegrees = 0.0;
}

void gDirection::draw(float degrees) {
  float radians, c, s;
  uint16_t x1, x2, x3, x4, y1, y2, y3, y4;

  if (degrees!=_oldDegrees) {

    // old value with _backColour
    radians = (-_oldDegrees / 180.0 * PI + PI);
    c = cos(radians) * 0.6 * _radius;
    s = sin(radians) * 0.6 * _radius;

    x1 = _x0 + (  c*(-0.5) + s*( 0.0) ) + 0.5;
    y1 = _y0 + ( -s*(-0.5) + c*( 0.0) ) + 0.5;
    x2 = _x0 + (  c*( 0.5) + s*( 0.0) ) + 0.5;
    y2 = _y0 + ( -s*( 0.5) + c*( 0.0) ) + 0.5;
    x3 = _x0 + (  c*(-0.5) + s*(-1.0) ) + 0.5;
    y3 = _y0 + ( -s*(-0.5) + c*(-1.0) ) + 0.5;
    x4 = _x0 + (  c*( 0.5) + s*(-1.0) ) + 0.5;
    y4 = _y0 + ( -s*( 0.5) + c*(-1.0) ) + 0.5;

    _pscreen->line(x1, y1, x3, y3, _backColour);
    _pscreen->line(x3, y3, x4, y4, _backColour);
    _pscreen->line(x2, y2, x4, y4, _backColour);

    x3 = _x0 + (  c*(-1.0) + s*( 0.0) ) + 0.5;
    y3 = _y0 + ( -s*(-1.0) + c*( 0.0) ) + 0.5;
    x4 = _x0 + (  c*( 1.0) + s*( 0.0) ) + 0.5;
    y4 = _y0 + ( -s*( 1.0) + c*( 0.0) ) + 0.5;
    _pscreen->line(x1, y1, x3, y3, _backColour);
    _pscreen->line(x2, y2, x4, y4, _backColour);

    x1 = _x0 + (  c*( 0.0) + s*( 1.0) ) + 0.5;
    y1 = _y0 + ( -s*( 0.0) + c*( 1.0) ) + 0.5;
    _pscreen->line(x1, y1, x3, y3, _backColour);
    _pscreen->line(x1, y1, x4, y4, _backColour);

    // new value with _frontColour
    radians = (-degrees / 180.0 * PI + PI);
    c = cos(radians) * 0.6 * _radius;
    s = sin(radians) * 0.6 * _radius;

    x1 = _x0 + (  c*(-0.5) + s*( 0.0) ) + 0.5;
    y1 = _y0 + ( -s*(-0.5) + c*( 0.0) ) + 0.5;
    x2 = _x0 + (  c*( 0.5) + s*( 0.0) ) + 0.5;
    y2 = _y0 + ( -s*( 0.5) + c*( 0.0) ) + 0.5;
    x3 = _x0 + (  c*(-0.5) + s*(-1.0) ) + 0.5;
    y3 = _y0 + ( -s*(-0.5) + c*(-1.0) ) + 0.5;
    x4 = _x0 + (  c*( 0.5) + s*(-1.0) ) + 0.5;
    y4 = _y0 + ( -s*( 0.5) + c*(-1.0) ) + 0.5;

    _pscreen->line(x1, y1, x3, y3, _frontColour);
    _pscreen->line(x3, y3, x4, y4, _frontColour);
    _pscreen->line(x2, y2, x4, y4, _frontColour);

    x3 = _x0 + (  c*(-1.0) + s*( 0.0) ) + 0.5;
    y3 = _y0 + ( -s*(-1.0) + c*( 0.0) ) + 0.5;
    x4 = _x0 + (  c*( 1.0) + s*( 0.0) ) + 0.5;
    y4 = _y0 + ( -s*( 1.0) + c*( 0.0) ) + 0.5;
    _pscreen->line(x1, y1, x3, y3, _frontColour);
    _pscreen->line(x2, y2, x4, y4, _frontColour);

    x1 = _x0 + (  c*( 0.0) + s*( 1.0) ) + 0.5;
    y1 = _y0 + ( -s*( 0.0) + c*( 1.0) ) + 0.5;
    _pscreen->line(x1, y1, x3, y3, _frontColour);
    _pscreen->line(x1, y1, x4, y4, _frontColour);

    _oldDegrees = degrees;
  }

  _pscreen->circle(_x0, _y0, 2, _frontColour); 
}  


gHistogram::gHistogram() {
  ;
}

void gHistogram::dDefine(Serial_LCD * lcd0, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, float valueMin, float valueMax, uint16_t lapse, uint16_t memory, uint16_t gridX, uint16_t gridY, boolean continous, uint16_t backColour, uint16_t frontColour, uint16_t gridColour, uint16_t valueColour, uint16_t minColour, uint16_t maxColour) {
  _pscreen = lcd0;

  _x0 = x0; 
  _y0 = y0; 
  _dx = dx;
  _dy = dy;

  _backColour  = backColour;
  _frontColour = frontColour;
  _gridColour  = gridColour;
  _valueColour = valueColour;
  _minColour   = minColour;
  _maxColour   = maxColour;

  _valueMin  = valueMin;
  _valueMax  = valueMax;
  _continous = continous;
  _lapse     = lapse;
  _memory    = memory; 
  _gridX     = gridX;
  _gridY     = gridY;
  _gridC     = 0;
  _chrono    = millis();

  _pscreen->setPenSolid(true);
  _pscreen->dRectangle(_x0, _y0, _dx, _dy, _backColour);
  _pscreen->setPenSolid(false);
  _pscreen->dRectangle(_x0, _y0, _dx, _dy, _gridColour);

  _n   = 0; // number of values shown
  _min = 0; // y coordinate of min for memory
  _max = 0; // y coordinate of max for memory
  _amnesiaMin=0;
  _amnesiaMax=0;

  if (_gridX>0) for (uint16_t i=1; i<_gridX; i++) {
    _pscreen->dLine(_x0+1, _y0+map(i, 0, _gridX, 0, _dy), _dx-2, 1, _pscreen->halfColour(_gridColour));
  }
}


void gHistogram::draw(float value) {
  uint32_t l = millis()-_chrono;
  if ( (_lapse>0) && (l<_lapse) ) return;
  _chrono = millis();

  uint16_t y = _y0+1+_dy-2 - (uint16_t)( (value-_valueMin)*(_dy-2)/(_valueMax-_valueMin) );
  if (y<_y0+2)     y = _y0+2;
  if (y>_y0+_dy-4) y = _y0+_dy-4;

  // continuity management
  if (_continous) {
    // right-most side
    if (_n>_dx-4) {
      // move
      _pscreen->copyPaste(_x0+2, _y0, _x0+1, _y0, _dx-3, _dy);
      // new 
      _pscreen->line(_x0+_n+1, _y0+1, _x0+_n+1, _y0+_dy-2, _backColour);

      // gridY
      if (_gridY>0) { 
        if (_gridC==0) _pscreen->line(_x0+_n+1, _y0+1, _x0+_n+1, _y0+_dy-2, _pscreen->halfColour(_gridColour));
        _gridC++;
        _gridC %= _gridY;
      } // gridY

        // gridX
      if (_gridX>0) for (uint16_t i=1; i<_gridX; i++) 
        _pscreen->point(_x0+_n+1, _y0+map(i, 0, _gridX, 0, _dy), _pscreen->halfColour(_gridColour));
    } 
    else {
      _n++;
    } // right-most side
  } 
  else {
    // right 
    if (_n>_dx-4) {
      _n=1;
    } 
    else {
      _n++;
    } // right 

    _pscreen->line(_x0+_n+1, _y0+1, _x0+_n+1, _y0+_dy-2, _backColour);
    _pscreen->line(_x0+_n+2, _y0+1, _x0+_n+2, _y0+_dy-2, _gridColour);

    // gridY
    if (_gridY>0) { 
      if (_gridC==0) _pscreen->line(_x0+_n+1, _y0+1, _x0+_n+1, _y0+_dy-2, _pscreen->halfColour(_gridColour));
      _gridC++;
      _gridC %= _gridY;
    } // gridY

      // gridX
    if (_gridX>0) for (uint16_t i=1; i<_gridX; i++) 
      _pscreen->point(_x0+_n+1, _y0+map(i, 0, _gridX, 0, _dy), _pscreen->halfColour(_gridColour));

  } // continuity management

  // value
  _pscreen->dRectangle(_x0+_n, y, 2, 2, _valueColour);

  // min and max memory
  if (_memory>0) {

    // first time
    if (_n==0) {
      _max = y;
      _min = y;
    }

    // max - coordinates in reverse scale
    if (y<=_max) {
      _max = y;
      _amnesiaMax = _memory;
    } 
    else if (_amnesiaMax>0) {
      _pscreen->dRectangle(_x0+_n, _max, 2, 2, _maxColour);
      _amnesiaMax--;
    } 
    else {
      _max = y;
    } // max

    // min - coordinates in reverse scale
    if (y>=_min) {
      _min = y;
      _amnesiaMin = _memory;
    } 
    else if (_amnesiaMin>0) {  
      _pscreen->dRectangle(_x0+_n, _min, 2, 2, _minColour);
      _amnesiaMin--;
    } 
    else {
      _min = y;
    } // min
  } // min and max memory

    ;
  _pscreen->setFont(0);
  _pscreen->setFontSolid(true);
  _pscreen->gText(_x0+3, _y0+2, _frontColour, ftoa(_valueMax, 1, 0));
  _pscreen->gText(_x0+3, _y0+_dy-2-_pscreen->fontY(), _frontColour, ftoa(_valueMin, 1, 0));

  // lapse error
  if (l>_lapse) {
    _pscreen->setBackGroundColour(_frontColour);
    _pscreen->gText(_x0+_dx-2-5*_pscreen->fontX(), _y0+_dy-2-_pscreen->fontY(), _backColour, ftoa(l*_gridY/1000.0, 1, 4)+"s");
    _pscreen->setBackGroundColour(_backColour);
  } 
  else {
    _pscreen->gText(_x0+_dx-2-5*_pscreen->fontX(), _y0+_dy-2-_pscreen->fontY(), _frontColour, ftoa(l*_gridY/1000.0, 1, 4)+"s");
  } // lapse error

}




















