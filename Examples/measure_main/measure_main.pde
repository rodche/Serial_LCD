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
#include "Serial_LCD.h"
#include "GUI.h"
#include "proxySerial.h"

// test release
#if GUI_RELEASE < 23
#error required GUI_RELEASE 23
#endif

ProxySerial mySerial(&Serial1);
Serial_LCD myLCD( &mySerial); 
uint16_t x, y;
uint32_t l;

button b7;

void alphabet() {
  myLCD.setFontSolid(true);

  myLCD.setFont(3);
  myLCD.gText(0,  0, 0xffff, "         1         2    ");
  myLCD.gText(0, 20, 0xffff, "12345678901234567890123456"); 
  myLCD.gText(0, 40, 0xffff, ftoa(myLCD.fontX(), 0, 8)); 

  myLCD.setFont(2);
  myLCD.gText(0,  60, 0xffff, "         1         2         3         4");
  myLCD.gText(0, 80, 0xffff, "1234567890123456789012345678901234567890"); 
  myLCD.gText(0, 100, 0xffff, ftoa(myLCD.fontX(), 0, 8)); 

  myLCD.setFont(1);
  myLCD.gText(0,  120, 0xffff, "         1         2         3         4");
  myLCD.gText(0, 140, 0xffff, "1234567890123456789012345678901234567890"); 
  myLCD.gText(0, 160, 0xffff, ftoa(myLCD.fontX(), 0, 8)); 

  myLCD.setFont(0);
  myLCD.gText(0,  180, 0xffff, "         1         2         3         4         5");
  myLCD.gText(0, 200, 0xffff, "12345678901234567890123456789012345678901234567890123"); 
  myLCD.gText(0, 220, 0xffff, ftoa(myLCD.fontX(), 0, 8)); 
}



void setup() {
  uint8_t a;

  Serial.begin(19200);
  Serial.print("\n\n\n***\n");

  Serial1.begin(9600);
  myLCD.begin();
  myLCD.setOrientation(0x03);

  myLCD.setPenSolid(true);
  myLCD.setFontSolid(true);

  myLCD.setFont(0);
  myLCD.gText( 0, 210, 0xffff, myLCD.WhoAmI());
  Serial.print(myLCD.WhoAmI());
  Serial.print("\n");




  myLCD.setTouch(true);
  myLCD.initSD();

  Serial.print("\n");
  Serial.print("FULL screen \n");

  myLCD.clear();
  myLCD.line(  0, 0, 319, 239, 0xffff);
  myLCD.line(319, 0,   0, 239, 0xffff);

  l=millis();
  a=myLCD.saveScreenFAT("dialog.tmp");
  Serial.print(" saveScreenFAT \t");
  Serial.print(millis()-l, DEC); 
  Serial.print("\n");

  alphabet();

  l=millis();
  a=myLCD.readScreenFAT("dialog.tmp");
  Serial.print(" readScreenFAT \t");
  Serial.print(millis()-l, DEC); 
  Serial.print("\n");


  delay(1000);

  Serial.print("\n");
  Serial.print("AREA screen \n");

  myLCD.clear();
  myLCD.line(  0, 0, 319, 239, 0xffff);
  myLCD.line(319, 0,   0, 239, 0xffff);

  l=millis();
  a=myLCD.saveScreenFAT("dialog.tmp", 60, 20, 260, 220);
  Serial.print(" saveScreenFAT \t");
  Serial.print(millis()-l, DEC); 
  Serial.print("\n");

  alphabet();

  l=millis();
  a=myLCD.readScreenFAT("dialog.tmp", 60, 20);
  Serial.print(" readScreenFAT \t");
  Serial.print(millis()-l, DEC); 
  Serial.print("\n");



  uint16_t i=9;
  b7.define(&myLCD,  160, 120, 79, 59, setItem(0, "STOP"),        myLCD.setColour(0xff, 0xff, 0xff), myLCD.setColour(0xff, 0x00, 0x00), myLCD.setColour(0x88, 0x00, 0x00), i);

  b7.enable(true);
  b7.draw();

}

uint8_t c;

void loop() {

  c=myLCD.getTouchActivity();

  if (c>0) {
    myLCD.getTouchXY(x, y);
    myLCD.setFont(0);
    myLCD.gText(200, 0, 0xffff, ftoa(x, 0, 5)); 
    myLCD.gText(200, 15, 0xffff, ftoa(y, 0, 5)); 

    // quit
    if (b7.check()) {
      myLCD.off();
      while(true);
    }



  }
  myLCD.setFont(0);
  myLCD.setFontSolid(true);
  myLCD.gText( 250, 225, 0xffff, String(millis()-l));
  l=millis();
}


