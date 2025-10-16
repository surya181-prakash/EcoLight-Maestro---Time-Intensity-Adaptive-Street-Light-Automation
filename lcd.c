//lcd.c
#include <LPC21xx.h>
#include "defines.h"
#include "lcd_defines.h"
#include "delay.h"

void WriteLCD(unsigned char anyByte)
{
	//select write operation
	IOCLR0=1<<LCD_RW;
	//put any byte onto data pins d0-d7
	WRITEBYTE(IOPIN0,LCD_DATA,anyByte);
	//provide high to low pulse
	IOSET0=1<<LCD_EN;
	delay_us(1);
	IOCLR0=1<<LCD_EN;
	delay_ms(2);
}

void CmdLCD(unsigned char cmd)
{
	//select cmd/inst reg
	IOCLR0=1<<LCD_RS;
	//write cmd to reg
	WriteLCD(cmd);
}

void CharLCD(unsigned char asciiVal)
{
 	//select data reg
	IOSET0=1<<LCD_RS;
	//write ascii via data reg to ddram/display
	WriteLCD(asciiVal);	
}

void InitLCD(void)
{
	//cfg p0.0 to p0.18 as gpio output pins
	IODIR0=(0xFF<<LCD_DATA)|1<<LCD_RS
	       |1<<LCD_RW|1<<LCD_EN;
	//power on delay
	delay_ms(15);
	
	CmdLCD(0x30);
	delay_ms(4);
	delay_us(100);
	CmdLCD(0x30);
	delay_us(100);
	CmdLCD(0x30);
	CmdLCD(MODE_8BIT_2LINE);
	CmdLCD(DSP_ON_CUR_OFF);
	CmdLCD(CLEAR_LCD);
  CmdLCD(SHIFT_CUR_RIGHT);	
}

void StrLCD(char *p)
{
	while(*p)
	{	
		CharLCD(*p++);		
	}	
}

void U32LCD(unsigned int num)
{
	unsigned char a[10];
	int i=0;
	if(num==0)
	{
		CharLCD('0');
	}
	else
	{
		while(num>0)
		{
			a[i]=(num%10)+48;
			i++;
			num/=10;
		}
		for(--i;i>=0;i--)
		{
			CharLCD(a[i]);
		}			
	}
}

void S32LCD(int snum)
{
	if(snum<0)
	{
		CharLCD('-');
		snum=-snum;
	}
	U32LCD(snum);
}

void F32LCD(float fNum,unsigned char nDP)
{
  unsigned int num,i;
	if(fNum<0.0)
	{
		CharLCD('-');
		fNum=-fNum;
	}
	num=fNum;
	U32LCD(num);
	CharLCD('.');
	for(i=0;i<nDP;i++)
	{
		fNum=(fNum-num)*10;
		num=fNum;
		CharLCD(num+48);
	}
}

void BuildCGRAM(unsigned char *p,
	              unsigned char nBytes)
{
	unsigned int i;
  //goto cgram start
  CmdLCD(GOTO_CGRAM_START);
	//select data reg
	IOSET0=1<<LCD_RS;
	for(i=0;i<nBytes;i++)
	{
		//write to cgram memory
		WriteLCD(p[i]);
	}
	//return back to ddram
	CmdLCD(GOTO_LINE1_POS0);
}
