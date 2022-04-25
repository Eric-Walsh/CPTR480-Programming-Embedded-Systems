/* ***************************************************************************************************************
// Filename: main.c 																							   //
// Author: E.Walsh 																								   //
// Version: 3/29/22 written 																					   //
// Processor: NXP MKL25Z4 																						   //
// Compiler: Keil uVision5 																						   //
// Library: CMSIS core and device startup 																		   //
// also needs Pit_Functions.c, debug_signals.c, LEDs.c, Main_Functions.c, switches.s, gpio_defs.h, LCD_Functions.c //
// Hardware: MKL25Z128VLH4 Microcontroller connected to 4 switches,a DAC, ADC, 2 LEDS, and a 2x8 LCD  			   //
// Expected Outcome: The purpose of this software is to have the user start the PIT timer by pressing switch 1 and //
// stop the timer by pressing it again. The elapsed time would be displayed on the LCD screen. If the elapsed time //
// is greater than 1000 ms, then the LED on the kl25 lights red and stays red until the reset button (switch 2) is //
// pressed.																										   //
// Actual outcome: The switches screen functions as intended. The elapsed time is inaccurate due to incertainty to //
// the frequency of the clock.																					   //
// ****************************************************************************************************************/
#include "MKL25z4.h"
#include "PIT_Functions.h"
#include "switches.h"
#include "gpio_defs.h"
#include "LCD_Functions.h"
#include "Main_Functions.h"
#include "LEDs.h"

extern volatile unsigned switch_pressed;
extern void init_debug_signals(void);


void LCD_init(void);
void LCD_command(uint32_t command);
void LCD_send_data(uint32_t data);
void delayMs(uint32_t n);



int main(){
		// Enable clock to Ports B and C
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	LCD_init();
	LCD_command(clear_screen);
	init_RGB_LEDs();
	init_switch();
	init_debug_signals();
	Init_PIT(10500);
	__enable_irq();
	present_state = stateA;
	control_RGB_LEDs(0,1,0);
	countToClock(0);
	while (1) {
		int flag = 0;
		switch (present_state){
			case stateA:
				if(SW1_NOT_PRESSED){
					flag = 0;
				} else if (SW1_PRESSED){
					flag = 1;
				}
				break;
			case stateB:
				clear
					
		
	}
	
}
