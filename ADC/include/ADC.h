#ifndef __ADC_H__
#define __ADC_H__

// ADC reg
#define rADC1_SQ3 (*(volatile int *)0x40012434)
#define rADC1_CR2 (*(volatile int *)0x40012408)
#define rADC1_DR (*(volatile int *)0x4001244C)

// funcs
void ADC_init(void);
unsigned int ADC_get_value(void);

#endif