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
#include "Wire.h"
#include "Serial_LCD.h"
#include "GUI.h"
#include "proxySerial.h"

// test release
#if GUI_RELEASE < 26
#error required GUI_RELEASE 26
#endif

// === Serial port choice ===

// uncomment for I2C serial interface
//#define __I2C_Serial__

// --- I2C Case -
#if defined(__I2C_Serial__)
#include "Wire.h"
#include "I2C_Serial.h"
I2C_Serial mySerial(0);
ProxySerial myPort(&mySerial);

// --- Arduino SoftwareSerial Case - Arduino only
#elif defined(__AVR__)
#include "NewSoftSerial.h"
NewSoftSerial mySerial(2, 3); // RX, TX
ProxySerial myPort(&mySerial);

// --- chipKIT HardwareSerial Case - chipKIT
#elif defined(__PIC32MX__) 
ProxySerial myPort(&Serial1);

#else
#error Non defined board
#endif 

// === End of Serial port choice ===


Serial_LCD myLCD( &myPort); 
button myButton, myRotate;
uint16_t x, y;
uint32_t l;


void show() {
    switch (myLCD.checkScreenType()) {
  case 0:
    dLabel(&myLCD, 0, 0, myLCD.maxX(), 40, "8-bits uLED", 0xffff, 0x0000, 0, 0, 9);
    break;
  case 1:
    dLabel(&myLCD, 0, 0, myLCD.maxX(), 40, "16-bits uLCD", 0xffff, 0x0000, 0, 0, 9);
    break;
  case 2:
    dLabel(&myLCD, 0, 0, myLCD.maxX(), 40, "16-bits uVGA", 0xffff, 0x0000, 0, 0, 9);
    break;
  default:
    dLabel(&myLCD, 0, 0, myLCD.maxX(), 40, "Unknown", 0xffff, 0x0000, 0, 0, 9);
  }

  dLabel(&myLCD, 0, 40, myLCD.maxX()/2, 40, "Hardware: " + htoa(myLCD.checkHardwareVersion(), 2), 0xffff, myLCD.setColour(0x7f, 0x7f, 0x00), 0, 0, 9);
  dLabel(&myLCD, myLCD.maxX()/2, 40, myLCD.maxX()/2, 40, "Software: " + htoa(myLCD.checkSoftwareVersion(), 2), 0xffff, myLCD.setColour(0x7f, 0x7f, 0x00), 0, 0, 9);

  dLabel(&myLCD, 0, 80, myLCD.maxX()/2, 40, "max X:" + ftoa(myLCD.maxX(), 0, 5), 0xffff, myLCD.setColour(0x7f, 0x7f, 0x7f), 0, 0, 9);
  dLabel(&myLCD, myLCD.maxX()/2, 80, myLCD.maxX()/2, 40, "max Y:" + ftoa(myLCD.maxY(), 0, 5), 0xffff, myLCD.setColour(0x7f, 0x7f, 0x7f), 0, 0, 9);

  myLCD.initSD();

  if (myLCD.checkSD()) {
    dLabel(&myLCD, 0, 120, myLCD.maxX()/2, 40, "SD card", 0xffff, myLCD.setColour(0x00, 0x7f, 0x00), 0, 0, 9);

    if (myLCD.checkRAW()) dLabel(&myLCD, myLCD.maxX()/2, 120, myLCD.maxX()/2, 40, "FAT + RAW",   0xffff, myLCD.setColour(0x00, 0x00, 0x7f), 0, 0, 9);
    else dLabel(&myLCD, myLCD.maxX()/2, 120, myLCD.maxX()/2, 40, "FAT only",  0xffff, myLCD.setColour(0x00, 0x00, 0x7f), 0, 0, 9);
  } 
  else {
    dLabel(&myLCD, 0, 120, myLCD.maxX()/2, 40, "no SD card",   0xffff, myLCD.setColour(0x7f, 0x00, 0x00), 0, 0, 9);
  }

  myRotate.dDefine(&myLCD, 0, myLCD.maxY()-50, 80, 50, setItem(0, "Rotate"), myLCD.rgb16(0xff, 0xff, 0xff), myLCD.rgb16(0x00, 0xff, 0x00));
  myRotate.enable(true);
  myRotate.draw();

  myButton.dDefine(&myLCD, myLCD.maxX()-80, myLCD.maxY()-50, 80, 50, setItem(0, "Stop"), myLCD.rgb16(0xff, 0xff, 0xff), myLCD.rgb16(0xff, 0x00, 0x00));
  myButton.enable(true);
  myButton.draw();
}


void setup() {
  Serial.begin(19200);
  Serial.print("\n\n\n***\n");

  // === Serial port initialisation ===
#if defined(__I2C_Serial__)
  Serial.print("i2c\n");
  Wire.begin();
  mySerial.begin(9600);

#elif defined(__AVR__)
  Serial.print("avr\n");
  mySerial.begin(9600);

#elif defined(__PIC32MX__) 
  Serial.print("chipKIT\n");
  Serial1.begin(9600);

#endif 
  // === End of Serial port initialisation ===

  myLCD.begin();  // 9600 at start-up
  myLCD.setOrientation(0x03);
  myLCD.setTouch(true);

  show();
}

uint8_t c;
uint16_t result;
boolean b=true;

void loop() {
  if (myLCD.getTouchActivity()>0) {
    if (myRotate.check()) {
      myLCD.clear();
      myLCD.setOrientation(myLCD.getOrientation() %4 +1);
      show();
    } 
    else if (myButton.check()) {
      myLCD.off();
      while(true);
    }
  }

  delay(250);
}















