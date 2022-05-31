#include <MKL25Z4.H>
#include "LEDs.h"
#include "gpio_defs.h"

void init_LEDs(void) {
	// Enable clock to ports B and D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
	
	// Make 3 pins GPIO
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1);          
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1);          
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(1); 
	PORTB->PCR[D1_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[D1_POS] |= PORT_PCR_MUX(1);          
	PORTB->PCR[D2_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[D2_POS] |= PORT_PCR_MUX(1);	
	PORTB->PCR[D3_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[D3_POS] |= PORT_PCR_MUX(1);          
	PORTB->PCR[D4_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[D4_POS] |= PORT_PCR_MUX(1);
	
	// Set ports to outputs
	PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
	PTD->PDDR |= MASK(BLUE_LED_POS);
	
	control_RGB_LEDs(1, 1, 1);
	control_RGB_LEDs(0, 0, 0);
}

void control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on) {
	if (red_on) {
			PTB->PCOR = MASK(RED_LED_POS);
	} else {
			PTB->PSOR = MASK(RED_LED_POS); 
	}
	if (green_on) {
			PTB->PCOR = MASK(GREEN_LED_POS);
	}	else {
			PTB->PSOR = MASK(GREEN_LED_POS); 
	} 
	if (blue_on) {
			PTD->PCOR = MASK(BLUE_LED_POS);
	}	else {
			PTD->PSOR = MASK(BLUE_LED_POS); 
	}
}	

void toggle_RGB_LEDs(unsigned int red_tog, unsigned int green_tog, unsigned int blue_tog) {
	if (red_tog) {
			PTB->PTOR = MASK(RED_LED_POS);
	} 
	if (green_tog) {
			PTB->PTOR = MASK(GREEN_LED_POS);
	} 
	if (blue_tog) {
			PTD->PTOR = MASK(BLUE_LED_POS);
	}	
}	
// *******************************ARM University Program Copyright � ARM Ltd 2013*************************************   
