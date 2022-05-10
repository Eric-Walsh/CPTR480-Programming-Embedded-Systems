/* ***************************************************************************************************************
// Filename: main.c 																							  	   //
// Author: E.Walsh 																								  	   //
// Version: 4/5/22 written 																				    	   	   //
// Processor: NXP MKL25Z4 																						   	   //
// Compiler: Keil uVision5 																							   //
// Library: CMSIS core and device startup 															    			   //
// also needs debug_signals.c, LEDs.c, Main_Functions.c, switches.s, gpio_defs.h, LCD_Functions.c, and TPM_Functions.c //
// Hardware: MKL25Z128VLH4 Microcontroller connected to 4 switches,a DAC, ADC, 2 LEDS, and a 2x8 LCD  				   //
// Expected Outcome: An ultasound device that measures distance will be connected to the board, which will use the TPM //
// to measure the distance from the ultrasound device to whatever is infront of it		        					   //
// Actual outcome: The distance signals are succesfully recieved from the ultrasound device, but the distance is	   //
// inaccurate and only works if there isn't polling.																   //
// ****************************************************************************************************************/
#include "MKL25z4.h"
#include "LCD_Functions.h"
#include "Main_Functions.h"
#include "TPM_Functions.h"
#include "USound_Functions.h"
#include "gpio_defs.h"
#include "LEDs.h"
#include <stdio.h>


void LCD_init(void);
void LCD_command(uint32_t command);
void LCD_send_data(uint32_t data);
void delayMs(uint32_t n);





int main(){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK;
	LCD_init();
	LCD_command(0x01);
	init_RGB_LEDs();
	control_RGB_LEDs(0,1,0);
	init_dist_TPM0();
	init_ultrasound();
	uint32_t array[5];
	uint32_t distance;
	while (1) {
		
		distance = measure_distance();
		for (int i=4; i>0; i--) {
		    array[i-1] = distance%10 + 48;
			  distance = distance/10;
	    }
		
		LCD_command(clear_screen);
		displayString(array, 5);
	}
	
}
