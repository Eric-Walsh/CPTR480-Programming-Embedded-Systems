#include "MKL25z4.h"
#include "gpio_defs.h"
#include "SPI_Functions.h"
#include "LEDs.h"
#include "Mag_Functions.h"
#include "UART_Functions.h"

int main(){
	init_RGB_LEDs();
	init_SPI1();
	init_UART2();
	uint32_t data[3];
	while(1){
		delayMs(5000);
		data[0] = get_XData();
		delayMs(10);
		data[1] = get_YData();
		delayMs(10);
		data[2] = get_ZData();
		delayMs(10);
		
		print_base10(data[0], 3);
		delayMs(10);
		print_base10(data[1], 3);
		delayMs(10);
		print_base10(data[2], 3);
		
		delayMs(5000);
	}
}




