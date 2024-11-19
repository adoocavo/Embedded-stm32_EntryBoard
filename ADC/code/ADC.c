#include "sfr.h"
#include "ADC.h"

void ADC_init(void)
{
	rRCC_APB2ENR = rRCC_APB2ENR | (0x1 << 9) | (0x1 << 2);
	
	rGPIOA->CRL = rGPIOA->CRL & ~(0xF << 4);
	
	rADC1_SQ3 = (rADC1_SQ3 & ~(0x1F << 0)) | (0x1 << 0);
	
	rADC1_CR2 = rADC1_CR2 | (0x7 << 17) | (0x3 << 0);
	rADC1_CR2 = rADC1_CR2 & ~(0x1 << 22);
	
}



unsigned int ADC_get_value(void)
{
	return rADC1_DR;
}