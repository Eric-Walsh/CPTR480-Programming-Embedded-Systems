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
#include "USound_Functions.h"

void Test_Motors(int val){
	if(val == 0){
		go_Forward();
	} else if (val == 1){
		go_Backward();
	} else if(val == 2){
		turn_Left();
	} else if(val == 3) {
		turn_Right();
	} else {
		stop();
	}
}

void Test_Mag(){
	uint32_t test =  SPIsendRec(0xCF, 0xFF);
	//PTD->PSOR |= MASK(4);
	if(test != 0x40){
		control_RGB_LEDs(1,0,0);
		print_base10(test, 5);
		Print_Newline();
	}	else {
		control_RGB_LEDs(0,1,0);
		print_base10(test, 3);
		Print_Newline();
		test = get_XData();
		print_base10(test, 5);
		Print_Newline();
	}
	control_White_LEDs(test);
	
	delayMs(10);
	//PTD->PCOR |= MASK(4);
}

void Test_UART(){
	char string[] = "Testing UART2";
	//control_White_LEDs(string[0]);
	Print_String(string, 13);
	Print_Newline();
}

void Test_ADC(){
	uint32_t array[9];
	scan_ADC(array);
	//control_White_LEDs(array[0]);
	/*for(int i = 0; i < 9; i++){
		print_base10(array[i], 3);
		Print_Newline();
	}*/
}

void Test_USound(){
	print_base10(measure_distance(), 3);
}