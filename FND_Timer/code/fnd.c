#include "sfr.h"

void fnd_display(int pos, int value, int dot)
{
	//0-1. all transister off
	rGPIOB -> ODR = rGPIOB -> ODR & ~(0xF << 12);		//pb12-15 off
	
	//0-2. all led off
	rGPIOC -> ODR = rGPIOC -> ODR & ~(0xFF << 0);		//pc0-7 off
	
	
	//1. transister on
	// set pos 
	//// pb12 - 15 : 0-3
	switch(pos)
	{
		//// pos 0 == DIG1 == pb12
		case 0 :
			rGPIOB->ODR = rGPIOB->ODR | (0x1 <<12);
			break;
		
		//// pos 1 == DIG2 == pb13
		case 1 :
			rGPIOB->ODR = rGPIOB->ODR | (0x1 <<13);
			break;
		
		//// pos 2 == DIG3 == pb14
		case 2 :
			rGPIOB->ODR = rGPIOB->ODR | (0x1 <<14);
			break;
		
		//// pos 3 == DIG4 == pb15
		case 3 :
			rGPIOB->ODR = rGPIOB->ODR | (0x1 <<15);
			break;
		
		default : 
			break;
	}
	
	//2. LED on
	// set value
	//// LED election : D0-D7 == pC0-PC7
	switch(value)
	{
		//// pC0-PC6 on
		case 0 :
			rGPIOC -> ODR = rGPIOC -> ODR | (0x1<<5)	\
                                        | (0x1<<4)	\
                                        | (0x1<<3)	\
                                        | (0x1<<2)	\
                                        | (0x1<<1)	\
                                        | (0x1<<0);
			break;
		
		// pc1,2 on
		case 1 :
			rGPIOC->ODR = rGPIOC->ODR | (0x1<<2) | (0x1<<1);
			break;
		
		//pc2, 5 off 
		case 2 :
			rGPIOC -> ODR = rGPIOC -> ODR | (0x1<<6)	\
                                        | (0x1<<4)	\
                                        | (0x1<<3)	\
                                        | (0x1<<1)	\
                                        | (0x1<<0);
			break;
		
		//pc5, 4 off 
		case 3 :
			rGPIOC -> ODR = rGPIOC -> ODR | (0x1<<6)	\
                                        | (0x1<<3)	\
                                        | (0x1<<2)	\
                                        | (0x1<<1)	\
                                        | (0x1<<0);
			break;
		
		//pc0, 3, 4 off 
		case 4 :
			rGPIOC -> ODR = rGPIOC -> ODR | (0x1<<6)	\
                                        | (0x1<<5)	\
                                        | (0x1<<2)	\
                                        | (0x1<<1);	
			break;
		
		//pc1, 4 off 
		case 5 :
			rGPIOC -> ODR = rGPIOC -> ODR | (0x1<<6)	\
                                        | (0x1<<5)	\
                                        | (0x1<<3)	\
                                        | (0x1<<2)	\
                                        | (0x1<<0);
		
			break;
		
		//pc1 off 
		case 6 :
			rGPIOC -> ODR = rGPIOC -> ODR | (0x1<<6)	\
                                        | (0x1<<5)	\
                                        | (0x1<<4)	\
                                        | (0x1<<3)	\
                                        | (0x1<<2)	\
                                        | (0x1<<0);
			break;
		
		//pc6, 3, 4 off 
		case 7 :
			rGPIOC -> ODR = rGPIOC -> ODR | (0x1<<5)	\
                                        | (0x1<<2)	\
                                        | (0x1<<1)	\
                                        | (0x1<<0);
			break;
		
		// all on
		case 8 :
			rGPIOC -> ODR = rGPIOC -> ODR | (0x1<<6)	\
                                        | (0x1<<5)	\
                                        | (0x1<<4)	\
                                        | (0x1<<3)	\
                                        | (0x1<<2)	\
                                        | (0x1<<1)	\
                                        | (0x1<<0);
			break;
		
		//pc3, 4 off 
		case 9 :			
			rGPIOC -> ODR = rGPIOC -> ODR | (0x1<<6)	\
                                        | (0x1<<5)	\
                                        | (0x1<<2)	\
                                        | (0x1<<1)	\
                                        | (0x1<<0);
			break;

		default : 
			break;
	}
	
	//+) dot(. == pc7) on
	if(dot == 1)
	{
		rGPIOC -> ODR = rGPIOC -> ODR | (0x1 << 7);			//set 1 -> on
	}
	else 
	{
		rGPIOC -> ODR = rGPIOC -> ODR & ~(0x1 << 7);			//set 0 -> off
	}
}




void fnd_init()
{
	//1. clk enable Port-B, Port-C
	rRCC_APB2ENR = rRCC_APB2ENR | (0x1 << 3);		//clk enable port-B
	rRCC_APB2ENR = rRCC_APB2ENR | (0x1 << 4);		//clk enable port-C
	
	//2. output : PC0-PC7(led), PB12-PB15(Tr.) 0011
	//// set CNF#,MODE# 0x0011
	rGPIOC->CRL = ((rGPIOC->CRL & ~(0xF << 0)) | (0x3 << 0));				//set PC0 pin output
	rGPIOC->CRL = ((rGPIOC->CRL & ~(0xF << 4)) | (0x3 << 4));				//set PC1 pin output
	rGPIOC->CRL = ((rGPIOC->CRL & ~(0xF << 8)) | (0x3 << 8));				//set PC2 pin output
	rGPIOC->CRL = ((rGPIOC->CRL & ~(0xF << 12)) | (0x3 << 12));			//set PC3 pin output
	rGPIOC->CRL = ((rGPIOC->CRL & ~(0xF << 16)) | (0x3 << 16));			//set PC4 pin output
	rGPIOC->CRL = ((rGPIOC->CRL & ~(0xF << 20)) | (0x3 << 20));			//set PC5 pin output
	rGPIOC->CRL = ((rGPIOC->CRL & ~(0xF << 24)) | (0x3 << 24));			//set PC6 pin output
	rGPIOC->CRL = ((rGPIOC->CRL & ~(0xF << 28)) | (0x3 << 28));			//set PC7 pin output
	
	//// set CNF#,MODE# 0x0011
	rGPIOB->CRH = ((rGPIOB->CRH & ~(0xF << 16)) | (0x3 << 16));			//set PB12 pin output
	rGPIOB->CRH = ((rGPIOB->CRH & ~(0xF << 20)) | (0x3 << 20));			//set PB13 pin output
	rGPIOB->CRH = ((rGPIOB->CRH & ~(0xF << 24)) | (0x3 << 24));			//set PB14 pin output
	rGPIOB->CRH = ((rGPIOB->CRH & ~(0xF << 28)) | (0x3 << 28));			//set PB15 pin output
	
	return;
	
}