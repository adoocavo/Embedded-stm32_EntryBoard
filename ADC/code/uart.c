#include "uart.h"	
#include "sfr.h"
#include <stdio.h>


int fputc(int c, FILE *fp)
{
   uart_sendbyte(c);
   return c;
}

// send to TerraTerm 
void uart_sendbyte(unsigned char c)
{
	while ((rUSART1_SR & (0x1<<7))==0);
	rUSART1_DR = c;
}


// input 1 char by keyboard -> call uart_rx_isr()
///
void uart_rx_isr(void)
{
	printf("received data : %c \r\n", rUSART1_DR);
}

void uart_rx_intr_init(void)
{
	//1. enable clk for UART1, port-A
	rRCC_APB2ENR = rRCC_APB2ENR | (0x1<<14);			//set rRCC_APB2ENR[14] 1
	rRCC_APB2ENR = rRCC_APB2ENR | (0x1 << 2);		//clk enable port-A 
	
	//2. set pin : PA9, PA10
	//// UART1_TX == PA9 => CNF9[1:0] : 0x2(10), MODE9[1:0] : 0x3(11)
	rGPIOA->CRH = (rGPIOA->CRH & ~(0xF << 4)) | (0xB << 4);
	//// UART1_RX == PA10 => CNF10[1:0] : 0x1(01), MODE10[1:0] : 0x0(00)
	rGPIOA->CRH = (rGPIOA->CRH & ~(0xF << 8)) | (0x4 << 8);
	
	//3. set Baudrate : USART_BRR
	rUSART1_BRR = SYS_CLOCK / 115200;
	
	//4. enable  trans(TE), recv(RE), USART(UE), interrupt to NVIC(RXNEIE)
	rUSART1_CR1 = rUSART1_CR1 | (0x1<<13) | (0x1<<3) | (0x1<<2) | (0x1<<5);
		
	//5. interrupt set enable : enable irq37
	//// enroll interrupt vector table(Interrupt Set-Enable Register)
	//// interrupt from USART -> core
	*(int*)0xE000E104 = (0x1 << 5);
	
}
