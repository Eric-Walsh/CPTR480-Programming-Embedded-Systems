#include "MKL25z4.h"
#include "gpio_defs.h"
#include "Queue_Functions.h"

const uint16_t BAUD_RATE = 9600;
const uint32_t CLOCK_RATE = 24000000;
Q_T q;

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
	
	//Turn on transmit complete inturrupt
	UART2->C2 |= UART_C2_TCIE_MASK;
	
	//assign Baud rate
	uint16_t sbr = (uint16_t)((CLOCK_RATE)/(BAUD_RATE*16));
	
	UART2->BDH = sbr >> 8;
	UART2->BDL = sbr;
	
	//Configure Control register
	UART2->C1 = 0;
	
	
	Q_Init(&q);
	
	//Enable Transit
	UART2->C2 |= 0x8;
	
	NVIC_SetPriority(UART2_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(UART2_IRQn); 
	NVIC_EnableIRQ(UART2_IRQn);
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

void Q_UART2_Transmit(uint32_t data[]){
	for(int i = 0; i < 14; i++){
			Q_Enqueue(&q, data[i]);
		}
	
		UART2_Transmit(Q_Dequeue(&q));
		delayMs(2);
}

//***************************************************************************
//   print_base10                                         L.Aamodt
//      Print an unsigned integer value, base 10, using UART2
//      Two parameters are used.
//        first parameter is the value to be displayed
//        second parameter is the number of digits to display
//***************************************************************************
void print_base10(uint32_t data, uint32_t numdig)
{
	  int32_t i;
		uint32_t array[10];
		for (i=numdig; i>0; i--) {
		    array[i-1] = data%10;
			  data = data/10;
	  }
		for (i=0; i<numdig; i++){
		    UART2->D = array[i]+48;
				while(!(UART2_S1 & 0x80)) { }			
		}
		delayMs(2);
}

void UART2_IRQHandler(void){
	NVIC_ClearPendingIRQ(UART2_IRQn);
	
	if(!Q_Empty(&q)){
		UART2_Transmit(Q_Dequeue(&q));
		delayMs(2);
	}


}