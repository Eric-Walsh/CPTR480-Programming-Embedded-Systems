#include "MKL25z4.h"
#include "gpio_defs.h"
#include "SPI_Functions.h"
#include "LEDs.h"
#include "UART_Functions.h"
#include "LCD_Functions.h"

void init_Mag(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[4] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[4] |= PORT_PCR_MUX(1);
	
	PORTD->PCR[0] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[0] |= PORT_PCR_MUX(1);
	
	PTD->PDDR |= MASK(4);
	PTD->PSOR |= MASK(4);
	
	//PTD->PDDR |= MASK(0);
	//PTD->PSOR |= MASK(0);
	
	delayMs(10);
	
	uint32_t test = SPIsendRec(0xCF, 0xFF);
	
	if(test != 0x40){
		control_RGB_LEDs(1,0,0);
		print_base10(test, 4);
		Print_Newline();
	}	else {
		control_RGB_LEDs(0,1,0);
	}
	
	delayMs(10);
	
	//delayMs(50);
	test = SPIsendRec(0x60, 0x80);
	test = SPIsendRec(0xE0, 0xFF);
	if(test != 0x80){
		control_RGB_LEDs(1,0,0);
		print_base10(test, 4);
		Print_Newline();
	}	else {
		control_RGB_LEDs(0,1,0);
	}
	
	
}

uint32_t get_Mag_Status(){
	uint32_t data = 0;
	data = SPIsendRec(0xE7, 0xFF);
	
	return data;
}

uint32_t get_XData(){
	uint32_t data = 0;
	data = SPIsendRec(0xE8, 0xFF) ;
	//data &= 0xFF;
	data |= SPIsendRec(0xE9, 0xFF) << 8;
	//data &= 0xFFFF;
	
	return data;
}

uint32_t get_YData(){
	uint32_t data = 0;
	data = SPIsendRec(0xEA, 0xFF) ;
	//data &= 0xFF;
	data |= SPIsendRec(0xEB, 0xFF) << 8;
	//data &= 0xFFFF;
	return data;
}

uint32_t get_ZData(){
	uint32_t data = 0;
	data = SPIsendRec(0xEC, 0xFF) ;
	//data &= 0xFF;
	data |= SPIsendRec(0xED, 0xFF)   << 8;
	//data &= 0xFFFF;
	return data;
}
