#include "MKL25z4.h"
#include "gpio_defs.h"
#include "LEDs.h"
#include "UART_Functions.h"

void init_SPI1(void){
	//enable clock
	SIM->SCGC4 |= SIM_SCGC4_SPI1_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	//disable SPI1 to allow configuration
	SPI1 -> C1 &= ~SPI_C1_SPE_MASK;
	
	//set PTD4 to SPI0_PCS0
	//PORTD->PCR[4] &= ~PORT_PCR_MUX_MASK;
	//PORTD->PCR[4] |= PORT_PCR_MUX(2);
	//set PTD5 to SPI0_SCK
	PORTD->PCR[5] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[5] |= PORT_PCR_MUX(2);
	//set PTD6 to SPI0_MOSI
	PORTD->PCR[6] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[6] |= PORT_PCR_MUX(2);
	//set PTD7 to SPI0_MISO
	PORTD->PCR[7] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[7] |= PORT_PCR_MUX(2);
	
	//select master mode, enable SS output
	SPI1->C1|= SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK | SPI_C1_CPOL_MASK;
	//bidirectional communication on MOSI pin
	SPI1->C2 = SPI_C2_MODFEN_MASK | SPI_C2_BIDIROE_MASK | SPI_C2_SPC0_MASK;
	
	//select active high clock, fist edge sample
	SPI1->C1 &= ~SPI_C1_CPHA_MASK;
	//SPI1->C1 &= ~SPI_C1_CPOL_MASK;
	
	//baude rate = busclock / ((SPR+1)*2^(SPR+1))
	SPI1->BR = SPI_BR_SPPR(2) | SPI_BR_SPR(1);
	
	//enable spi
	SPI1->C1 |= SPI_C1_SPE_MASK;
	
}

uint32_t SPIsendRec(uint32_t data){
	uint32_t dummy;
	
	//send
	SPI1 -> C2 |= SPI_C2_BIDIROE_MASK;
	while(!(SPI1->S & SPI_S_SPTEF_MASK)); //wait for transmit buffer to empty
	SPI1->D = data;
	//delayMs(3);
	while(!(SPI1->S & SPI_S_SPRF_MASK)); //wait for recieve buffer to empty
	dummy =  SPI1->D;
	
	//recieve
	SPI1 -> C2 &= ~SPI_C2_BIDIROE_MASK;
	while(!(SPI1->S & SPI_S_SPTEF_MASK)); //wait for transmit buffer to empty
	SPI1->D = 0xFF;
	//delayMs(3);
	while(!(SPI1->S & SPI_S_SPRF_MASK)); //wait for recieve buffer to empty
	return  SPI1->D;
}

void SPIsend(uint32_t data){
	SPI1 -> C2 |= SPI_C2_BIDIROE_MASK;
	while(!(SPI1->S & SPI_S_SPTEF_MASK)); //wait for transmit buffer to empty
	SPI1->D = data;
	//delayMs(3);
	//while(!(SPI1->S & SPI_S_SPTEF_MASK));
}

void Test_SPI_Loopback(void){
	uint8_t out = 'A', in;
	
	while (1) {
		in = SPIsendRec(out);
		if(in != out){
			control_RGB_LEDs(1,0,0);
		} else {
			control_RGB_LEDs(0,1,0);
		}
		
		for(int i = 0; i < 50; i++);
	}
}
