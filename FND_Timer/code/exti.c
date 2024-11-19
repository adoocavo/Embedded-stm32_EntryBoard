#include<stdio.h>
#include "sfr.h"

extern unsigned char start;
extern unsigned int gTickCount2;

//1. define ISR -> enroll at vec table 
// up key
void exti_0_isr()										// irq6
{
	rEXTI_PR = (0x1 << 0);								//pending clear
	
	start = start ^ 1;										
}

// center key
void exti_2_isr()										// irq8
{
	rEXTI_PR = (0x1 << 2);								//pending clear
	
	gTickCount2 = 0;
}


//2. 
void exti_init()
{
	////2-1. clock enable AFIO, Port A, Port B
	rRCC_APB2ENR = rRCC_APB2ENR | (0x1 << 3) | (0x1 << 2) | (0x1 << 0);

	////2-2. interrupt set enable : enable irq6 ... irq10
	////// PB0(up) == EXTI0 == irq6
	////// PA2(center) == EXTI2 == irq8
	////// 0xE000E100 == SETENA(Interrupt set-enable reg)
	*(int*)0xE000E100 = (0x1 << 8) | (0x1 << 6);
	
	
	//////////////================== ??? only for 0, 2?
	
	////2-3. config MUX 
	//// PB0 ==> EXTI0 ==> rAFIO_EXTICR1[3:0] : 0001
	//// PA2 ==> EXTI2 ==> rAFIO_EXTICR1[11:8] : 0001
	//// => AFIO_EXTICR1 : 
	rAFIO_EXTICR1 = 0x0001;																//atomic

	
	////2-4. falling edge trigger
	rEXTI_FTSR = rEXTI_FTSR | (0x1F << 0);
	
	////2-5. enable EXTI-0 ... EXTI-4
	rEXTI_IMR = rEXTI_IMR | (0x1F << 0);
	
	//////////////================== ???

	return;
}
