/* ***************************************************************************************************************
// Filename: main.c 																							   //
// Author: E.Walsh 																								   //
// Version: 4/13/22 written 																					   //
// Processor: NXP MKL25Z4 																						   //
// Compiler: Keil uVision5 																						   //
// Library: CMSIS core and device startup 																		   //
// also needs UART_Functions.h																					   //
// Hardware: MKL25Z128VLH4 Microcontroller connected to 4 switches,a DAC, ADC, 1 RGB LEDS, and a 2x8 LCD  			   //
// Expected Outcome: The UART2 channel would output the a char array data output into the UART2_Transmit function.				   //																									   //
// Actual outcome: The UART2 channel succesfully sends data.													   //
// ****************************************************************************************************************/
#include "MKL25z4.h"
#include "UART_Functions.h"



int main(){
	init_UART2();
	char data[] = "Testing UART2";
	Print_String(data);
	Print_Newline();
	while (1) {
		
	}
}
