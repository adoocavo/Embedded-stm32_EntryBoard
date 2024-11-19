#include <stdio.h>
#include "sfr.h"
#include "stm32f10x.h"		//for __set_PRIMASK

#define DELAY_MSEC 3
#define TICK_CNT 4

extern void fnd_display(int , int , int);
extern void fnd_init(void);
extern void exti_init(void);

volatile unsigned int gTickCount;
volatile unsigned int gTickCount2;
unsigned char start;									//flag

void MySystemTimerIsr()
{
  gTickCount = gTickCount + 1;
   
	if(start)
	{
		gTickCount2 = gTickCount2 + 1;
	}
}

void Key_init(void)
{
	//0. clock enable port-A, port-B
	rRCC_APB2ENR = rRCC_APB2ENR | (0x1 << 2);		//clk enable port-A 
	rRCC_APB2ENR = rRCC_APB2ENR | (0x1 << 3);		//clk enable port-B
	
	//1. input enable (rGPIOA->IDR : read only)
	//// PB0 : up, PB1 : down, PA2 : center, PA3 : left, PA4 : right
	//// rGPIOA->IDR[2] == 0 -> center key on
	//// rGPIOB->IDR[0] == 0 -> up key on
	rGPIOA->CRL = (rGPIOA->CRL & ~(0x4 << 8)) | (0x4 << 8);		//input enable PA2(center)
	rGPIOB->CRL = (rGPIOB->CRL & ~(0x4 << 0)) | (0x4 << 0);		//input enable PA0(up)
}


int main()
{ 
	// set sys Timer
	rSRVR = 72000 - 1;
	rSCSR = 0x7;
	
	// init regs
    fnd_init();
	Key_init();
	exti_init();
	
	unsigned int next_tick[TICK_CNT];
	next_tick[0] = gTickCount;
	next_tick[1] = next_tick[0] + DELAY_MSEC;
	next_tick[2] = next_tick[1] + DELAY_MSEC;
	next_tick[3] = next_tick[2] + DELAY_MSEC;
	
	// stop watch
	int value[TICK_CNT];
	
	while (1)
	{		
		value[0] = (gTickCount2 /10000) % 10;
		value[1] = (gTickCount2 /1000) % 10;
		value[2] = (gTickCount2 /100) % 10;
		value[3] = (gTickCount2 /10) % 10;
		
		for(int i = 0; i < TICK_CNT; ++i)
		{
            if(gTickCount > next_tick[i])
            {
                next_tick[i] = gTickCount + (DELAY_MSEC * TICK_CNT);
                if(i == 1)	fnd_display(i, value[i], 1);
                else fnd_display(i, value[i], 0);
            }
		}
	}
	
	return 0; 
}