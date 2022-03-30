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
	LCD_command(0x01);
	init_RGB_LEDs();
	init_switch();
	init_debug_signals();
	Init_PIT(64000);
	__enable_irq();
	
	control_RGB_LEDs(0,1,0);
	countToClock(0);
	while (1) {
		DEBUG_PORT->PTOR = MASK(DBG_MAIN_POS);
		
	}
	
}
