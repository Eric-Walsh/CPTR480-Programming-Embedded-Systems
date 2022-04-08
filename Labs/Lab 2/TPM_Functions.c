#include <MKL25Z4.H>
#include "LEDs.h"

void Init_TPM(int32_t function){
	//Turn on the clock
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	
	
	if(function == 0){
		//Set clock source
		SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(2) | SIM_SOPT2_PLLFLLSEL_MASK);
		//Mod value
		TPM0->MOD = 0xf424;
		//set channel to capture falling edge input
		TPM0->CONTROLS[0].CnSC = TPM_CnSC_ELSB_MASK | TPM_CnSC_CHIE_MASK;
		//Select pin mux to send the input signal on PTD0 to the timer
		PORTD->PCR[0] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[0] |= PORT_PCR_MUX(4);
		//Enable interrupts
		TPM0->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7) | TPM_SC_TOIE_MASK;
		NVIC_SetPriority(TPM0_IRQn, 3);
		NVIC_ClearPendingIRQ(TPM0_IRQn);
		NVIC_EnableIRQ(TPM0_IRQn);
	} else {
		PORTD->PCR[5] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[5] |= PORT_PCR_MUX(4);
		SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
		TPM0->MOD = 47999;
		TPM0->SC = TPM_SC_PS(1);
		TPM0->CONF |= TPM_CONF_DBGMODE(3);
		TPM0->CONTROLS[5].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
		TPM0->CONTROLS[5].CnV = 0;
		TPM0->SC = TPM_SC_CMOD(1);
	}
	
	
}

void TPM0_IRQHandler(){
	control_RGB_LEDs(1, 1, 1);
	
	
}