#include <MKL25Z4.H>
#include "LEDs.h"



void init_TPM(){
	//clock to TPM and port A
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	
	//configure Ports A12 & A13 to connect to TPM1 and Ports C8 and C9 to TPM0
	PORTA->PCR[12] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[12] |= PORT_PCR_MUX(3);
	
	PORTA->PCR[13] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[13] |= PORT_PCR_MUX(3);
	
	PORTC->PCR[8] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[8] |= PORT_PCR_MUX(3);
	
	PORTC->PCR[9] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[9] |= PORT_PCR_MUX(3);
	
	//set clock source for TPM
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	
	//timer is turned off
	TPM0->SC = 0;
	TPM1->SC = 0;
	
	//set TPM0 channel 0 for rising edge input capture
	TPM1->CONTROLS[0].CnSC |= TPM_CnSC_ELSA_MASK;
	
	//set TPM0 channel 1 for falling edge input capture
	TPM1->CONTROLS[1].CnSC |= TPM_CnSC_ELSB_MASK;
	
	//set TPM0 channel 4 for high true edge alligned PWM
	TPM0->CONTROLS[4].CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	
	//set TPM0 channel 5 for high true edge alligned PWM
	TPM0->CONTROLS[5].CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	
	//allow clock to run in debug
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	TPM1->CONF |= TPM_CONF_DBGMODE(3);
	
	//set prescaler value
	TPM0->SC |= TPM_SC_PS(4);
	TPM1->SC |= TPM_SC_PS(4);
	
	//clear count register
	TPM0->CNT = 0x0000;
	TPM1->CNT = 0x0000;
	
	//Load TPM0 Mod register with maximum count
	TPM1->MOD = 0xffff;
	
	//Load TPM1 Mod register with to have a 20ms period
	TPM0->MOD = 0xEA5F;
}



void TPM0_IRQHandler(){
	control_RGB_LEDs(1, 1, 1);
	
	
}