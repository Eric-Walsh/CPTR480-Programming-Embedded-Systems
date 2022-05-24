#include "MKL25z4.h"
#include "TPM_Functions.h"
#include "gpio_defs.h"
#include "Motor_Functions.h"
#include "LCD_Functions.h"
#include "LEDs.h"

const uint32_t FORWARD_PULSE = 0x1517 ;

const uint32_t STILL_PULSE = 0xDEA7;

const uint32_t BACKWARD_PULSE = 0xE05;

//Right wheel is TPM channel 0, left wheel is channel 1
void right_wheel_forward(){
	TPM0->CONTROLS[0].CnV = FORWARD_PULSE;
	control_RGB_LEDs(1,0,0);
}
	
void left_wheel_forward(){
	TPM0->CONTROLS[1].CnV = FORWARD_PULSE;
	control_RGB_LEDs(0,0,1);
}
	
void right_wheel_stop(){
	TPM0->CONTROLS[0].CnV = STILL_PULSE;
	toggle_RGB_LEDs(1,0,0);
}
	
void left_wheel_stop(){
	TPM0->CONTROLS[1].CnV = STILL_PULSE;
	toggle_RGB_LEDs(0,0,1);
}

void go_Forward(){
	right_wheel_forward();
	left_wheel_forward();
}

void stop(){
	right_wheel_stop();
	delayMs(10);
	left_wheel_stop();
}
	
void turn_Left(){
	right_wheel_forward();
	left_wheel_stop();
}
	
void turn_Right(){
	right_wheel_stop();
	left_wheel_forward();
}