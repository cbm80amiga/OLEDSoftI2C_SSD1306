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

//#include "fonts_all.h"
#include "small5x7bold_font.h"
#include "term8x14_font.h"
#include "digits4x7_font.h"

const uint8_t npn [] PROGMEM = {28,4,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10,
0x10, 0x10, 0x10, 0x20, 0x20, 0xA0, 0x40, 0xA0, 0x10, 0x0F, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80,
0xE0, 0x9C, 0x82, 0x81, 0x80, 0x80, 0x80, 0x80, 0xFE, 0xFE, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02,
0x01, 0x00, 0x00, 0x00, 0x01, 0x02, 0x1C, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x38, 0x40, 0x80,
0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x02, 0x04, 0x08, 0x90, 0xA0, 0xC0, 0xF0, 0x00, 0x00, 0x00,
0x80, 0x40, 0x38, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04,
0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x05, 0x02, 0x05, 0x08, 0xF0, 0x00, 0x00
};

const uint8_t ind [] PROGMEM = {27,1,
0x40, 0x40, 0x40, 0x78, 0x04, 0x02, 0x02, 0x04, 0x78, 0x04, 0x02, 0x02, 0x04, 0x78, 0x04, 0x02,
0x02, 0x04, 0x78, 0x04, 0x02, 0x02, 0x04, 0x78, 0x40, 0x40, 0x40, 
};

void setup() 
{
  Serial.begin(9600);
  oled.init(oled128x32);  // 0-128x64, 1-128x32
}

// --------------------------------------------------------------------------
byte scr[100*6];  // full frame buffer - for demo
byte scrWd = 84;
byte scrHt = 6;

void clrBuf()
{
  int ii=0;
  for(int i=0;i<scrWd*scrHt;i++) scr[ii++]=0;
}
// --------------------------------------------------------------------------
void drawPixel(int16_t x, int16_t y, uint16_t color) 
{
  if(x<0 || x>=scrWd || y<0 || y>=scrHt*8) return;
  switch (color) {
    case 1: scr[x+(y/8)*scrWd] |=  (1 << (y&7)); break;
    case 0: scr[x+(y/8)*scrWd] &= ~(1 << (y&7)); break; 
    case 2: scr[x+(y/8)*scrWd] ^=  (1 << (y&7)); break; 
  }
}
// --------------------------------------------------------------------------

char buf[40];
void loop() 
{
  int i,j;
  oled.clrScr();
  oled.setFont(Term8x14PL);
  oled.printStr(ALIGN_RIGHT, 5, "Cnt:");
  oled.drawBitmap(npn, 3, 0);
  oled.drawBitmap(ind, 127-27-6, 0);
  oled.fillWin(ALIGN_RIGHT,2,44,2,0xaa);
  oled.setFont(Small5x7PLBold);
  oled.printStr(0,2,"B");
  oled.printStr(30,0,"E");
  oled.printStr(30,3,"C");
  oled.printStr(127-5-6-27,0,"0");
  oled.printStr(127-5,0,"1");
  oled.setFont(Digits4x7);
  oled.setDigitMinWd(4);
  
  // 54x16 pixels graph
  scrWd = 54;
  scrHt = 2;
  for(j=0;j<400;j++) {
    clrBuf();  
    for(i = 0;i<scrWd;i++) {
      int y = sin(i/5.0)*sin(j/10.0+i/10.0)*8+8;
      drawPixel(i,y,1);
    }
    oled.drawBuf(scr,0,6,scrWd,scrHt);
    snprintf(buf,39,"%06d",random(1,1000000));
    if((j%4)==0) oled.printStr(ALIGN_RIGHT,7,buf);
    //delay(20);
  }
  
  // full screen graph
  oled.clrScr();
  scrWd = 100;
  scrHt = 6;
  for(j=0;j<400;j++) {
    clrBuf();  
    for(i = 0;i<scrWd;i++) {
      int y = sin(i/10.0)*sin(j/10.0+i/20.0)*24+24;
      drawPixel(i,y,1);
      drawPixel(i,y+1,1);
      drawPixel(i+1,y,1);
      drawPixel(i+1,y+1,1);
      drawPixel(i,0,1);
      drawPixel(i,scrHt*8-1,1);
    }
    for(i=1;i<scrHt*8-1;i++) {
      drawPixel(0,i,1);
      drawPixel(scrWd-1,i,1);
    }
    oled.drawBuf(scr,ALIGN_CENTER,1,scrWd,scrHt);
    //oled.setFont(Small5x7PLBold);
    //oled.printStr(ALIGN_CENTER,1,"GRAPH");
    //delay(20);
  }

}
