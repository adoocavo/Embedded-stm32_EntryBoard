#ifndef __UART_H__
#define __UART_H__

#include <stdio.h>

#define SYS_CLOCK 			(72000000)
#define rRCC_APB2ENR 		(*(volatile int *)0x40021018)
#define rGPIOA_CRH 			(*(volatile int *)0x40010804)
#define rUSART1_SR 			(*(volatile int *)0x40013800)
#define rUSART1_DR 			(*(volatile int *)0x40013804)
#define rUSART1_BRR 		(*(volatile int *)0x40013808)
#define rUSART1_CR1 		(*(volatile int *)0x4001380C)
	
void uart_sendbyte(unsigned char c);
unsigned char uart_readbyte(void);
int uart_peekbyte(void);
void uart_rx_isr(void);
void uart_rx_intr_init(void);
int fputc(int, FILE *);

#endif
