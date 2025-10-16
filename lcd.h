#ifndef LCD_H

#define LCD_H


//lcd.h

void WriteLCD(unsigned char anyByte);

void CmdLCD(unsigned char cmd);

void CharLCD(unsigned char asciiVal);

void InitLCD(void);

void StrLCD(char *p);

void U32LCD(unsigned int num);

void S32LCD(int snum);

void F32LCD(float fNum,unsigned char nDP);

void BuildCGRAM(unsigned char *p,

	              unsigned char nBytes);




#endif