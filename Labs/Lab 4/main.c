/* ***************************************************************************************************************
// Filename: main.c 																							  	   //
// Author: E.Walsh 																								  	   //
// Version: 4/5/22 written 																				    	   	   //
// Processor: NXP MKL25Z4 																						   	   //
// Compiler: Keil uVision5 																							   //
// Library: CMSIS core and device startup 															    			   //
// also needs debug_signals.c, LEDs.c, Main_Functions.c, switches.s, gpio_defs.h, LCD_Functions.c, and TPM_Functions.c //
// Hardware: MKL25Z128VLH4 Microcontroller connected to 4 switches,a DAC, ADC, 2 LEDS, and a 2x8 LCD  				   //
// Expected Outcome: have a signal sent out to to a ccounter connected to PTD0. The counter returns a signal to PTD7   //
// The time between the signal being sent out and the signal recieved would then be displayed on the LCD.			   //
// Actual outcome: The signal on PTD0 is sucessfully sent out and the signal is recieved to PTD7, but the status flag  //
// is not set, so nothing gets displayed to the LCD and the system is perpetually waiting for the flag				   //
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
		    array[i-1] = distance%10;
			  distance = distance/10;
	    }
		displayString(array, 10);
	}
	
}
