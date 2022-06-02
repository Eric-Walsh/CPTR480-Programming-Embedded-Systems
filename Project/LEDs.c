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
	PORTE->PCR[D5_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTE->PCR[D5_POS] |= PORT_PCR_MUX(1);
	PORTE->PCR[D6_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTE->PCR[D6_POS] |= PORT_PCR_MUX(1);
	PORTE->PCR[D7_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTE->PCR[D7_POS] |= PORT_PCR_MUX(1);
	PORTE->PCR[D8_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTE->PCR[D8_POS] |= PORT_PCR_MUX(1);
	
	
	// Set ports to outputs
	PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS) | MASK(D1_POS) | MASK(D2_POS)| MASK(D3_POS) | MASK(D4_POS);
	PTE->PDDR |= MASK(D5_POS) | MASK(D6_POS) | MASK(D7_POS) | MASK(D8_POS);
	PTD->PDDR |= MASK(BLUE_LED_POS);
	
	control_RGB_LEDs(1, 1, 1);
	control_RGB_LEDs(0, 0, 0);
	
	for(int i = 0; i <= 0x80; i++){
		control_White_LEDs(i);
	}
	control_White_LEDs(0);
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

void control_White_LEDs(uint32_t LED){
	if(LED & 0x1){
		PTB->PSOR = MASK(D1_POS);
	} else {
		PTB->PCOR = MASK(D1_POS);
	}
	if(LED & 0x2){
		PTB->PSOR = MASK(D2_POS);
	} else {
		PTB->PCOR = MASK(D2_POS);
	}
	if(LED & 0x4){
		PTB->PSOR = MASK(D3_POS);
	} else {
		PTB->PCOR = MASK(D3_POS);
	}
	if(LED & 0x8){
		PTB->PSOR = MASK(D4_POS);
	} else {
		PTB->PCOR = MASK(D4_POS);
	}
	if(LED & 0x10){
		PTE->PSOR = MASK(D5_POS);
	} else {
		PTE->PCOR = MASK(D5_POS);
	}
	if(LED & 0x20){
		PTE->PSOR = MASK(D6_POS);
	} else {
		PTE->PCOR = MASK(D6_POS);
	}
	if(LED & 0x40){
		PTE->PSOR = MASK(D7_POS);
	} else {
		PTE->PCOR = MASK(D7_POS);
	}
	if(LED & 0x80){
		PTE->PSOR = MASK(D8_POS);
	} else {
		PTE->PCOR = MASK(D8_POS);
	}
}
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
