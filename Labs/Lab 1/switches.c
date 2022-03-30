#include <MKL25Z4.H>
#include "switches.h"
#include "PIT_Functions.h"
#include "gpio_defs.h"
#include "LCD_Functions.h"
#include "Main_Functions.h"
#include "LEDs.h"

uint32_t doublePress;

void init_switch(void) {
	SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK; /* enable clock for port A */

	/* Select GPIO and enable pull-up resistors and interrupts 
		on falling edges for pins connected to switches */
	PORTA->PCR[SW1_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	PORTA->PCR[SW2_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	
	/* Set port A switch bit to inputs */
	PTA->PDDR &= ~MASK(SW1_POS);
	PTA->PDDR &= ~MASK(SW2_POS);

	/* Enable Interrupts */
	NVIC_SetPriority(PORTA_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTA_IRQn); 
	NVIC_EnableIRQ(PORTA_IRQn);
	
	doublePress = 0;
}

void PORTA_IRQHandler(void) {  
	DEBUG_PORT->PSOR = MASK(DBG_ISR_POS);
	// clear pending interrupts
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	delayMs(100);
	if ((PORTA->ISFR & MASK(SW1_POS))) {
		if(doublePress == 0){
			Start_PIT();
			doublePress = 1;
		} else if (doublePress != 0) {
			Stop_PIT();
			doublePress = 0;
		}
	} else if((PORTA->ISFR & MASK(SW2_POS))){
		delayMs(10);
		doublePress = 0;
		control_RGB_LEDs(0,1,0);
		countToClock(0);
	}
	// clear status flags 
	PORTA->ISFR = 0xffffffff;
	DEBUG_PORT->PCOR = MASK(DBG_ISR_POS);
}
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
