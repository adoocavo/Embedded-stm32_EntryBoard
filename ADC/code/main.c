#include <stdio.h>
#include "sfr.h"
#include "uart.h"
#include "ADC.h" 

volatile unsigned int gTickCount;

void MyDelay(unsigned int msec)
{   
   unsigned int next_tick = gTickCount + msec;
   
   while(gTickCount < next_tick);
}

void MySystemTimerIsr(void)
{
   gTickCount = gTickCount + 1;
}


int main(void)
{ 
	// set sys Timer
	rSRVR = 72000 - 1;
	rSCSR = 0x7;
	
	// set ADC
	ADC_init();
	uart_rx_intr_init();
	
	// ==== ADC ==== 
	printf("ADC \r\n");
	
	int count = 0;
	int adc_value = ADC_get_value();
	float pred_value = (float)adc_value;
	
	while(1)
	{
		pred_value = 0.9 * pred_value + 0.1 * ADC_get_value();
		count = (count + 1) % 10;
		MyDelay(10);
		
		if((count % 10) == 0)
		{
			printf("===================\r\n");
			printf("ADC value : %d \r\n", (int)(pred_value + 0.5f));
			printf("===================\r\n");
		}
	}
	// ==== ADC ==== 

	
}