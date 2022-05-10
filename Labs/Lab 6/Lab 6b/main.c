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
	uint32_t line[] = {'X', '=', ' '};
	while(1){
		delayMs(50);
		data[0] = get_XData();
		delayMs(10);
		data[1] = get_YData();
		delayMs(10);
		data[2] = get_ZData();
		delayMs(10);
		
		Print_String(line);
		delayMs(10);
		print_base10(data[0], 4);
		Print_Newline();
		
		line[0] = 'Y';
		Print_String(line);
		delayMs(10);
		print_base10(data[1], 4);
		Print_Newline();
		
		line[0] = 'Z';
		Print_String(line);
		delayMs(10);
		print_base10(data[2], 4);
		Print_Newline();
		
		delayMs(5000);
	}
}




