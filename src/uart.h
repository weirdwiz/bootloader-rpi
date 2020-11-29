#include "gpio.h"

enum
{
	UART_BASE = ((volatile unsigned int*)(MMIO_BASE+0x0020100)),

	UART_DR = ((volatile unsigned int*)(UART_BASE+0x0)),
	UART_RSRECR = ((volatile unsigned int*)(UART_BASE+0x4)),
	UART_FR = ((volatile unsigned int*)(UART_BASE+0x18)),
	UART_ILPR = ((volatile unsigned int*)(UART_BASE+0x20)),
	UART_IBRD = ((volatile unsigned int*)(UART_BASE+0x24)),
	UART_FBRD = ((volatile unsigned int*)(UART_BASE+0x28)),
	UART_LCRH = ((volatile unsigned int*)(UART_BASE+0x2c)),
	UART_CR = ((volatile unsigned int*)(UART_BASE+0x30)),
	UART_IFLS = ((volatile unsigned int*)(UART_BASE+0x34)),
	UART_IMSC = ((volatile unsigned int*)(UART_BASE+0x38)),
	UART_RIS = ((volatile unsigned int*)(UART_BASE+0x3c)),
	UART_MIS = ((volatile unsigned int*)(UART_BASE+0x40)),
	UART_ICR = ((volatile unsigned int*)(UART_BASE+0x44)),
	UART_DMACR = ((volatile unsigned int*)(UART_BASE+0x48)),
	UART_ITCR = ((volatile unsigned int*)(UART_BASE+0x80)),
	UART_ITIP = ((volatile unsigned int*)(UART_BASE+0x84)),
	UART_ITOP = ((volatile unsigned int*)(UART_BASE+0x88)),
	UART_TDR = ((volatile unsigned int*)(UART_BASE+0x8c)),
};

void uart_init();
void uart_puts();
