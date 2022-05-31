#include "MKL25z4.h"
#include "TPM_Functions.h"
#include "gpio_defs.h"
#include "Motor_Functions.h"
#include "LCD_Functions.h"
#include "LEDs.h"

const uint32_t FORWARD_PULSE = 0x1500;

const uint32_t STILL_PULSE = 0xFFFE;

const uint32_t BACKWARD_PULSE = 0xE05;

//Right wheel is TPM channel 4, left wheel is channel 5
void right_wheel_forward(){
	TPM0->CONTROLS[4].CnV = FORWARD_PULSE;
	control_RGB_LEDs(1,0,0);
}
	
void left_wheel_forward(){
	TPM0->CONTROLS[5].CnV = FORWARD_PULSE;
	control_RGB_LEDs(0,0,1);
}
	
void right_wheel_stop(){
	TPM0->CONTROLS[4].CnV = STILL_PULSE;
	toggle_RGB_LEDs(1,0,0);
}
	
void left_wheel_stop(){
	TPM0->CONTROLS[5].CnV = STILL_PULSE;
	toggle_RGB_LEDs(0,0,1);
}

void right_wheel_backward(){
	TPM0->CONTROLS[4].CnV = BACKWARD_PULSE;
	control_RGB_LEDs(0,1,0);
}

void left_wheel_backward(){
	TPM0->CONTROLS[5].CnV = BACKWARD_PULSE;
	control_RGB_LEDs(0,1,0);
}

void go_Forward(){
	right_wheel_forward();
	left_wheel_backward();
}

void go_Backward(){
	left_wheel_forward();
	right_wheel_backward();
}

void stop(){
	right_wheel_stop();
	//delayMs(10);
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