/* ***************************************************************************************************************
// Filename: main.c 																							   //
// Author: E.Walsh 																								   //
// Version: 4/13/22 written 																					   //
// Processor: NXP MKL25Z4 																						   //
// Compiler: Keil uVision5 																						   //
// Library: CMSIS core and device startup 																		   //
// also needs UART_Functions.h																					   //
// Hardware: MKL25Z128VLH4 Microcontroller connected to 4 switches,a DAC, ADC, 2 LEDS, and a 2x8 LCD  			   //
// Expected Outcome: The UART2 channel would output the data put into the UART2_Transmit function.				   //																									   //
// Actual outcome: The UART2 channel succesfully sends data.													   //
// ****************************************************************************************************************/
#include "MKL25z4.h"
#include "UART_Functions.h"

void delayMs(uint32_t n)
{
uint32_t i;
uint32_t j;
for(i=0; i < n; i++)
		for(j=0; j < 3500; j++) {}
}

int main(){
	init_UART2();
	while (1) {
		UART2_Transmit(0x35);
		while(!(UART2_S1 & 0x80)){}
		delayMs(2);
	}
		
	
}
