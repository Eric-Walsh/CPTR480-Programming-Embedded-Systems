#include <stdio.h>
#include <math.h>
#include <MKL25Z4.H>
#include "PIT_Functions.h"
#include "LCD_Functions.h"
#include "gpio_defs.h"
#include "LEDs.h"

	uint32_t minutes = 0;
	uint32_t seconds = 0;
	uint32_t tenthsec = 0;
	uint32_t clock[] = {0,0,0,0,0,0,0,0,0};
	enum state_type present_state,next_state;
	
	
unsigned int counter; //increments everytime the PIT IRQ ia called

void countToTime(){ //converts the counter to a time format 00:00:00
	unsigned int count = counter;
	minutes = floor(count/6000);
	count = count - minutes*6000;
	seconds = floor(count/100);
	count =  count - seconds*100;
	tenthsec = count;
	return;
}


uint32_t decToHex(int dec){ //converts decimal numbers to hexidecimal numbers
	switch(dec){
		case 0:
			return 0x0;
			break;
		case 1:
			return 0x1;
			break;
		case 2:
			return 0x2;
			break;
		case 3:
			return 0x3;
			break;
		case 4:
			return 0x4;
			break;
		case 5:
			return 0x5;
			break;
		case 6:
			return 0x6;
			break;
		case 7:
			return 0x7;
			break;
		case 8:
			return 0x8;
			break;
		case 9:
			return 0x9;
			break;
		case 10:
			return 0xA;
			break;
		case 11:
			return 0xB;
			break;
		case 12:
			return 0xC;
			break;
		case 13:
			return 0xD;
			break;
		case 14:
			return 0xE;
			break;
		case 15:
			return 0xF;
			break;
		default :
			return 0xFF;
	}
}


void placeSeperator(int dec, int *tens, int *ones){ //seperates the tens and ones place into seperate variables
	if(dec%10 == 0){
		*tens = dec/10;
		*ones = 0;
	} else {
		*tens = floor(dec/10);
		*ones = dec - (*tens*10);
	}
	return;
}

void decToClock(){ //takes the time format, converts it to hex, then puts it into a clock string
	int ones;
	int tens;
	
	placeSeperator(minutes, &tens, &ones);
	clock[0] = decToHex(tens) + 0x30;
	clock[1] = decToHex(ones) + 0x30;
	placeSeperator(seconds, &tens, &ones);
	clock[2] = 0x3A;
	clock[3] = decToHex(tens) + 0x30;
	clock[4] = decToHex(ones) + 0x30;
	placeSeperator(tenthsec, &tens, &ones);
	clock[5] = 0x3A;
	clock[6] = decToHex(tens) + 0x30;
	clock[7] = decToHex(ones) + 0x30;
	return;
}

void countToClock(uint32_t count){
		counter = count;
	//convert the counter to a time format 00:00:00
		countToTime();
		//converts the time from decimal to hex, then puts it into the clock array
		decToClock();
		//display the time on the LCD
		LCD_command(0x01);
		displayString(clock, 8);
	return;
}

void inc_Count(void){
	counter++;
	return;
}

void clear_Count(void){
	counter = 0;
	return;
}

uint32_t get_Count(void){
	return counter;
}

void display_Count(void){
	countToTime();
	decToClock();
	LCD_command(clear_screen);
	displayString(clock, 8);
	control_RGB_LEDs(0,0,1);
	return;
}

void display_Error(void){
	//int32_t i;
	LCD_command(clear_screen);
		//LCD_command(cursor_line1);
	uint32_t error[8] = {'E','R','R','O','R', ':',' ',' '};
		//uint32_t array[5];
		displayString(error,8);
		LCD_command(cursor_line2);
		countToTime();
		decToClock();
		displayString(clock, 8);
	//	LCD_command(cursor_line1);
	}

	void display_Ready(void){
		LCD_command(clear_screen);
		//LCD_command(cursor_line1);
		uint32_t array[] = {'R', 'E', 'A', 'D', 'Y'};
		displayString(array, 5);
		control_RGB_LEDs(1,1,1);
	}
		

void state_Update(int flag){
	switch (present_state){
		case stateA:
			if(flag == 0){
				next_state = stateA;
			} else if(flag == 1){
				next_state = stateB;
			}
			break;
		case stateB:
			next_state = stateC;
			break;
		case stateC:
			if(flag ==0){
				next_state = stateC;
			}else if(flag == 1){
				next_state = stateD;
			}
			break;
		case stateD:
			if(flag ==0){
				next_state = stateD;
			}else if(flag == 1){
				next_state = stateE;
			} else if(flag == 2){
				next_state = stateF;
			}
			break;
		case stateE:
			next_state = stateH;
			break;
		case stateF:
			if(flag ==0){
				next_state = stateF;
			}else if(flag == 1){
				next_state = stateE;
			} else if(flag == 2){
				next_state = stateG;
			}
			break;
		case stateG:
			next_state = stateH;
			break;
		case stateH:
			if(flag == 0){
				next_state = stateH;
			} else if(flag == 1){
				next_state = stateI;
			}
			break;
		case stateI:
			next_state = stateA;
			break;
		default:
			next_state = stateA;
			break;
	}
	
	present_state = next_state;
	return;
}

