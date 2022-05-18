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
	init_Mag();
	uint32_t data[3] = {0,0,0};
	uint32_t line[] = {'X', '=', ' '};
	uint32_t flag;
	while(1){   
		
		PTD->PCOR |= MASK(4);
		flag = get_Mag_Status();
		PTD->PSOR |= MASK(4);
		
		if(flag & 0x4){
			delayMs(10);
			PTD->PCOR |= MASK(4);
			data[0] = get_XData();
			PTD->PSOR |= MASK(4);
			
			delayMs(10);
			PTD->PCOR |= MASK(4);
			data[1] = get_YData();
			PTD->PSOR |= MASK(4);
			
			delayMs(10);
			PTD->PCOR |= MASK(4);
			data[2] = get_ZData();
			PTD->PSOR |= MASK(4);
			delayMs(10);
			
			line[0] = 'X';
			delayMs(10);
			Print_String(line, 3);
			delayMs(10);
			print_base10(data[0], 5);
			Print_Newline();
			
			line[0] = 'Y';
			delayMs(10);
			Print_String(line,3 );
			delayMs(10);
			print_base10(data[1], 5);
			Print_Newline();
			
			line[0] = 'Z';
			delayMs(10);
			Print_String(line, 3);
			delayMs(10);
			print_base10(data[2], 5);
			Print_Newline();
			
		} else {
			data[0] = flag;
			data[1] = 0;
			data[2] = 0;
			
			delayMs(10);
			print_base10(data[0], 5);
			Print_Newline();
		}
		
		
		
		//PTD->PSOR |= MASK(4);
		delayMs(5000);
	}
}




