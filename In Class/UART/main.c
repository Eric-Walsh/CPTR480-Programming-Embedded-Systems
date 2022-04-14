/* ***************************************************************************************************************
// Filename: main.c 																							   //
// Author: E.Walsh 																								   //
// Version: 3/29/22 written 																					   //
// Processor: NXP MKL25Z4 																						   //
// Compiler: Keil uVision5 																						   //
// Library: CMSIS core and device startup 																		   //
// also needs Pit_Functions.c, debug_signals.c, LEDs.c, Main_Functions.c, switches.s, gpio_defs.h, LCD_Functions.c //
// Hardware: MKL25Z128VLH4 Microcontroller connected to 4 switches,a DAC, ADC, 2 LEDS, and a 2x8 LCD  			   //
// Expected Outcome: The purpose of this software is to have the user start the PIT timer by pressing switch 1 and //
// stop the timer by pressing it again. The elapsed time would be displayed on the LCD screen. If the elapsed time //
// is greater than 1000 ms, then the LED on the kl25 lights red and stays red until the reset button (switch 2) is //
// pressed.																										   //
// Actual outcome: The switches screen functions as intended. The elapsed time is inaccurate due to incertainty to //
// the frequency of the clock.																					   //
// ****************************************************************************************************************/
#include "MKL25z4.h"
#include "UART_Functions.h"



int main(){
	init_UART2();
	int i = 0;
	while (1) {
		if(i % 5 ==0){
			UART2_Transmit(0x35);
			
		}
		if (i > 1000){
			i = 0;
		}
		i++;
	}
	
}
