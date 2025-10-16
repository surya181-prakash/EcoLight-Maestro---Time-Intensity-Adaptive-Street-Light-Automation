#include "types.h"
//include LCD header files
#include "lcd.h"
//#include "lpc21xx.h"
#include "lcd_defines.h"
#include "adc.h"
#include "kpm.h"
#include "rtc_defines.h"
#include "rtc.h"
#include <lpc214x.h>
#include "delay.h"
#include "pin_connect_block.h"
#define EINT0_FUN FUN2
#define FUN2 1
#define EINT0 14
//#define EINT0_LED 18
int cnt,flag=0;
void edit_time(void)
{ //delay_s(1);
    char key2;
	  int key1; 
    int exit_flag = 0;
//delay_s(1);
    while(1)
    {   key2=0;
        CmdLCD(0x01);                 
        CmdLCD(0x80);
        StrLCD("1:hr 2:min 3:sec");
        CmdLCD(0xC0);
        StrLCD("4:date 5:mon 6:exit");
         delay_ms(100);
        key2 = KeyScan();
			
			// wait for key press
         //CharLCD(key2);
			  delay_ms(1000);
        switch(key2)
        {
            case '1': // Edit hour
                key1=0;
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("SETING HOUR");
                key1 = ReadNum();
						    U32LCD(key1);
					    	delay_ms(1000);
                if(key1 >= 0 && key1 <= 23)
                {
                    HOUR = key1;
                    CmdLCD(0xC0);
									 //delay_s(1);
                   StrLCD("UPDATED");
									  delay_s(1);
                }
                else
                {
                    CmdLCD(0xC0);
                    StrLCD("ERROR Hour");
								  	 delay_s(1);
                }
                break;

            case '2': // Edit minute
							  key1=0;
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("SETING MIN");
						     
                key1= ReadNum();
                if(key1 >= 0 && key1 <= 59)
                {
                    MIN = key1;
                    CmdLCD(0xC0);
                    StrLCD("UPDATED");
									  delay_s(1);
                }
                else
                {
                    CmdLCD(0xC0);
                    StrLCD("ERROR Minute");
									  delay_s(1);
                }
                break;

            case '3': // Edit second
						  	key1=0;
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("Setting SEC ");
						    
                key1 = ReadNum();
                if(key1 >= 0 && key1 <= 59)
                {
                    SEC = key1;
                    CmdLCD(0xC0);
                    StrLCD("UPDATED");
									 delay_s(1);
                }
                else
                {
                    CmdLCD(0xC0);
                    StrLCD("ERROR Second");
									 delay_s(1);
                }
                break;

            case '4': // Edit date
							  key1=0;
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("Setting Date");
                key1 = ReadNum();
                if(key1 >= 1 && key1 <= 31)
                {
                    DOM = key1;
                    CmdLCD(0xC0);
                    StrLCD("UPDATED");
									  delay_s(1);
                }
                else
                {
                    CmdLCD(0xC0);
                    StrLCD("ERROR Date");
									  delay_s(1);
                }
                break;

            case '5': // Edit month
							   key1=0;
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("Setting MONTH");
                key1 = ReadNum();
                if(key1 >= 1 && key1 <= 12)
                {
                    MONTH = key1;
                    CmdLCD(0xC0);
                    StrLCD("UPDATED");
									 delay_s(1);
                }
                else
                {
                    CmdLCD(0xC0);
                    StrLCD("ERROR Month");
									   delay_s(1);
                }
                break;

            case '6': // Exit
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("EXIT");
							 delay_s(1);
                exit_flag = 1;   // set flag to break
                break;
        }

        if(exit_flag == 1)
            break;
				key1=0;
    }
}

void change_time(void)
{
    //SetRTCTimeInfo(10, 20, 01);
    //DisplayRTCDate(10, 20, 01);
    while(1)
    { char key;
			CmdLCD(0x01);
			CmdLCD(0xc0);
			 CmdLCD(0x80);
    StrLCD("1. EDIT RTC INFO");
    CmdLCD(0xC0);
    StrLCD("2. EXIT");
         key = KeyScan();
        if(key == '1')
        {
            edit_time();
        }
        else if(key == '2')
        {
            CmdLCD(0x01);
            StrLCD("Exit Selected");
					  delay_s(1);
            break;
        }
    }

  
}
void eint0_isr(void)__irq
{
	//toggle the led
  flag=1;
	EXTINT=1<<0;
	VICVectAddr=0;
}
void enable_eint0(void)
{
	//cfg the led pin as an output

	// p0.16 is cfg as eint0
	CfgPortPinFunc(0,16,EINT0_FUN);
	//select the type of the interrupt irq/fiq
	VICIntSelect=0;//irq type
	//enable the eint0
	VICIntEnable=1<<EINT0;
	//set the enable bit and channel binary 
	VICVectCntl0=(1<<5)|EINT0;
	//assign the ISR address
	VICVectAddr0=(unsigned int)eint0_isr;
	//edge triggereing
	EXTMODE=1<<0;
	//falling edge
	EXTPOLAR=0<<0;
}
int main()
{
	float avg=0,total=0;
	
	s32 hour,min,sec,cnt=0,date,month,year,day;
	float eAR;
  unsigned int adcDVal;
	//enable_eint0();
	InitLCD();
	enable_eint0();
	//IODIR1=IODIR1|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN);
	
	
	Init_ADC();
	Init_KPM();
	RTC_Init();
		IODIR1|=1<<27;
	SetRTCTimeInfo(20, 26, 00);
	 //IOSET1=3<<16;
	while(1){
		total=0,cnt=0;
	  GetRTCTimeInfo(&hour,&min,&sec);
			DisplayRTCTime(hour,min,sec);
  		GetRTCDateInfo(&date,&month,&year);
			DisplayRTCDate(date,month,year);
			GetRTCDay(&day);
			DisplayRTCDay(day);
	   //CmdLCD(GOTO_LINE1_POS0);
	  	Read_ADC(0,&adcDVal,&eAR);
				CmdLCD(0xc0+8);
				//F32LCD(e,3);
				U32LCD(adcDVal);
		if(flag==1)
		{
			change_time();
			CmdLCD(0x01);
			flag=0;
			
		}
		if(HOUR>=18||HOUR<=6)
		{
			while(cnt!=10){
				total+=eAR;
				cnt++;
			}
			avg=total/10;
		
			if(avg<=1.0)
			{
		    IOSET1=1<<27;
			
		  }
			else
			{
				IOCLR1=1<<27;
				
				
			}
		}
	
}
}