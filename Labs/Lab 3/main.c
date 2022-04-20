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
#include "ADC_Functions.h"
#define MASK(x) (1UL << (x))


int main(){
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[0] &= ~PORT_PCR_MUX_MASK;
  PORTD->PCR[0] |= PORT_PCR_MUX(1);
	PTD->PDDR|= MASK(0);
	PTD->PTOR = MASK(0);
	init_UART2();
	Init_ADC();
	char data[] = "Testing UART2";
	uint32_t ADC_data[4] = {1,1,1,1};
	Print_String(data);
	Print_Newline();
	while (1) {
		scan_ADC(ADC_data);
	}
}
