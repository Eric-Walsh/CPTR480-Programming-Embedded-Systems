#include <MKL25Z4.H>
#include "gpio_defs.h"
#include "LEDS.h"

void delayMicros(uint32_t n)
{
uint32_t i;
uint32_t j;
for(i=0; i < n; i++)
		for(j=0; j < 11; j++) {
		control_RGB_LEDs(0, 0, 1);
		} //using clock setup 1
}

void init_ultrasound(){
	//set clock to portA
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	//set mux to ports
	PORTA->PCR[17] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[17] |= PORT_PCR_MUX(1);
	
	
	//make ports gpio
	PTA->PDDR |= MASK(17);
	
}

uint32_t measure_distance(){
	uint32_t rawDist = 1;
	uint32_t mmDist = 0;
	
	//Turn on port D bit 7
	PTA->PSOR = MASK(17);
	
	//clear count register
	TPM1->CNT = 0x0000;
	
	
	TPM1->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK;
	TPM1->CONTROLS[1].CnSC |= TPM_CnSC_CHF_MASK;
	
	//turn on counter
	TPM1->SC |= TPM_SC_CMOD(1);
	
	//delay for 10 microseconds
	for(int i = 0; i < 116; i++);
	//delayMicros(5);
	
	//clear ptd7
	PTD->PCOR = MASK(7);
	
	//delayMicros(20);
	
	//poll chf flag of tpm0
 	//while(!(TPM0->CONTROLS[0].CnSC & TPM_CnSC_CHF_MASK));
	//while(!(TPM0->CONTROLS[1].CnSC & TPM_CnSC_CHF_MASK));
	
	//turn off counter
	TPM1->SC |= TPM_SC_CMOD(0);
	
	//get raw data
	rawDist = (TPM1->CONTROLS[1].CnV) - (TPM1->CONTROLS[0].CnV);
	
	//convert to milimeters
	mmDist = rawDist/9;
	
	return mmDist;
}