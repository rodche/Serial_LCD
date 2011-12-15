//
// μLCD-32PT(SGC) 3.2” Serial LCD Display Module
// Arduino & chipKIT Library
//
// May 10, 2011 release 1 - initial release
// Jun 15, 2011 release 2 - features added and bugs fixed
// Jun 29, 2011 release 3 - setBackGroundColour added and SD card
// Jul 31, 2011 release 4 - stdint.h types for chipKIT compatibility
// Aug 04, 2011 release 5 - chipKIT compatibility with external proxySerial1.h
// Aug 07, 2011 release 6 - playing sounds - up to 250 mA!
// Sep 18, 2011 release 7 - dialog window with up to 3 button1s
// Sep 23, 2011 release 8 - ms monitoring to avoid RX TX collapse
// Oct 10, 2011 release 9 - Stream.h class based i2cSerial library
// Oct 14, 2011 release 10 - ellipse and detectTouchRegion from sebgiroux
// Oct 24, 2011 release 11 - serial port managed in main only - setSpeed added - proxySerial1 still needed
// Oct 27, 2011 release 12 - setSpeed fixed for 155200 
// Nov 02, 2011 release 13 - HardwareSerial derived from Stream on chipKIT platform by msproul
// Nov 09, 2011 release 14 - proxySerial1 as autonomous project with ftoa utility
// Nov 25, 2011 release 15 - faster dialog show/hide and optional area for screen copy to/read from SD
// Nov 29, 2011 release 16 - read pixel colour and new colour functions
// Dec 15, 2011 release 1-16 - Arduino 1.0 implementation - no longer compatible with 0022
//
//
// CC = BY NC SA
// http://sites.google.com/site/vilorei/
// http://github.com/rei-vilo/Serial_LCD1
//
// Based on
// 4D LABS PICASO-SGC Command Set
// Software Interface Specification
// Document Date: 1st March 2011 
// Document Revision: 6.0
// http://www.4d-Labs.com
//
//

#include "Serial_LCD1.h"
#include "Arduino.h"
//#include "Arduino.h"

#include "button1.h"

button::button(Serial_LCD1 * pscreen0)   {   
  _pscreen = pscreen0;
}


void button::define(uint16_t x1, uint16_t y1, uint16_t dx1, uint16_t dy1, String text0, uint16_t textColour1, uint16_t highColour1, uint16_t lowColour1) {
  define( x1, y1, dx1, dy1, text0, textColour1, highColour1, lowColour1, 9);
}


void button::define(uint16_t x1, uint16_t y1, uint16_t dx1, uint16_t dy1, String text0, uint16_t textColour1, uint16_t highColour1, uint16_t lowColour1, uint8_t size0) {

  _x1 = x1;
  _y1 = y1;
  _x2 = _x1+dx1;
  _y2 = _y1+dy1;

  _textColour = textColour1;
  _highColour = highColour1;
  _lowColour  = lowColour1;
  _enable = false;  


  if (size0==9) {
    uint16_t i=4;
    do {
      i--;
      _pscreen->setFont(i);
    } 
    while ((text0.length() * _pscreen->fontX() > dx1 ) && ( i > 0));
    _size=i;
  } 
  else {
    _size = size0;
  }
  _pscreen->setFont(_size);
  _text = text0.substring(0, min(text0.length(), dx1 / _pscreen->fontX()));
  _text.trim();  // in place 1.0
  _xt = _x1 + ( dx1 - (_text.length() * _pscreen->fontX()) ) /2;
  _yt = _y1 + ( dy1 - _pscreen->fontY() ) /2;

}

void button::draw(bool b1) {
  if (_enable) {
    if (b1) {
      _pscreen->setPenSolid(true);
      _pscreen->rectangle(_x1, _y1, _x2, _y2, _highColour);
      delay(10);    // delay required by chipKIT
      _pscreen->setPenSolid(false);
      _pscreen->rectangle(_x1+2, _y1+2, _x2-2, _y2-2, _lowColour); 

      _pscreen->setFont(_size);
      _pscreen->setFontSolid(false);
      _pscreen->gText(_xt, _yt, _textColour, _text);
    } 
    else {
      _pscreen->setPenSolid(true);
      _pscreen->rectangle(_x1, _y1, _x2, _y2, _lowColour); 
      delay(10);    // delay required by chipKIT
      _pscreen->setPenSolid(false);
      _pscreen->rectangle(_x1+2, _y1+2, _x2-2, _y2-2, _highColour); 

      _pscreen->setFontSolid(false);
      _pscreen->setFont(_size);
      _pscreen->gText(_xt, _yt, _textColour, _text);
    }
  }  
  else {
    _pscreen->setPenSolid(true);
    _pscreen->rectangle(_x1, _y1, _x2, _y2, _pscreen->rgb16(0x44, 0x44, 0x44)); 
    delay(10);    // delay required by chipKIT
    _pscreen->setPenSolid(false);
    _pscreen->rectangle(_x1+2, _y1+2, _x2-2, _y2-2, _textColour); 

    _pscreen->setFontSolid(false);
    _pscreen->setFont(_size);
    _pscreen->gText(_xt, _yt, _textColour, _text);
  }

}

