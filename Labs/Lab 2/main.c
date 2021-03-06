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
#include "gpio_defs.h"
#include "LEDs.h"
#include <stdio.h>


void LCD_init(void);
void LCD_command(uint32_t command);
void LCD_send_data(uint32_t data);
void delayMs(uint32_t n);

void delayMicros(uint32_t n)
{
uint32_t i;
uint32_t j;
for(i=0; i < n; i++)
		for(j=0; j < 8; j++) {
		control_RGB_LEDs(0, 0, 1);
		} //Counting to 11 in a 10.5MHz clock to get one microsecond
}

uint32_t distance(){
	//initialization
	//SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	//Reset Flags
	TPM0->CNT = 0;
	TPM0->STATUS |=  TPM_STATUS_CH0F_MASK;
	//delayMs(100);
	TPM0->SC |= TPM_SC_CMOD(1);
	
	PTD->PTOR = MASK(7);
	delayMicros(100);
	control_RGB_LEDs(0, 0, 0);
	PTD->PTOR = MASK(7);
	int poll = 1;
	 while(poll > 0){
		if(TPM0->STATUS & TPM_STATUS_CH0F_MASK){
			poll = 0;
			control_RGB_LEDs(0, 1, 0);
		} else {
			poll = 1;
			control_RGB_LEDs(1, 0, 0);
		}
	}
	
	
	return TPM0->CONTROLS[0].CnV;
}


int main(){
		// Enable clock to Ports D, E, B, and C
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK;
	int func = 0;
	LCD_init();
	LCD_command(0x01);
	init_RGB_LEDs();
	//init_debug_signals();
	Init_TPM(func);
	__enable_irq();
	uint32_t dist = 0x00;
	control_RGB_LEDs(0,1,0);
	PORTD->PCR[7] &= ~PORT_PCR_MUX(7);
	PORTD->PCR[7] |= PORT_PCR_MUX(1);
	PTD->PDDR |= MASK(7);
	PORTD->PCR[6] &= ~PORT_PCR_MUX(7);
	PORTD->PCR[6] |= PORT_PCR_MUX(1);
	PTD->PDDR |= MASK(6);
	while (1) {
		if(func == 0){
			PTD->PSOR = MASK(6);
			PTD->PSOR = MASK(7);
			dist = distance();
			LCD_command(0x01);
			LCD_send_data(dist);
			PTD->PCOR = MASK(6);
			delayMs(10000);
		} else {
			for(int i = 0; i < 48000; i++){
				TPM0->CONTROLS[5].CnV = i;
				delayMicros(100);  
			}
		}
		
		
	}
	
}
