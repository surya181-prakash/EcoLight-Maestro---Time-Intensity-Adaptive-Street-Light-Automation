//kpm.c
#include <LPC21xx.h>
#include "defines.h"
#include "kpm_defines.h"

/*const unsigned int kpmLUT[4][4]=
{
	{1,2,3,4},
	{5,6,7,8},
	{9,10,11,12},
	{13,14,15,16},
};
*/
const char  kpmLUT[4][4]=
{
	{'7','8','9','/'},
	{'4','5','6','X'},
	{'1','2','3','-'},
	{'C','0','=','+'},
};

void Init_KPM(void)
{
	//cfg p1.16 to p1.19 as gpio out
	//for row lines,all rows grounded
	WRITENIBBLE(IODIR1,ROW0,15);
	//default all col lines are high,input
}

unsigned int ColScan(void)
{
	unsigned int status;
	status=(READNIBBLE(IOPIN1,COL0)<15)?0:1;
	return status;
}

unsigned int RowCheck(void)
{
	unsigned int r;
	for(r=0;r<=3;r++)
	{
		//ground one row at a time,
		//keeping other rows high,
		//starting with 0th row
		WRITENIBBLE(IOPIN1,ROW0,~(1<<r));
		//check if any key pressed in that row
		if(ColScan()==0)
		{
			break;
		}
	}
	//re-initialize all rows to ground
	WRITENIBBLE(IOPIN1,ROW0,0);
	//return row in which key was pressed
	return r;
}

unsigned int ColCheck(void)
{
	unsigned int c;
	for(c=0;c<=3;c++)
	{
		if(READBIT(IOPIN1,COL0+c)==0)
		{
			break;
		}
	}
	return c;
}

unsigned int KeyScan(void)
{
	unsigned int r,c,key;
	//wait for any key press
	while(ColScan());
	//if any key pressed
	//identify row in which key was pressed
	r=RowCheck();
	//identify col in which key was pressed
	c=ColCheck();
	//extract key value for look up table
	//using row & col indices
	key=kpmLUT[r][c];
	//return val
	return key;
}

/*void ReadNum(unsigned int *num,char *key)
{
	*num=0;
	while(1)
	{
		*key=KeyScan();
		if(*key>='0' && *key<='9')
		{
 		*num=(*num * 10)+(*key-'0');
			while(ColScan()==0);
		}
		else
		{
			while(ColScan()==0);
			break;
		}
	}
}
*/

unsigned int ReadNum(void)
{
	 unsigned int sum=0;
	unsigned char num;
	while(1)
	{
		num=KeyScan();
		if(num>='0'&&num<='9')
		{
			sum=(sum*10)+(num-48);
			while(ColScan()==0);
		}
		else
		{
			while(ColScan()==0);
			break;
		}
	}
	return sum;
}
