#include "OLEDSoftI2C_SSD1306.h"

#if USEHW==1
#include <Wire.h>
#else
#include "SoftI2C.h"
#endif

// ---------------------------------
OLEDSoftI2C_SSD1306::OLEDSoftI2C_SSD1306(int addr)
{
  i2cAddr = addr;
  cr = 0;
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::setHWin(uint8_t colS, uint8_t rowS, uint8_t wd, uint8_t ht)
{
  writeCmd(0x20); //set horizontal addressing mode
  writeCmd(0x00);
  
  writeCmd(0x21); //set column start and end address
  writeCmd(colS); //set column start address
  writeCmd(colS+wd-1); //set column end address
  
  writeCmd(0x22); //set row start and end address
  writeCmd(rowS); //set row start address
  writeCmd(rowS+ht-1); //set row end address
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::setVWin(uint8_t colS, uint8_t rowS, uint8_t wd, uint8_t ht)
{
  writeCmd(0x20); //set vertical addressing mode
  writeCmd(0x01);
  
  writeCmd(0x21); //set column start and end address
  writeCmd(colS); //set column start address
  writeCmd(colS+wd-1); //set column end address
  
  writeCmd(0x22); //set row start and end address
  writeCmd(rowS); //set row start address
  writeCmd(rowS+ht-1); //set row end address
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::writeData(byte data)
{
    #if USEHW==1
    Wire.beginTransmission(i2cAddr);
    Wire.write(CTR_DAT);
    Wire.write(data);
    Wire.endTransmission();
    #else
    i2c_start(i2cAddr<<1 | I2C_WRITE);
    i2c_write(CTR_DAT);
    i2c_write(data);
    i2c_stop();
    #endif
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::writeCmd(byte command)
{
    #if USEHW==1
    Wire.beginTransmission(i2cAddr);
    Wire.write(CTR_CMD);
    Wire.write(command);
    Wire.endTransmission();
    #else
    i2c_start(i2cAddr<<1 | I2C_WRITE);
    i2c_write(CTR_CMD);
    i2c_write(command);
    i2c_stop();
    #endif
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::scroll()
{
  writeCmd(0x27); //set right horizontal scroll
  writeCmd(0x0);  //dummy byte
  writeCmd(0x0);  //page start address
  writeCmd(0x7);  //scroll speed
  writeCmd(0x7);  //page end address
  writeCmd(0x0);  //dummy byte
  writeCmd(0xff); //dummy byte
  writeCmd(0x2f); //start scrolling
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::enable()
{
  writeCmd(0xaf);
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::disable()
{
  writeCmd(0xae);
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::contrast(int c)
{
  writeCmd(0x81);
  writeCmd(c);
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::scrollV(int y)
{
  writeCmd(0x40+y); //set right horizontal scroll
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::flipV(bool flip)
{
  writeCmd(flip ? 0xc0 : 0xc8);
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::flipH(bool flip)
{
  writeCmd(flip ? 0xa0 : 0xa1);
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::invert(bool inv)
{
  writeCmd(inv ? 0xa7 : 0xa6);
}
// ---------------------------------
// val:
// SSD1306_DISPLAYOFF
// SSD1306_DISPLAYON
// SSD1306_NORMALDISPLAY
// SSD1306_DISPLAYALLON
// SSD1306_INVERTDISPLAY
void OLEDSoftI2C_SSD1306::displayMode(byte val)
{
  writeCmd(val);
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::writeStart()
{
#if USEHW==1
  Wire.beginTransmission(i2cAddr);
  Wire.write(CTR_DAT);
#else
  i2c_start(i2cAddr<<1 | I2C_WRITE);
  i2c_write(CTR_DAT);
#endif
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::writeStop()
{
#if USEHW==1
  Wire.endTransmission();
#else
  i2c_stop();
#endif
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::write(uint8_t val)
{
#if USEHW==1
  Wire.write(val);
#else
  i2c_write(val);
#endif
}
// ---------------------------------
// 0 - 128x64
// 1 - 128x32
void OLEDSoftI2C_SSD1306::init(int mode)
{
  font = NULL;
  dualChar = 0;
  
  #if USEHW==1
  Wire.begin();
  Wire.setClock(800000); // faster I2C
  #else
  Serial.println(i2c_init() ? F("SoftI2C initialization done") : F("SoftI2C initialization error. SDA or SCL are low"));
  #endif
/*  
  writeCmd(0x8d); //enable charge pump
  writeCmd(0x14);
  delay(1);
  writeCmd(0xaf); //set display on

  writeCmd(0xa8); //set MUX ratio
  writeCmd(mode==0 ? 0x3f : 0x1f);
  writeCmd(0xd3); //set display offset
  writeCmd(0x00);
  writeCmd(0x40); //set display start line
  writeCmd(0xa1); //set segment re-map (horizontal flip) - reset value is 0xa0 (or 0xa1)
  writeCmd(0xc8); //set COM output scan direction (vertical flip) - reset value is 0xc0 (or 0xc8)
  writeCmd(0xda); //set COM pins hardware configuration
  writeCmd(mode==0 ? 0x12 : 0x02); //reset value is 0x12
  writeCmd(0x81); //set contrast (2-byte)
  writeCmd(0xff);*/
//  writeCmd(0xa4); //disable entire display on
//  writeCmd(0xa6); //set normal display
//  writeCmd(0xd5); //set oscillator frequency
//  writeCmd(0x80);
//  writeCmd(0xdb); //vcomh deselect level (brightness)
//  writeCmd(0x20);

    writeCmd(SSD1306_DISPLAYOFF);                    // 0xAE
    writeCmd(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    writeCmd(0x80);                                  // the suggested ratio 0x80
    writeCmd(SSD1306_SETMULTIPLEX);                  // 0xA8
    writeCmd(mode==0 ? 0x3f : 0x1f);
    writeCmd(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    writeCmd(0x0);                                   // no offset
    writeCmd(SSD1306_SETSTARTLINE | 0x0);            // line #0
    writeCmd(SSD1306_CHARGEPUMP);                    // 0x8D
    writeCmd(0x14);                                  // 0x14, 0x10 for EXTERNALVCC
    writeCmd(SSD1306_MEMORYMODE);                    // 0x20
    writeCmd(0x00);                                  // 0x0 act like ks0108
    writeCmd(SSD1306_SEGREMAP | 0x1);
    writeCmd(SSD1306_COMSCANDEC);
    writeCmd(SSD1306_SETCOMPINS);                    // 0xDA
    writeCmd(mode==0 ? 0x12 : 0x02);
    writeCmd(SSD1306_SETCONTRAST);                   // 0x81
    writeCmd(0xCF);                                  // 0xcf, 0x9f for EXTERNALVCC
    writeCmd(SSD1306_SETPRECHARGE);                  // 0xd9
    writeCmd(0xF1);                                  // 0xf1, 0x22  for EXTERNALVCC
    writeCmd(SSD1306_SETVCOMDETECT);                 // 0xDB
    writeCmd(0x40);
    writeCmd(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
    writeCmd(SSD1306_NORMALDISPLAY);                 // 0xA6

    writeCmd(SSD1306_DISPLAYON);//--turn on oled panel 
}
// ---------------------------------
#define ALIGNMENT \
  if(x==-1)\
    x = SCR_WD-wd; \
  else if(x<0) \
    x = (SCR_WD-wd)/2; \
  if(x<0) x=0; \
  if(x>=SCR_WD || y8>=SCR_HT/8) return 0; \
  if(x+wd>SCR_WD) wd = SCR_WD-x; \
  if(y8+ht8>SCR_HT/8) ht8 = SCR_HT/8-y8

int OLEDSoftI2C_SSD1306::fillWin(int x, int y8, int wd, int ht8, int val)
{
  ALIGNMENT;
  setVWin(x,y8,wd,ht8);
#if USEHW==1
  for(int i=0; i<wd*ht8; i++) {
    Wire.beginTransmission(i2cAddr);
    Wire.write(CTR_DAT);
    Wire.write(val);
    Wire.endTransmission();
  }
#else
  i2c_start(i2cAddr<<1 | I2C_WRITE);
  i2c_write(CTR_DAT);
  for(int i=0; i<wd*ht8; i++) i2c_write(val);
  i2c_stop();
#endif
  return x+wd;
}
// ---------------------------------
void OLEDSoftI2C_SSD1306::clrScr()
{
  setVWin(0,0,SCR_WD,SCR_HT/8);
#if USEHW==1
  for (int i=0; i<SCR_WD*SCR_HT/8; i+=16) 
  {
    Wire.beginTransmission(i2cAddr);
    Wire.write(CTR_DAT);
    for(int j=0; j<4; j++)  // send 16 bytes
      {Wire.write(0); Wire.write(0); Wire.write(0); Wire.write(0);}
    Wire.endTransmission();
  }
#else
  i2c_start(i2cAddr<<1 | I2C_WRITE);
  i2c_write(CTR_DAT);
  for (int i=0; i<SCR_WD*SCR_HT/8/4; i++) {i2c_write(0); i2c_write(0); i2c_write(0); i2c_write(0); }
  i2c_stop();
#endif
}
// ---------------------------------
int OLEDSoftI2C_SSD1306::drawBuf(uint8_t *bmp, int x, uint8_t y8, uint8_t wd, uint8_t ht8)
{
  uint8_t wdb = wd;
  ALIGNMENT;
  setHWin(x,y8,wd,ht8);
#if USEHW==1
  for(int j=0; j<ht8; j++) {
    for(int i=0; i<wd; i++) {
      Wire.beginTransmission(i2cAddr);
      Wire.write(CTR_DAT);
      Wire.write(*(bmp+i));
      Wire.endTransmission();
    }
    bmp += wdb;
  }
#else
  i2c_start(i2cAddr<<1 | I2C_WRITE);
  i2c_write(CTR_DAT);
  for (int j=0; j<ht8; j++) {
    for (int i=0; i<wd; i++) i2c_write(*(bmp+i));
    bmp += wdb;
  }
  i2c_stop();
#endif
  return x+wd;
}
// ---------------------------------
int OLEDSoftI2C_SSD1306::drawBitmap(const uint8_t *bmp, int x, uint8_t y8, uint8_t wd, uint8_t ht8)
{
  uint8_t wdb = wd;
  ALIGNMENT;
  setHWin(x,y8,wd,ht8);
#if USEHW==1
  for(int j=0; j<ht8; j++) {
    for(int i=0; i<wd; i++) {
      Wire.beginTransmission(i2cAddr);
      Wire.write(CTR_DAT);
      Wire.write(pgm_read_byte(bmp+i));
      Wire.endTransmission();
    }
    bmp += wdb;
  }
#else
  i2c_start(i2cAddr<<1 | I2C_WRITE);
  i2c_write(CTR_DAT);
  for(int j=0; j<ht8; j++) {
    for(int i=0; i<wd; i++) i2c_write(pgm_read_byte(bmp+i));
    bmp += wdb;
  }
  i2c_stop();
#endif
  return x+wd;
}
// ---------------------------------
int OLEDSoftI2C_SSD1306::drawBitmap(const uint8_t *bmp, int x, uint8_t y8)
{
  uint8_t wd  = pgm_read_byte(bmp++);
  uint8_t ht8 = pgm_read_byte(bmp++);
  return drawBitmap(bmp, x, y8, wd, ht8);
}
// ---------------------------------
// text rendering stuff
// ---------------------------------
void OLEDSoftI2C_SSD1306::setFont(const uint8_t* f)
{
  font     = f;
  xSize    =-pgm_read_byte(font+0);
  ySize    = pgm_read_byte(font+1);
  firstCh  = pgm_read_byte(font+2);
  lastCh   = pgm_read_byte(font+3);
  ySize8   = (ySize+7)/8;
  minCharWd  = 0;
  minDigitWd = 0;
  cr = 0;
  invertCh = 0;
}
// ---------------------------------
int OLEDSoftI2C_SSD1306::printStr(int x, uint8_t y8, char *txt)
{
  if(!font) return 0;
  int xpos = x;
  int ypos = y8;
  if(xpos==-1)
    xpos = SCR_WD-strWidth(txt);  // align to right
  else if(xpos<0)
    xpos = (SCR_WD-strWidth(txt))/2;  // center
  if(xpos<0) xpos=0;
  while (*txt) {
    if(*txt==10) { // \n clears area to the end of line and jumps to the next line
      fillWin(xpos,ypos,SCR_WD-xpos,ySize8,0);
      xpos = 0;
      ypos += ySize8;
      txt++;
    } else {
      int wd = printChar(xpos, ypos, *txt++);
      xpos += wd;
      if(cr && xpos>=SCR_WD) {
        xpos = 0;
        ypos += ySize8;
        if(ypos>SCR_HT/8)
          ypos = 0;
      }
    }
  }
  return xpos;
}
// ---------------------------------
int OLEDSoftI2C_SSD1306::strWidth(char *txt)
{
  if(!font || !txt || !*txt) return 0;
  int wd = 0;
  char ch;
  while(*txt)
    if(*txt<' ') txt++; else wd+=charWidth((ch=*txt++));
  return wd-(charWidth(ch,true)-charWidth(ch,false));
}
// ---------------------------------
int OLEDSoftI2C_SSD1306::charWidth(uint8_t _ch, bool last)
{
  int ch = convertPolish(_ch);
  if(!font || ch<firstCh || ch>lastCh) return 0;
  int idx = 4 + (ch - firstCh)*(xSize*ySize8+1);
  int wd = pgm_read_byte(font + idx);
  int wdL = 0, wdR = 1; // default spacing before and behind char
  if(isdigit(ch)) {
    if(minDigitWd>wd) {
      wdL = (minDigitWd-wd)/2;
      wdR += (minDigitWd-wd-wdL);
    }
  } else
  if(minCharWd>wd) {
    wdL = (minCharWd-wd)/2;
    wdR += (minCharWd-wd-wdL);
  }
  return last ? wd+wdL+wdR : wd+wdL;  // last!=0 -> get rid of last empty columns
}
// ---------------------------------
uint8_t OLEDSoftI2C_SSD1306::printChar(uint8_t x, uint8_t row, uint8_t _ch)
{
  int ch = convertPolish(_ch);
  if(!font || ch<firstCh || ch>lastCh || x>=SCR_WD || row>=SCR_HT/8) return 0;

  int j,i, idx = 4 + (ch - firstCh)*(xSize*ySize8+1);
  int wd = pgm_read_byte(font + idx++);
  int wdL = 0, wdR = 1; // default spacing before and behind char
  if(isdigit(ch)) {
    if(minDigitWd>wd) {
      wdL = (minDigitWd-wd)/2;
      wdR += (minDigitWd-wd-wdL);
    }
  } else
  if(minCharWd>wd) {
    wdL = (minCharWd-wd)/2;
    wdR += (minCharWd-wd-wdL);
  }
  if(x+wd+wdL+wdR>SCR_WD) wdR = max(SCR_WD-x-wdL-wd, 0);
  if(x+wd+wdL+wdR>SCR_WD) wd = max(SCR_WD-x-wdL, 0);
  if(x+wd+wdL+wdR>SCR_WD) wdL = max(SCR_WD-x, 0);
  setVWin(x, row, wd+wdL+wdR, ySize8);
  wdL *= ySize8;
  wdR *= ySize8;
  wd *= ySize8;
#if USEHW==1
  Wire.beginTransmission(i2cAddr);
  Wire.write(CTR_DAT);
  if(!invertCh) {
    for(i=0; i<wdL; i++) Wire.write(0);
    for(i=0; i<wd; i++)  Wire.write(pgm_read_byte(font+idx+i));
    for(i=0; i<wdR; i++) Wire.write(0);
  } else {
    for(i=0; i<wdL; i++) Wire.write(0xff);
    for(i=0; i<wd; i++)  Wire.write(pgm_read_byte(font+idx+i)^0xff);
    for(i=0; i<wdR; i++) Wire.write(0xff);
  }
  Wire.endTransmission();
#else
  i2c_start(i2cAddr<<1 | I2C_WRITE);
  i2c_write(CTR_DAT);
  if(!invertCh) {
    for(i=0; i<wdL; i++) i2c_write(0);
    for(i=0; i<wd; i++)  i2c_write(pgm_read_byte(font+idx+i));
    for(i=0; i<wdR; i++) i2c_write(0);
  } else {
    for(i=0; i<wdL; i++) i2c_write(0xff);
    for(i=0; i<wd; i++)  i2c_write(pgm_read_byte(font+idx+i)^0xff);
    for(i=0; i<wdR; i++) i2c_write(0xff);
  }
  i2c_stop();
#endif
  return (wd+wdL+wdR)/ySize8;
}
// ---------------------------------
unsigned char OLEDSoftI2C_SSD1306::convertPolish(unsigned char _c)
{
  unsigned char pl, c = _c;
  if(c==196 || c==197 || c==195) {
	  dualChar = c;
    return 0;
  }
  if(dualChar) { // UTF8 coding
    switch(_c) {
      case 133: pl = 1+9; break; // '¹'
      case 135: pl = 2+9; break; // 'æ'
      case 153: pl = 3+9; break; // 'ê'
      case 130: pl = 4+9; break; // '³'
      case 132: pl = dualChar==197 ? 5+9 : 1; break; // 'ñ' and '¥'
      case 179: pl = 6+9; break; // 'ó'
      case 155: pl = 7+9; break; // 'œ'
      case 186: pl = 8+9; break; // 'Ÿ'
      case 188: pl = 9+9; break; // '¿'
      //case 132: pl = 1; break; // '¥'
      case 134: pl = 2; break; // 'Æ'
      case 152: pl = 3; break; // 'Ê'
      case 129: pl = 4; break; // '£'
      case 131: pl = 5; break; // 'Ñ'
      case 147: pl = 6; break; // 'Ó'
      case 154: pl = 7; break; // 'Œ'
      case 185: pl = 8; break; // ''
      case 187: pl = 9; break; // '¯'
      default:  return c; break;
    }
    dualChar = 0;
  } else   
  switch(_c) {  // Windows coding
    case 165: pl = 1; break; // ¥
    case 198: pl = 2; break; // Æ
    case 202: pl = 3; break; // Ê
    case 163: pl = 4; break; // £
    case 209: pl = 5; break; // Ñ
    case 211: pl = 6; break; // Ó
    case 140: pl = 7; break; // Œ
    case 143: pl = 8; break; // 
    case 175: pl = 9; break; // ¯
    case 185: pl = 10; break; // ¹
    case 230: pl = 11; break; // æ
    case 234: pl = 12; break; // ê
    case 179: pl = 13; break; // ³
    case 241: pl = 14; break; // ñ
    case 243: pl = 15; break; // ó
    case 156: pl = 16; break; // œ
    case 159: pl = 17; break; // Ÿ
    case 191: pl = 18; break; // ¿
    default:  return c; break;
  }
  return pl+'~'+1;
}
// ---------------------------------
