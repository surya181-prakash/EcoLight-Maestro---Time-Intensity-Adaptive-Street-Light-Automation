#include <LPC21xx.H>


#include "rtc_defines.h"

#include "types.h"

#include "lcd.h"

#include "lcd_defines.h"


// Array to hold names of days of the week

char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};




/*

Initialize the Real-Time Clock (RTC)

This function disables the RTC, sets the prescaler values, 

and then enables the RTC.

*/

void RTC_Init(void) 

{

  // Disable and reset the RTC

	CCR = RTC_RESET;


#if (CPU == LPC2129)	

  // Set prescaler integer and fractional parts

	PREINT = PREINT_VAL;

	PREFRAC = PREFRAC_VAL;

	CCR = RTC_ENABLE; 

#elif(CPU == LPC2148)

  // Enable the RTC

	CCR = RTC_ENABLE | RTC_CLKSRC;  

#endif

}


/*

Get the current RTC time

hour Pointer to store the current hour

minute Pointer to store the current minute

second Pointer to store the current second

*/

void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)

{

	*hour = HOUR;

	*minute = MIN;

	*second = SEC;

}


/*

Display the RTC time on LCD

hour value (0 23)

minute value (0 59)

second value (0 59) seperated by ':'

*/

void DisplayRTCTime(u32 hour, u32 minute, u32 second)

{

	CmdLCD(GOTO_LINE1_POS0);

	CharLCD((hour/10)+48);

	CharLCD((hour%10)+48);

	CharLCD(':');

	CharLCD((minute/10)+48);

	CharLCD((minute%10)+48);

	CharLCD(':');

	CharLCD((second/10)+48);

	CharLCD((second%10)+48);

}


/*

Get the current RTC date

day Pointer to store the current date (1 31)

month Pointer to store the current month (1 12)

year Pointer to store the current year (four digits)

*/

void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)

{

	*date = DOM;

	*month = MONTH;

	*year = YEAR;

}


/*

Display the RTC date on LCD

Day of month (1 31)

Month (1 12)

Year (four digits) and seperated by '/'

*/

void DisplayRTCDate(u32 date, u32 month, u32 year)

{

	CmdLCD(GOTO_LINE2_POS0);

	CharLCD((date/10)+48);

	CharLCD((date%10)+48);

	CharLCD('/');

	CharLCD((month/10)+48);

	CharLCD((month%10)+48);

	CharLCD('/');

	U32LCD(year);

}


/*

Set the RTC time

Hour to set (0 23)

Minute to set (0 59)

Second to set (0 59)

*/

void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)

{

	HOUR = hour;

	MIN = minute;

	SEC = second;

}


/*

Set the RTC date

day of month to set (1 31)

month to set (1 12)

year to set (four digits)

*/

void SetRTCDateInfo(u32 date, u32 month, u32 year)

{

	DOM = date;

	MONTH = month;

	YEAR = year;

}


/*

Get the current day of the week

dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)

*/

void GetRTCDay(s32 *day)

{

	*day = DOW;

}


/*

Display the current day of the week on LCD

dow (Day of Week) (0=Sunday, ..., 6=Saturday)

*/

void DisplayRTCDay(u32 day)

{

	CmdLCD(GOTO_LINE1_POS0+10);

	StrLCD(week[day]);

  

}


/*

Set the day of the week in RTC

Day of Week to set (0=Sunday, ..., 6=Saturday)

*/

void SetRTCDay(u32 day)

{

	DOW = day;

}