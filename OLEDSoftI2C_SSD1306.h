#ifndef OLEDSoftI2C_SSD1306_H
#define OLEDSoftI2C_SSD1306_H 

#define USEHW 0

#define SCR_WD  128
#define SCR_HT  64

#define CTR_CMD  0x00
#define CTR_DAT  0x40

#define ALIGN_LEFT    0
#define ALIGN_RIGHT  -1 
#define ALIGN_CENTER -2

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A 

#include <Arduino.h>
#include <avr/pgmspace.h>

class OLEDSoftI2C_SSD1306 {
public:
    OLEDSoftI2C_SSD1306(int addr=0x3c);
    void writeData(byte data);
    void writeCmd(byte command);
    void setVWin(uint8_t colS, uint8_t rowS, uint8_t wd, uint8_t ht);
    void setHWin(uint8_t colS, uint8_t rowS, uint8_t wd, uint8_t ht);
    void writeStart();
    void writeStop();
    void write(uint8_t val);
    void scroll();
    void enable();
    void disable();
    void contrast(int c);
    void scrollV(int y);
    void flipV(bool flip);
    void flipH(bool flip);
    void invert(bool inv);	
    void displayMode(byte val);
    void init(int mode=0);

    int drawBuf(uint8_t *buf, int x, uint8_t y8, uint8_t wd, uint8_t ht8);
    int drawBitmap(const uint8_t *bmp, int x, uint8_t y8, uint8_t wd, uint8_t ht8);
    int drawBitmap(const uint8_t *bmp, int x, uint8_t y8);
    int fillWin(int x, int y8, int wd, int ht8, int val);
    void clrScr();

    void setFont(const uint8_t* f);
  	void setCR(uint8_t _cr) { cr = _cr; }
    void setFontMinWd(uint8_t wd) { minCharWd = wd; }
    void setCharMinWd(uint8_t wd) { minCharWd = wd; }
    void setDigitMinWd(uint8_t wd) { minDigitWd = wd; }
  	int printStr(int x, uint8_t y8, char *txt);
    uint8_t printChar(uint8_t x, uint8_t row, uint8_t ch);
    int charWidth(uint8_t _ch, bool last=true);
    int strWidth(char *txt);
    unsigned char convertPolish(unsigned char _c);

    int i2cAddr = 0x3c;

private:
    const uint8_t* font; 
    uint8_t xSize;
    uint8_t ySize;
    uint8_t ySize8;
  	uint8_t firstCh;
	  uint8_t lastCh;
    uint8_t minCharWd;
    uint8_t minDigitWd;
    uint8_t cr;  // carriage return mode for printStr
    uint8_t dualChar;
};
#endif

