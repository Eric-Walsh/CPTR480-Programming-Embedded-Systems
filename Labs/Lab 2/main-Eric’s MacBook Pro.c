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
#include "gpio_defs.h"
#include "LCD_Functions.h"
#include "Main_Functions.h"
#include "TPM_Functions.h"
#include "LEDs.h"
#include <stdio.h>

extern volatile unsigned switch_pressed;
extern void init_debug_signals(void);


void LCD_init(void);
void LCD_command(uint32_t command);
void LCD_send_data(uint32_t data);
void delayMs(uint32_t n);

uint32_t distance(){
	//initialization
	//SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	TPM0->CNT = 0;
	//Reset Flags
	TPM0->STATUS |=  TPM_STATUS_CH0F_MASK | TPM_STATUS_CH1F_MASK;
	
	PORTD->PCR[7] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[7] |= PORT_PCR_MUX(1);
	PTD->PDDR |= MASK(7);
	
	PTD->PSOR = MASK(7);
	delayMs(100);
	control_RGB_LEDs(0, 0, 0);
	PTD->PCOR = MASK(7);
	int poll = 1;
	do {
		if(TPM0->STATUS & TPM_STATUS_CH0F_MASK){
			poll = 0;
			control_RGB_LEDs(0, 1, 0);
		} else {
			poll = 1;
			control_RGB_LEDs(1, 0, 0);
		}
	} while(poll > 0);
	
	return TPM0_C0V;
}


int main(){
		// Enable clock to Ports B and C
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	int func = 1;
	Init_TPM(func);
	LCD_init();
	LCD_command(0x01);
	init_RGB_LEDs();
	init_debug_signals();
	__enable_irq();
	uint32_t dist;
	control_RGB_LEDs(0,1,0);
	while (1) {
		if(func ==0){
			dist = distance();
			LCD_send_data(dist);
			delayMs(1000000);
		} else {
			for(int i = 0; i < 48000; i++){
				TPM0->CONTROLS[5].CnV = i;
				delayMs(100);
			}
		}
		
		
	}
	
}
