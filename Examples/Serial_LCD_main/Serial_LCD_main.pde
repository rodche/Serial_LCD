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


#include "proxySerial.h"
#include "Serial_LCD.h"

// test release
#if SERIAL_LCD_RELEASE < 118
#error required SERIAL_LCD_RELEASE 118
#endif

// === Serial port choice ===

// uncomment for I2C serial interface
//#define __I2C_Serial__

// --- I2C Case -
#if defined(__I2C_Serial__)
#include "Wire.h"
#include "I2C_Serial.h"
  // Test release
  #if I2C_SERIAL_RELEASE < 103
  #error required I2C_SERIAL_RELEASE 103
  #endif
I2C_Serial mySerial(0);
ProxySerial myPort(&mySerial);

// --- Arduino SoftwareSerial Case - Arduino only
#elif defined(__AVR__)  || defined (__AVR_ATmega328P__)
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

uint8_t aa;

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


  myLCD.begin();

delay(100);
  aa=myLCD.setOrientation(0x03);

delay(100);
  Serial.print("\n line \t");
  aa=myLCD.line(0,0,100,100, myLCD.rgb16(0,255,0));
  Serial.print(aa, DEC);

delay(100);
  Serial.print("\n rectangle \t");
  aa=myLCD.rectangle(239,0,319,256, myLCD.rgb16(255,0,0));
  Serial.print(aa, DEC);

delay(100);
  Serial.print("\n circle \t");
  aa=myLCD.circle(200,100, 50, myLCD.rgb16(0,0,255));
  Serial.print(aa, DEC);

delay(200);
  Serial.print("\n setFont \t");
  aa=myLCD.setFont(2);
  Serial.print(aa, DEC);

delay(100);
  Serial.print("\n gText \t");
  aa=myLCD.gText(25, 25, 0xffff, "String");
  Serial.print(aa, DEC);

delay(100);
//  Serial.print("\n tText \t");
//  aa=myLCD.tText(0, 19, 0xffff, "WhoAmI? "+ myLCD.WhoAmI());
//  Serial.print(aa, DEC);

//  for (uint8_t i=0; i<myLCD.WhoAmI().length(); i++)   
//    Serial.print(myLCD.WhoAmI().charAt(i));
//  Serial.print("\n");

  delay(100);

delay(1000);
  Serial.print("\n triangle \t");
  aa=myLCD.triangle(160, 200, 80, 160, 60, 100, 0xffff);
  Serial.print(aa, DEC);

delay(100);
  Serial.print("\n setTouch \t");
  aa=myLCD.setTouch(true);
  Serial.print(aa, DEC);

  Serial.print("\n ");
}

uint16_t x, y;
uint8_t b;

void loop() {


  Serial.print("\n getTouchActivity \t");
  aa=myLCD.getTouchActivity();
  Serial.print(aa, DEC);


  if (aa) {
aa=0;
Serial.print(" * " );
    Serial.print("\t getTouchXY \t");
    aa=myLCD.getTouchXY(x, y);
delay(10);
    Serial.print(aa, DEC);

    Serial.print("\t");
    Serial.print(x, DEC );      
    Serial.print("\t");
    Serial.print(y, DEC );

    if (x>256) {
      myLCD.off();
      while(1);
    }
    Serial.println();
  }


  delay(200);

}












