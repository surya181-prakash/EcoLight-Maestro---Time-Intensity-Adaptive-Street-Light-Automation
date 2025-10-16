				   #include <LPC21xx.h>

#include "delay.h"

#include "pin_connect_block.h"

#include "adc_defines.h"


void Init_ADC(void)

{

	//cfg p0.27 as ain0 input pin

//	CfgPortPinFunc(0,28,1);
PINSEL1|=0x15400000;

	//cfg ADCR

	ADCR=(CLKDIV<<CLKDIV_BITS)|

	      (1<<PDN_BIT);

}


void Read_ADC(unsigned int chNo,

	            unsigned int *adcDVal,

							float *eAR)

{

	//Mask any prev channel sel

	ADCR&=0xFFFFFF00;

	//write channel for analog read,

	//& start adc conversion wrt that channel

	ADCR|=(1<<chNo)|(1<<ADC_CONV_START_BIT);

	delay_us(3);

	//wait until conversion completion status

	while(((ADDR>>DONE_BIT)&1)==0);

	//stop  adc convert wrt that channel

	ADCR&=~(1<<ADC_CONV_START_BIT);

	//read digital data

	*adcDVal=((ADDR>>DIGITAL_DATA_BITS)&1023);

	//equivalent analog represention bt/w

	//0 to 3.3v

	*eAR=(*adcDVal * (3.3/1023));

}