#include <MKL25Z4.H>
#include "switches.h"
#include "gpio_defs.h"
#include "LCD_Functions.h"
#include "Motor_Functions.h"
#include "LEDs.h"
#include "Test_Functions.h"

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
	if (SW1_PRESSED) {
		if(SW2_PRESSED){
			Test_Motors(1);
			//control_White_LEDs(0x3);
		}else if (SW4_PRESSED){
			Test_Motors(2);
			//control_White_LEDs(0x9);
		} else if (SW5_PRESSED){
			Test_Motors(3);
			//control_White_LEDs(0x11);
		} else if (SW2_PRESSED && SW4_PRESSED){
			Test_Motors(4);
			//control_White_LEDs(0xB);
		} else {
			Test_Motors(0);
			//control_White_LEDs(0x1);
		}
	} else if(SW2_PRESSED){
		Test_ADC();
		//control_White_LEDs(0x2);
		
	}else if(SW3_PRESSED){
		//DO NOT USE 
		
		
	}else if(SW4_PRESSED){
		Test_Mag();
		//control_White_LEDs(0x4);
		
	}else if(SW5_PRESSED){
		if (SW2_PRESSED){
			Test_UART();
			//control_White_LEDs(0x12);
		} else {
			Test_USound();
			//control_White_LEDs(0x18);
		}
		
	}
	// clear status flags 
	PORTA->ISFR = 0xffffffff;
}
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
