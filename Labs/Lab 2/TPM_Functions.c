#include <MKL25Z4.H>


void Init_TPM(int32_t function){
	//Turn on the clock
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	
	
	if(function == 0){
		//Set clock source
		SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(2) | SIM_SOPT2_TPMSRC_MASK);
		//Mod value
		TPM0->MOD = 0xffff;
		//set channel to capture falling edge input
		TPM0->CONTROLS[0].CnSC = TPM_CnSC_ELSB_MASK | TPM_CnSC_CHIE_MASK;
		//Select pin mux to send the input signal on PTD0 to the timer
		PORTD->PCR[0] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[0] |= PORT_PCR_MUX(4);
	} else {
	}
	//Enable interrupts
	TPM0->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7) | TPM_SC_TOIE_MASK;
	NVIC_SetPriority(TPM0_IRQn, 3);
	NVIC_ClearPendingIRQ(TPM0_IRQn);
	NVIC_EnableIRQ(TPM0_IRQn);
	
}

void TPM0_IRQHandler(){
	
	
	//Reset Flags
	TPM0->STATUS |= TPM_STATUS_CH0F_MASK | TPM_STATUS_CH0F_MASK | TPM_STATUS_CH1F_MASK;
}