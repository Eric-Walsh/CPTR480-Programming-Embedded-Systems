#include "MKL25z4.h"
#include "gpio_defs.h"
#include "SPI_Functions.h"

uint32_t get_XData(){
	uint32_t data = 0;
	data = SPIsend(0x168);
	data |= SPIsend(0x169) << 8;
	
	return data;
}

uint32_t get_YData(){
	uint32_t data = 0;
	data = SPIsend(0x16A);
	data |= SPIsend(0x16B) << 8;
	
	return data;
}

uint32_t get_ZData(){
	uint32_t data = 0;
	data = SPIsend(0x16C);
	data |= SPIsend(0x16D) << 8;
	
	return data;
}
