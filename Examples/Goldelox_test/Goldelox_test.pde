// 
// μLCD-32PT(SGC) 3.2” Serial LCD Display Module
// Arduino & chipKIT Library
//
// Example - see README.txt
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
#include <Wire.h>

#include "Serial_LCD.h"
#include "GUI.h"

// test release
#if GUI_RELEASE < 24
#error required GUI_RELEASE 24
#endif

// Arduino Case : uncomment #include
// #if defined(__AVR__)  || defined (__AVR_ATmega328P__) doesn't work!
// ---
//#include "NewSoftSerial.h"
// ===

#include "proxySerial.h"

#if defined(__AVR__)  || defined (__AVR_ATmega328P__) | defined (__AVR_ATmega328P__)
// Arduino Case ---
#include "NewSoftSerial.h"
NewSoftSerial nss(2, 3); // RX, TX
ProxySerial mySerial(&nss);

#elif defined(__PIC32MX__) 
// chipKIT Case ---
ProxySerial mySerial(&Serial1);

#else
#error Non defined board
#endif 


Serial_LCD myLCD( &mySerial); 



uint16_t x, y;
uint32_t l;

button b7;



void setup() {
  Serial.begin(19200);
  Serial.print("\n\n\n***\n");

#if defined(__AVR__)  || defined (__AVR_ATmega328P__) | defined (__AVR_ATmega328P__)
  Serial.print("avr\t");
  Serial.print(__AVR__);
  Serial.print("\n");
  nss.begin(9600);
#elif defined(__PIC32MX__) 
  Serial.print("chipKIT\t");
  Serial.print(__PIC32MX__);
  Serial.print("\n");
  Serial1.begin(9600);
#endif 

//  mySerial.begin(9600);

  myLCD.begin();
  myLCD.setOrientation(0x03);

  myLCD.setPenSolid(true);
  myLCD.setFontSolid(true);
  myLCD.setFont(0);
  myLCD.gText( 0, 60, 0xffff, myLCD.WhoAmI());

  myLCD.setTouch(true);

  l=millis();

  Serial.print("\n maxX \t");
  Serial.print( myLCD.maxX(), DEC);
  Serial.print("\n maxY \t");
  Serial.print( myLCD.maxY(), DEC);
  Serial.print("\n");
  Serial.print("\n xy16 \t");
  Serial.print( myLCD.checkScreenType()>0, DEC);
  
  dLabel(&myLCD, 0, 0, myLCD.maxY(), 25, "label left",   myLCD.setColour(0xff, 0x00, 0x00), myLCD.setColour(0x00, 0x2f, 0x2f), 1, 0, 9);
  dLabel(&myLCD, 0, myLCD.maxY()/3, myLCD.maxY(), 25, "label center", myLCD.setColour(0x00, 0xff, 0x00), myLCD.setColour(0x2f, 0x00, 0x2f), 0, 0, 9);
  dLabel(&myLCD, 0, myLCD.maxY()*2/3, myLCD.maxY(), 25, "label right",  myLCD.setColour(0x00, 0x00, 0xff), myLCD.setColour(0x2f, 0x2f, 0x00), 2, 0, 9);

  uint16_t i=9;
  b7.dDefine(&myLCD,  myLCD.maxX()-80, myLCD.maxY()-60, 79, 59, setItem(1, "Stop"), myLCD.setColour(0xff, 0xff, 0xff), myLCD.setColour(0xff, 0x00, 0x00), myLCD.setColour(0x88, 0x00, 0x00), i);
  b7.enable(true);
  b7.draw();
}

uint8_t c;

void loop() {

  c=myLCD.getTouchActivity();

  if (c>0) {
    myLCD.getTouchXY(x, y);
    myLCD.setFont(0);
    myLCD.gText(0, 50, 0xffff, ftoa(x, 0, 5)); 
    myLCD.gText(myLCD.maxX()/3, 50, 0xffff, ftoa(y, 0, 5)); 

    // quit
    if (b7.check()) {
      myLCD.off();
      while(true);
    }
  }
  myLCD.setFont(0);
  myLCD.setFontSolid(true);
  myLCD.gText( myLCD.maxX()*2/3, 50, 0xffff, String(millis()-l));
  l=millis();
}



