void button::enable(bool b1) {
  _enable = b1;
}

bool button::check() {
  if (!_enable) return false;

  uint16_t x0, y0, z0;

  // down
  if ((_pscreen->getTouchActivity() == 1) || (_pscreen->getTouchActivity() == 3)) {
    _pscreen->getTouchXY(x0, y0);

    // pressed
    if ((x0>=_x1) && (x0<=_x2) && (y0>=_y1) && (y0<=_y2)) {
      draw(true); 

      // debounce
      do {   
        z0 = _pscreen->getTouchActivity();
        // Serial.pruint16_t ln(z0);
        delay(10); 
      }
      while (z0 != 2);

      // released
      delay(50);
      draw();        

      // up
      if (z0 == 2)  {
        _pscreen->getTouchXY(x0, y0);
        if ((x0>=_x1) && (x0<=_x2) && (y0>=_y1) && (y0<=_y2)) {
          return true;
        } 
      } // if up
    } // if pressed
  } // if down
  return false; 
}


dialog::dialog(Serial_LCD1 * pscreen0)   {   
  _pscreen = pscreen0;
  _checkedSD=false;

}



uint8_t a;
String dialog::prompt(String text0, uint8_t kind0, uint16_t textColour0, uint16_t highColour0, uint16_t lowColour0, String text1, String button11, uint16_t textColour1, uint16_t highColour1, uint16_t lowColour1) {
  return prompt(text0, kind0, textColour0, highColour0, lowColour0, text1, button11, textColour1, highColour1, lowColour1, "", "", 0, 0, 0, "", "", 0, 0, 0);
}

String dialog::prompt(String text0, uint8_t kind0, uint16_t textColour0, uint16_t highColour0, uint16_t lowColour0, String text1, String button11, uint16_t textColour1, uint16_t highColour1, uint16_t lowColour1, String text2, String button12, uint16_t textColour2, uint16_t highColour2, uint16_t lowColour2) {
  return prompt(text0, kind0, textColour0, highColour0, lowColour0, text1, button11, textColour1, highColour1, lowColour1, text2, button12, textColour2, highColour2, lowColour2, "", "", 0, 0, 0);
}






