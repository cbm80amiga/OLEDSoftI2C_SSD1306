// (C)2016-18 Pawel A. Hernik

#include <OLEDSoftI2C_SSD1306.h>
//#include <OLEDSoftI2C_SH1106.h>
// define USEHW in above header for hw I2C version

OLEDSoftI2C_SSD1306 oled(0x3c);
//OLEDSoftI2C_SH1106 oled(0x3c);

#if USEHW==1
#include <Wire.h>
#endif

#include "small4x7_font.h"

void setup() 
{
  Serial.begin(9600);
  oled.init();
}

// --------------------------------------------------------------------------

void loop() 
{
  oled.displayMode(SSD1306_NORMALDISPLAY);
  oled.displayMode(SSD1306_DISPLAYON);
  oled.clrScr();
  oled.setFont(Small4x7PL);
  oled.setDigitMinWd(8);
  oled.printStr(0, 0, "Testing modes:");
  oled.printStr(0, 1, "1.DISPLAYINVERTED");
  oled.printStr(0, 2, "2.DISPLAYALLON");
  oled.printStr(0, 3, "3.DISPLAYBLANK");
  oled.printStr(0, 4, "4.DISPLAYNORMAL");
  delay(2000);
  oled.displayMode(SSD1306_INVERTDISPLAY);
  delay(2000);
  //oled.displayMode(SSD1306_DISPLAYALLON);
  delay(2000);
  oled.displayMode(SSD1306_DISPLAYOFF);
  delay(2000);
}

