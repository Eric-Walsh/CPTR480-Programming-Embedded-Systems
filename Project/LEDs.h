#ifndef LEDS_H
#define LEDS_H

// Freedom KL25Z LEDs
#define RED_LED_POS (18)		// on port B
#define GREEN_LED_POS (19)	// on port B
#define BLUE_LED_POS (1)		// on port D
#define D1_POS (8) //PTB
#define D2_POS (9)	//PTB
#define D3_POS (10) //PTB
#define D4_POS (11) //PTB
#define D5_POS (2) //PTE
#define D6_POS (3) //PTE
#define D7_POS (4) //PTE
#define D8_POS (5) //PTE

// function prototypes
void init_LEDs(void);
void control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on);
void toggle_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on);

#endif 

// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
