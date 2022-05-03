/* ***************************************************************************************************************
// Filename: main.c 																							   //
// Author: E.Walsh 																								   //
// Version: 4/13/22 written 																					   //
// Processor: NXP MKL25Z4 																						   //
// Compiler: Keil uVision5 																						   //
// Library: CMSIS core and device startup 																		   //
// also needs UART_Functions.h																					   //
// Hardware: MKL25Z128VLH4 Microcontroller connected to 4 switches,a DAC, ADC, 1 RGB LEDS, and a 2x8 LCD  		   //
// Expected Outcome: The scan_ADC funtion would scan 9 ADC channels and put the values into an array. The values in//
// the array would then be output to the UART2 transmitter for debugging.	   									   //
// Actual outcome: The scan function successfully scans the channels, however the UART2 is transmitting errors.    //
// ****************************************************************************************************************/
#include "MKL25z4.h"
#include "UART_Functions.h"
#include "Queue_Functions.h"
#include "gpio_defs.h"

int main(){
	Q_T que;
	Q_Init(&que);
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	init_UART2();
	uint32_t data[] = {'T','e','s','t','i','n','g',' ','U','A','R','T','2'};
	//Print_String(data);
	print_base10(2020, 4);
	Print_Newline();
	Q_UART2_Transmit(data);
	while (1) {
		
	}
}
