// (C)2016-18 Pawel A. Hernik

#include <OLEDSoftI2C_SSD1306.h>
//#include <OLEDSoftI2C_SH1106.h>
// define USEHW in above header for hw I2C version

OLEDSoftI2C_SSD1306 oled(0x3c);
//OLEDSoftI2C_SH1106 oled(0x3c);
int oled128x32 = 0;

#if USEHW==1
#include <Wire.h>
#endif

#include "small5x7bold_font.h"
#include "term7x14_font.h"

const uint8_t icon1 [] PROGMEM = { 16,2,
0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xDE, 0xCC, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80,
0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0x7B, 0x33, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01,
};

const uint8_t icon2 [] PROGMEM = { 16,2,
0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xCC, 0xDE, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80,
0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x33, 0x7B, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01,
};

const uint8_t icon3 [] PROGMEM = { 16,2,
0xFC, 0x0C, 0x14, 0x24, 0x44, 0x84, 0x04, 0x04, 0x04, 0x04, 0x84, 0x44, 0x24, 0x14, 0x0C, 0xFC,
0x3F, 0x30, 0x28, 0x24, 0x22, 0x21, 0x21, 0x22, 0x22, 0x21, 0x21, 0x22, 0x24, 0x28, 0x30, 0x3F,
};

void setup() 
{
  Serial.begin(9600);
  oled.init(oled128x32);  // 0-128x64, 1-128x32
  oled.clrScr();
}

// --------------------------------------------------------------------------

void loop() 
{
  unsigned long stTime;
  oled.setFont(Small5x7PLBold);
  for(int i=0;i<=128; i++) {
    stTime = millis();
    oled.printStr(i, 0, "  >> Scroll test <<");
    oled.printStr(i, 1, "abcdefghijklmnopqrtsuvwxyz");
    oled.printStr(i, 2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    oled.printStr(i, 3, "01234567890");
    oled.drawBitmap(icon1, i+00, 4);
    oled.drawBitmap(icon1, i+16, 4);
    oled.drawBitmap(icon3, i+32, 4);
    oled.drawBitmap(icon2, i+48, 4);
    oled.drawBitmap(icon2, i+64, 4);
    if(i>0) oled.fillWin(i-1,0,1,8,0); else delay(2000);
    if(millis()-stTime<10) {}
  }
  oled.setFont(Term7x14PL);
  for(int i=127;i--;) {
    stTime = millis();
    oled.printStr(i, 0, ">> Scroll test <<");
    oled.printStr(i, 2, "abcdefghijklmnopqrtsuvwxyz");
    oled.printStr(i, 4, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    oled.printStr(i, 6, "01234567890");
    if(millis()-stTime<10) {}
  }
  delay(4000);
  oled.setFont(Term7x14PL);
  for(int i=0;i<=128; i++) {
    stTime = millis();
    oled.printStr(i, 0, ">> Scroll test <<");
    oled.printStr(i, 2, "abcdefghijklmnopqrtsuvwxyz");
    oled.printStr(i, 4, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    oled.printStr(i, 6, "01234567890");
    if(i>0) oled.fillWin(i-1,0,1,8,0);
    if(millis()-stTime<10) {}
  }
  oled.setFont(Small5x7PLBold);
  for(int i=127;i--;) {
    stTime = millis();
    oled.printStr(i, 0, "  >> Scroll test <<");
    oled.printStr(i, 1, "abcdefghijklmnopqrtsuvwxyz");
    oled.printStr(i, 2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    oled.printStr(i, 3, "01234567890");
    oled.drawBitmap(icon1, i+00, 4);
    oled.drawBitmap(icon1, i+16, 4);
    oled.drawBitmap(icon3, i+32, 4);
    oled.drawBitmap(icon2, i+48, 4);
    oled.drawBitmap(icon2, i+64, 4);
    oled.fillWin(i+64+15,4,1,2,0);
    if(millis()-stTime<10) {}
  }
}

