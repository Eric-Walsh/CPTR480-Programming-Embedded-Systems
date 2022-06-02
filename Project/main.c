#include "MKL25Z4.h"
#include "UART_Functions.h"
#include "gpio_defs.h"
#include "LEDs.h"
#include "TPM_Functions.h"
#include "LCD_Functions.h"
#include "Motor_Functions.h"
#include "Mag_Functions.h"
#include "SPI_Functions.h"
#include "ADC_Functions.h"
#include "PIT_Functions.h"
#include "USound_Functions.h"
#include "switches.h"


int main(){
	Init_ADC();
	init_LEDs();
	init_SPI1();
	init_TPM();
	init_UART2();
	init_Mag();
	init_switch();
	Init_PIT(10500);
	__enable_irq();
	//init_ultrasound();
	//LCD_init();
	while(1){}
}
