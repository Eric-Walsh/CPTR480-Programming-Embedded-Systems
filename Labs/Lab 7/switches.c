#include <MKL25Z4.H>
#include "switches.h"
#include "gpio_defs.h"
#include "LCD_Functions.h"
#include "Motor_Functions.h"
#include "LEDs.h"

uint32_t doublePress;

void init_switch(void) {
	SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK; /* enable clock for port A */

	/* Select GPIO and enable pull-up resistors and interrupts 
		on falling edges for pins connected to switches */
	PORTA->PCR[SW1_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	PORTA->PCR[SW2_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	PORTA->PCR[SW3_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	PORTA->PCR[SW4_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	PORTA->PCR[SW5_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	
	/* Set port A switch bit to inputs */
	PTA->PDDR &= ~MASK(SW1_POS);
	PTA->PDDR &= ~MASK(SW2_POS);
	PTA->PDDR &= ~MASK(SW3_POS);
	PTA->PDDR &= ~MASK(SW4_POS);
	PTA->PDDR &= ~MASK(SW5_POS);

	/* Enable Interrupts */
	NVIC_SetPriority(PORTA_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTA_IRQn); 
	NVIC_EnableIRQ(PORTA_IRQn);
	
	
}

void PORTA_IRQHandler(void) {  
	// clear pending interrupts
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	delayMs(100);
	if ((PORTA->ISFR & MASK(SW1_POS))) {
		go_Forward();
	} else if((PORTA->ISFR & MASK(SW2_POS))){
		turn_Left();
		
	}else if((PORTA->ISFR & MASK(SW3_POS))){
		//DO NOT USE 
		
		
	}else if((PORTA->ISFR & MASK(SW4_POS))){
		stop();
		
	}else if((PORTA->ISFR & MASK(SW5_POS))){
		turn_Right();
		
	}
	// clear status flags 
	PORTA->ISFR = 0xffffffff;
}
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
