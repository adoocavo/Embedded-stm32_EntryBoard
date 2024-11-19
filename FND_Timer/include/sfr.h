#ifndef	__SFR_H__
#define __SFR_H__

// clock enable
#define rRCC_APB2ENR		(*(volatile int *)0x40021018)

// GPIO reg
typedef struct 
{
	volatile int CRL;
	volatile int CRH;
	volatile int IDR;
	volatile int ODR;
}	sfr_gpio_t;

#define rGPIOA 	((sfr_gpio_t*)0x40010800)
#define rGPIOB 	((sfr_gpio_t*)0x40010C00)
#define rGPIOC 	((sfr_gpio_t*)0x40011000)

// sysTimer reg
#define rSCSR						(*(volatile int *)0xE000E010)	
#define rSRVR						(*(volatile int *)0xE000E014)	
#define rSCVR						(*(volatile int *)0xE000E018)	

// EXTI reg
#define rAFIO_EXTICR1 (*(volatile int *)0x40010008)
#define rAFIO_EXTICR2 (*(volatile int *)0x4001000C)

#define rEXTI_IMR (*(volatile int *)0x40010400)
#define rEXTI_FTSR (*(volatile int *)0x4001040C)
#define rEXTI_SWIER (*(volatile int *)0x40010410)
#define rEXTI_PR (*(volatile int *)0x40010414)


#endif