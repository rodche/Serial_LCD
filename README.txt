//
// μLCD-32PT(SGC) 3.2” Serial LCD Display Module
// Arduino & chipKIT Library
//
// Serial Port Multiple Options
//
// hardware : Arduino . Serial (pins 0 & 1)
//          : chipKIT . Serial (pins 0 & 1) + Serial1 (pins 39 & 40)
// software : Arduino . with library NewSoftSerial release 11
//          : chipKIT . not available
// i2c      : Arduino . (pins 4 & 5) with library I2C_Serial
//          : chipKIT . (pins 4 & 5) with library I2C_Serial
//
// May 10, 2011 release 1 - initial release
// Jun 15, 2011 release 2 - features added and bugs fixed
// Jun 29, 2011 release 3 - setBackGroundColour added and SD card
// Jul 31, 2011 release 4 - stdint.h types for chipKIT compatibility
// Aug 04, 2011 release 5 - chipKIT compatibility with external proxySerial.h
// Aug 07, 2011 release 6 - playing sounds - up to 250 mA!
// Sep 18, 2011 release 7 - dialog window with up to 3 buttons
// Sep 23, 2011 release 8 - ms monitoring to avoid RX TX collapse
// Oct 10, 2011 release 9 - Stream.h class based i2cSerial library
// Oct 14, 2011 release 10 - ellipse and detectTouchRegion from sebgiroux
// Oct 24, 2011 release 11 - serial port managed in main only - setSpeed added - proxySerial still needed
// Oct 27, 2011 release 12 - setSpeed fixed for 155200 
// Nov 02, 2011 release 13 - HardwareSerial derived from Stream on chipKIT platform by msproul
// Nov 09, 2011 release 14 - proxySerial as autonomous project with ftoa utility
// Nov 25, 2011 release 15 - faster dialog show/hide and optional area for screen copy to/read from SD
// Nov 29, 2011 release 16 - read pixel colour and new colour functions
// Dec 15, 2011 release 1-16 - Arduino 1.0 implementation - no longer compatible with 0022
//
//
// * Tutorial
// Basics: http://sites.google.com/site/vilorei/arduino/13--serial-touch-320x240-lcd-screen/13i--back-to-basics
// Serial ports: http://sites.google.com/site/vilorei/arduino/13--serial-touch-320x240-lcd-screen/13p--tutorial-2-playing-with-serial-ports
//
//
// * SC16IS750 I2C slave bridge to serial
// Arduino + chipKIT Library
//
// Oct 06, 2011 release 1 - initial release
// Oct 10, 2011 release 2 - Stream.h class based
//
// CC = BY NC SA
// http://sites.google.com/site/vilorei/
//
//
// * Required
// NewSoftSerial release 11
//
//
// * See Bugs & ToDos
//
//
// * Based on
// 4D LABS PICASO-SGC Command Set
// Software Interface Specification
// Document Date: 1st March 2011     
// Document Revision: 6.0
// http://www.4d-Labs.com
//
