/* ***************************************************************************************************************
// Filename: main.c 																							   //
// Author: E.Walsh 																								   //
// Version: 4/5/22 written 																					   //
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
	Init_TPM(0);
	LCD_init();
	LCD_command(0x01);
	init_RGB_LEDs();
	init_debug_signals();
	__enable_irq();
	uint32_t dist;
	control_RGB_LEDs(0,1,0);
	while (1) {
		dist = distance();
		LCD_send_data(dist);
		delayMs(1000000);
	}
	
}
