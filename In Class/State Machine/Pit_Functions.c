#include "MKL25Z4.h"
#include "Main_Functions.h"
#include "LEDs.h"

volatile unsigned PIT_interrupt_counter = 0;
volatile unsigned LCD_update_requested = 0;
volatile unsigned int count;

void Init_PIT(unsigned period) {
		//ENable clock to PIT module
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	
		//Enable module, freeze timers in debug mode
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	PIT->MCR |= PIT_MCR_FRZ_MASK;
	
		//Initialize PIT0 to count down from argument
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(period);
	
		//No chaining
	PIT->CHANNEL[0].TCTRL &= PIT_TCTRL_CHN_MASK;
	
		//Generate Interrupts
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
	
		/* Enaable INterrupts */
	NVIC_SetPriority(PIT_IRQn, 128); //0,64,128 or 192
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_EnableIRQ(PIT_IRQn);
}


void Start_PIT(void) {
	//count = 0;
		//Enable counter
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
	return;
}

void Stop_PIT(void){
		//Disable Counter
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
	//countToClock(count);
	return;
}

void PIT_IRQHandler(void) {
		//clear pending IRQ
	NVIC_ClearPendingIRQ(PIT_IRQn);
	
		//check to see which channel triggered interrupt
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK){
			//Clear status flags for timer channel 0
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
		inc_Count;
		
	} 
	return;
}
