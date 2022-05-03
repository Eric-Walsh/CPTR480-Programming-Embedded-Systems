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
	//set clock to portD
	//SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	//set mux to ports
	PORTD->PCR[7] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[7] |= PORT_PCR_MUX(1);
	
	PORTD->PCR[2] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[2] |= PORT_PCR_MUX(1);
	
	//make ports gpio
	PTD->PDDR |= MASK(7);
	PTD->PDDR |= MASK(2);
	
	//turn on ptd2 for vdd
	PTD->PSOR = MASK(2);
}

uint32_t measure_distance(){
	uint32_t rawDist = 1;
	uint32_t mmDist = 0;
	
	//Turn on port D bit 7
	PTD->PSOR = MASK(7);
	
	//clear count register
	TPM0->CNT = 0x0000;
	
	
	TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK;
	TPM0->CONTROLS[1].CnSC |= TPM_CnSC_CHF_MASK;
	
	//turn on counter
	TPM0->SC |= TPM_SC_CMOD(1);
	
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
	TPM0->SC |= TPM_SC_CMOD(0);
	
	//get raw data
	rawDist = (TPM0->CONTROLS[1].CnV) - (TPM0->CONTROLS[0].CnV);
	
	//convert to milimeters
	mmDist = rawDist/9;
	
	return mmDist;
}