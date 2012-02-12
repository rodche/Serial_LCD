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


#include "Serial_LCD.h"
#include "proxySerial.h"
#include "Graphics.h"

// test release
#if GRAPHICS_RELEASE < 105
#error required GRAPHICS_RELEASE 105
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
#elif defined(__AVR__)  || defined (__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
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

uint16_t x, y;
uint32_t l;

uint8_t a;
gHistogram myHistogram;


void setup() {
  Serial.begin(19200);
  Serial.print("\n\n\n***\n");

  // === Serial port initialisation ===
#if defined(__I2C_Serial__)
  Serial.print("i2c\n");
  Wire.begin();
  mySerial.begin(9600);

#elif defined(__AVR__)  || defined (__AVR_ATmega328P__) | defined (__AVR_ATmega328P__)
  Serial.print("avr\n");
  mySerial.begin(9600);

#elif defined(__PIC32MX__) 
  Serial.print("chipKIT\n");
  Serial1.begin(9600);

#endif 
  // === End of Serial port initialisation ===

  myLCD.begin(4);

  Serial.print("begin\n");

  // === Serial port speed change ===
  myLCD.setSpeed(38400);
#if defined(__I2C_Serial__)
  mySerial.begin(38400);

#elif defined(__AVR__)  || defined (__AVR_ATmega328P__)
  mySerial.begin(38400);

#elif defined(__PIC32MX__) 
  Serial1.begin(38400);

#endif 
  // === End of Serial port speed change ===

  myLCD.setOrientation(0x03);
  myLCD.setPenSolid(true);
  myLCD.setFontSolid(true);

  myHistogram.dDefine(&myLCD, 1, 1, myLCD.maxX()-2, myLCD.maxY()-2, -2.0, 2.0, 100, 8, 4, 100, false, blackColour, whiteColour, yellowColour, blueColour, greenColour, redColour);
}

uint32_t s;
uint16_t i = 0;
float v;

void loop() {

  //  // Solution 1
  //  while (millis()-l<100) {
  //    v = cos(i*PI/64.0) + 0.3*cos(i*PI/16.0+PI/8.0);
  //    i++;
  //    i %= 256;
  //  }

  // Solution 2
  v = cos(i*PI/64.0) + 0.3*cos(i*PI/16.0+PI/8.0);
  i++;
  i %= 256;
  while (millis()-l<100);

  l=millis();
  myHistogram.draw( v );

  if (millis()>(uint32_t)(100000)) {
    myLCD.off();
    while (1) delay(100);
  }
}



























