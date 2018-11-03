// (C)2016-18 Pawel A. Hernik

#include <OLEDSoftI2C_SSD1306.h>
//#include <OLEDSoftI2C_SH1106.h>
// define USEHW in above header for hw I2C version

OLEDSoftI2C_SSD1306 oled(0x3c);
//OLEDSoftI2C_SH1106 oled(0x3c);

#if USEHW==1
#include <Wire.h>
#endif

//#include "fonts_all.h"
#include "small5x7bold_font.h"
#include "small4x7_font.h"
#include "digits4x7_font.h"

const uint8_t ind [] PROGMEM = {27,1,
0x40, 0x40, 0x40, 0x78, 0x04, 0x02, 0x02, 0x04, 0x78, 0x04, 0x02, 0x02, 0x04, 0x78, 0x04, 0x02,
0x02, 0x04, 0x78, 0x04, 0x02, 0x02, 0x04, 0x78, 0x40, 0x40, 0x40, 
};

void setup() 
{
  Serial.begin(9600);
  oled.init(0);  // 0-128x64, 1-128x32
  oled.setDigitMinWd(0);
}

// --------------------------------------------------------------------------
char buf[40];
void loop() 
{
  oled.clrScr();
  oled.setFont(Small5x7PLBold);
  oled.printStr(ALIGN_LEFT, 0, "Align left");
  oled.drawBitmap(ind, ALIGN_LEFT, 1);
  oled.printStr(ALIGN_RIGHT, 2, "Align right");
  oled.drawBitmap(ind, ALIGN_RIGHT, 3);
  oled.printStr(ALIGN_CENTER, 4, "Align center");
  oled.drawBitmap(ind, ALIGN_CENTER, 5);
  delay(4000);
  
  oled.clrScr();
  oled.setFont(Small4x7PL);
  oled.setFontMinWd(0); // default proportional font
  oled.printStr(0, 0, "abcdefghijklmnopqrtsuvwxyz");
  oled.setFontMinWd(4); // force fixed width
  oled.printStr(0, 1, "abcdefghijklmnopqrtsuvwxyz");
  oled.setFontMinWd(5);
  oled.printStr(0, 2, "abcdefghijklmnopqrtsuvwxyz");
  oled.setFontMinWd(0);
  
  for(int i=0;i<50;i++) {
    snprintf(buf,19,"%05u",(unsigned int) random(1,100000));
    //oled.fillWin(0,3,84,3,0xaa);
    oled.fillWin(0,3,84,3,0x00);
    oled.setFont(Digits4x7);
    oled.setDigitMinWd(0);
    oled.printStr(ALIGN_LEFT, 3, buf);
    oled.printStr(ALIGN_RIGHT, 3, buf);
    oled.setDigitMinWd(4);
    oled.printStr(ALIGN_LEFT, 4, buf);
    oled.printStr(ALIGN_RIGHT, 4, buf);
    oled.setDigitMinWd(5);
    oled.printStr(ALIGN_LEFT, 5, buf);
    oled.printStr(ALIGN_RIGHT, 5, buf);
    oled.setFont(Small4x7PL);
    oled.setFontMinWd(0); // default proportional font
    oled.printStr(ALIGN_CENTER, 3, "prop");
    oled.printStr(ALIGN_CENTER, 4, "fix4");
    oled.printStr(ALIGN_CENTER, 5, "fix5");
    delay(400);
  }
  delay(1000);
}
