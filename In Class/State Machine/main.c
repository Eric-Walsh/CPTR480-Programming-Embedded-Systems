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
// Actual outcome: The switches screen functions as intended.  //
// 																					   //
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
extern enum state_type present_state,next_state;


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
	//init_debug_signals();
	Init_PIT(10500);
	__enable_irq();
	present_state = stateA;
	control_RGB_LEDs(0,1,0);
	countToClock(0);
	LCD_command(clear_screen);
	//LCD_command(cursor_line1);
	while (1) {
		int flag = 0;
		uint32_t count = get_Count();
		switch (present_state){
			case stateA: //Waiting for sw1 to be pressed
				if(SW1_NOT_PRESSED){
					flag = 0;
					control_RGB_LEDs(0,0,0);
				} else if (SW1_PRESSED){
					flag = 1;
				}
				break;
			case stateB: //starting the timer
				clear_Count();
				control_RGB_LEDs(1,0,0);
				Start_PIT();
				break;
			case stateC: //debounce buffer
				if(count < 10){
					flag = 0;
				} else if (count >= 10){
					flag = 1;
				}
				break;
			case stateD: //error checking
				if(SW1_PRESSED && (count < 1000)){
					flag = 0;
				} else if(count > 1000){
					flag = 1;
				} else if(SW1_NOT_PRESSED && (count < 1001)){
					flag = 2;
				}
				break;
			case stateE: //Error state
				Stop_PIT();
				display_Error();
				break;
			case stateF: //error checking
				if(SW1_NOT_PRESSED){
					flag = 0;
				} else if(count > 1000){
					flag = 1;
				} else if(SW1_PRESSED){
					flag = 2;
				}
				break;
			case stateG: //sucess state
				Stop_PIT();
				display_Count();
				break;
			case stateH: //waiting for restart state
				if(SW2_NOT_PRESSED){
					flag = 0;
				} else if (SW2_PRESSED){
					flag = 1;
				}
				break;
			case stateI: //restart and clear screen
				display_Ready();
				break;
			default:
				flag = 0;
				break;
		}
		state_Update(flag);
	}
	
}
