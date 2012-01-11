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

#include "WProgram.h"
#include "Stream.h"
#include "proxySerial.h"

// Utilities

String ftoa(float number, byte precision, byte size) {
    // Based on mem,  16.07.2008
    // http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num = 1207226548/6#6
    
    // prints val with number of decimal places determine by precision
    // precision is a number from 0 to 6 indicating the desired decimial places
    // example: printDouble(3.1415, 2); // prints 3.14 (two decimal places)
    
    // Added rounding, size and overflow #
    // ftoa(343.1453, 2, 10) -> "    343.15"
    // ftoa(343.1453, 4,  7) -> "#      "
    // avenue33, April 10th, 2010
    
    String s = "";
    
    // Negative 
    if (number < 0.0)  {
        s = "-";
        number = -number;
    }
    
    float rounding = 0.5;
    for (byte i = 0; i < precision; ++i)    rounding /= 10.0;
    
    number += rounding;
    s += String(int(number));  // prints the integer part
    
    if(precision > 0) {
        s += ".";                // prints the decimal point
        uint32_t frac;
        uint32_t mult = 1;
        uint8_t padding = precision -1;
        while(precision--)     mult *= 10;
        
        frac = (number - (uint64_t)(number)) * mult;
        
        uint32_t frac1 = frac;
        while(frac1 /= 10)    padding--;
        while(padding--)      s += "0";
        
        s += String(frac,DEC) ;  // prints the fractional part
    }
    
    if (size>0)                // checks size
        if (s.length()>size)        return("#");
        else while(s.length()<size) s = " "+s;
    
    return s;
}


// Object

ProxySerial::ProxySerial(Stream * port0) {
  _proxyPort = port0; 
}


void ProxySerial::_checkSpeed() {  
  //    while(!(millis()-_millis > 3));    // time in ms
  while((millis()-_millis < securityDelay));    // time in ms, the same !> = <
  _millis=millis();
}

void ProxySerial::begin(uint16_t b) {  // to be managed at serial port level
  _checkSpeed();  
//  _proxyPort->begin(b); 
}

void ProxySerial::print(int8_t i) { 
  _checkSpeed();  
  _proxyPort->print(i); 
}

void ProxySerial::print(uint8_t ui) { 
  _checkSpeed();  
  _proxyPort->print(ui); 
};

void ProxySerial::print(int16_t i) { 
  _checkSpeed();  
  _proxyPort->print(highByte(i)); 
  _proxyPort->print(lowByte(i)); 
};

void ProxySerial::print(uint16_t ui) { 
  _checkSpeed();  
  _proxyPort->print(highByte(ui)); 
  _proxyPort->print(lowByte(ui)); 
};

void ProxySerial::print(char c) { 
  _proxyPort->print((uint8_t)c); 
};
void ProxySerial::print(String s) { 
  for (uint8_t i=0; i<s.length(); i++)         {
    //  _checkSpeed();  
    _proxyPort->print(s.charAt(i));
  }
}

uint8_t ProxySerial::read() { 
  _checkSpeed();  
  return _proxyPort->read(); 
}
int8_t ProxySerial::available() { 
  _checkSpeed();  
  return _proxyPort->available(); 
}
void ProxySerial::flush() {  
  _checkSpeed();  
  _proxyPort->flush(); 
}









