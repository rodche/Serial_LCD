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

#include "WProgram.h"
#include "Serial_LCD.h"
#include "Graphics.h"


gClock::gClock() {
    ;
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
    if ( (sX!=_sX) || (sY!=_sY) )    
        _pscreen->line(_x0, _y0, _sX, _sY, _backColour);
    
    if ( (mX!=_mX) || (mY!=_mY) ) {   
        _pscreen->line(_x0,   _y0,   _mX,   _mY,   _backColour);
        _pscreen->line(_x0,   _y0+1, _mX,   _mY+1, _backColour);
        _pscreen->line(_x0+1, _y0,   _mX+1, _mY,   _backColour);
        _pscreen->line(_x0+1, _y0+1, _mX+1, _mY+1, _backColour);
    }
    
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
    
    _oldSecond = second;
    _oldMinute = minute;
    _oldHour   = hour;
}


gDirection::gDirection() {
    ;
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