String dialog::prompt(String text0, uint8_t kind0, uint16_t textColour0, uint16_t highColour0, uint16_t lowColour0, String text1, String button11="OK", uint16_t textColour1=0xffff, uint16_t highColour1=0x000f, uint16_t lowColour1=0x0008, String text2="", String button12="", uint16_t textColour2=0, uint16_t highColour2=0, uint16_t lowColour2=0, String text3="", String button13="", uint16_t textColour3=0, uint16_t highColour3=0, uint16_t lowColour3=0) {
  // Check SD
  if (_checkedSD==false) {
    char a=_pscreen->initSD();
    //    Serial.print(a, DEC); 
    _checkedSD=(boolean)(a==0x06);
    //    delay(3000);
  } 
  else {
    //    Serial.print("done"); 
  }  
  //  Serial.print("\n");

    uint16_t x0 = 60;
    uint16_t y0 = 20;

  // landscape and portrait coordinates
  if ((_pscreen->getOrientation()==0x03) || (_pscreen->getOrientation()==0x04)) {
  } 
  else {
    x0 = 20;
    y0 = 60;
  }    

  if (_checkedSD==true) {
    // Save initial screen
    //  uint16_t l=millis();
    a=_pscreen->saveScreenSD("dialog.tmp", x0, y0, 200+x0, 200+y0);
    //  Serial.print("saveScreenSD");
    //  Serial.print("\t");
    //  l=millis()-l;
    //  Serial.print(l, DEC); 
    //  Serial.print("\n");
    //  delay(100);
  }


  // Draw window
  _pscreen->setPenSolid(true);
  _pscreen->rectangle(x0, y0, 200+x0, 200+y0, lowColour0);
  delay(10);    // delay required by chipKIT
  _pscreen->setPenSolid(false);
  _pscreen->rectangle(x0+2, y0+2, 200+x0-2, 200+y0-2, highColour0); 

  // String &result0, String text0, uint8_t kind0
  // uint16_t textColour0, uint16_t highColour0, uint16_t lowColour0, 
  _pscreen->setFont(3);
  _pscreen->setFontSolid(false);
  _pscreen->gText(x0+60, y0+20, textColour0, text0.substring(0, min(text0.length(), 130 / _pscreen->fontX())));

  _pscreen->setFont(2);
  _pscreen->setFontSolid(false);
  _pscreen->gText(x0+20, y0+70, textColour0, text1.substring(0, min(text1.length(), 130 / _pscreen->fontX())));

  _pscreen->setFont(2);
  _pscreen->setFontSolid(false);
  _pscreen->gText(x0+20, y0+90, textColour0, text2.substring(0, min(text2.length(), 130 / _pscreen->fontX())));

  _pscreen->setFont(2);
  _pscreen->setFontSolid(false);
  _pscreen->gText(x0+20, y0+110, textColour0, text3.substring(0, min(text3.length(), 130 / _pscreen->fontX())));

  // uint8_t kind0, 
  _pscreen->setPenSolid(false);
  if (kind0==1) {
    _pscreen->circle(x0+30, y0+30, 18, _pscreen->rgb16(0x00, 0x00, 0xff));  // blue !  
    _pscreen->circle(x0+30, y0+30, 15, _pscreen->rgb16(0x00, 0x00, 0xff));  // blue !  
    _pscreen->setFont(3);
    _pscreen->setFontSolid(false);
    _pscreen->gText(x0+30- (_pscreen->fontX()>>1), y0+30- (_pscreen->fontY()>>1), _pscreen->rgb16(0x00, 0x00, 0xff), "!");          
  }
  else if (kind0==2) {
    _pscreen->circle(x0+30, y0+30, 18, _pscreen->rgb16(0xff, 0xff, 0x00));  // yellow ? 
    _pscreen->circle(x0+30, y0+30, 15, _pscreen->rgb16(0xff, 0xff, 0x00));  // yellow ? 
    _pscreen->setFont(3);
    _pscreen->setFontSolid(false);
    _pscreen->gText(x0+30- (_pscreen->fontX()>>1), y0+30- (_pscreen->fontY()>>1), _pscreen->rgb16(0xff, 0xff, 0x00), "?");          
  }
  else if (kind0==3) {
    _pscreen->circle(x0+30, y0+30, 18, _pscreen->rgb16(0xff, 0x00, 0x00));  // red X 
    _pscreen->circle(x0+30, y0+30, 15, _pscreen->rgb16(0xff, 0x00, 0x00));  // red X 
    _pscreen->setFont(3);
    _pscreen->setFontSolid(false);
    _pscreen->gText(x0+30- (_pscreen->fontX()>>1), y0+30- (_pscreen->fontY()>>1), _pscreen->rgb16(0xff, 0x00, 0x00), "X");          
  }
  else  {
    _pscreen->circle(x0+30, y0+30, 18, _pscreen->rgb16(0x00, 0xff, 0x00));  // green + 
    _pscreen->circle(x0+30, y0+30, 15, _pscreen->rgb16(0x00, 0xff, 0x00));  // green + 
    _pscreen->setFont(3);
    _pscreen->setFontSolid(false);
    _pscreen->gText(x0+30- (_pscreen->fontX()>>1), y0+30- (_pscreen->fontY()>>1), _pscreen->rgb16(0x00, 0xff, 0x00), "+");          
  } 

  button b1(_pscreen);
  button b2(_pscreen);
  button b3(_pscreen);
  // String text1, String button11="OK", uint16_t textColour1=0xffff, uint16_t highColour1=0x000f, uint16_t lowColour1=0x0008, 
  // String text2="", String button12="", uint16_t textColour2=0, uint16_t highColour2=0, uint16_t lowColour2=0
  // String text3="", String button13="", uint16_t textColour3=0, uint16_t highColour3=0, uint16_t lowColour3=0

  b1.define( x0+130, y0+150, 60, 40, button11, textColour1, highColour1, lowColour1, 9);
  b2.define( x0+ 70, y0+150, 60, 40, button12, textColour2, highColour2, lowColour2, 9);
  b3.define( x0+ 10, y0+150, 60, 40, button13, textColour3, highColour3, lowColour3, 9);

  b1.enable(true);
  b1.draw();
  if (button12.length()>0) { 
    b2.enable(true); 
    b2.draw(); 
  }
  if (button12.length()>0) { 
    b3.enable(true); 
    b3.draw(); 
  }

  boolean done=false;
  String answer="";

  while (!done) {
    if (b1.check()) { 
      answer= button11; 
      done=true; 
    }
    else if (b2.check()) { 
      answer= button12; 
      done=true; 
    }
    else if (b3.check()) { 
      answer= button13; 
      done=true; 
    }
  }

  //  delay(100);

  if (_checkedSD==true) {
    // Restore initial screen
    //  Serial.print("readScreenSD");
    //  Serial.print("\t");
    //  l=millis();
    a=_pscreen->readScreenSD("dialog.tmp", x0, y0);
    //  Serial.print(a, DEC);
    //  Serial.print("\n");
    //  Serial.print("readScreenSD");
    //  Serial.print("\t");
    //  l=millis()-l;
    //  Serial.print(l, DEC); 
    //  Serial.print("\n");
    //  delay(100);
  }

  return answer;
}












