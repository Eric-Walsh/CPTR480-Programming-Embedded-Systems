#include "MKL25z4.h"
#include "gpio_defs.h"
#include "SPI_Functions.h"
#include "LEDs.h"

int main(){
	init_RGB_LEDs();
	init_SPI1();
	Test_SPI_Loopback();
}




