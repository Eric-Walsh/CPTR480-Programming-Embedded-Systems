#include "MKL25z4.h"

const uint16_t BAUD_RATE = 9600;
const uint32_t CLOCK_RATE = 24000000;

void delayMs(uint32_t n)
{
uint32_t i;
uint32_t j;
for(i=0; i < n; i++)
		for(j=0; j < 3500; j++) {}
}

void init_UART2(){
	//send clock to UART
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	//Configure Port D pin 3 for UART output
	PORTD->PCR[3] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[3] |= PORT_PCR_MUX(3);
	
	//Turn off transmit, recieve, and interrupt causes
	UART2_C2 = 0;
	
	//assign Baud rate
	
	uint16_t sbr = (uint16_t)((CLOCK_RATE)/(BAUD_RATE*16));
	
	UART2->BDH = sbr >> 8;
	UART2->BDL = sbr;
	
	//Configure Control register
	UART2->C1 = 0;
	
	//Enable Transit
	UART2->C2 |= 0x8;
}

void UART2_Transmit(uint32_t data){
	UART2_D = data;
}

void Print_String(char string[]){
	uint32_t ascii = 0;
	int i = 0;
	while(!(UART2_S1 & 0x80)){};
	do{
		ascii = string[i];
		i++;
		UART2_Transmit(ascii);
		while(!(UART2_S1 & 0x80)){};
		delayMs(2);
	}while(ascii != 0);
}

void Print_Newline(void){
	UART2_Transmit(0x0a);
	delayMs(2);
}