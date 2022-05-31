#include <MKL25Z4.h>
#include <stdio.h>
#include <string.h>


#define MASK(x) (1UL << (x))

void LCD_init(void);
       // send LCD commands
void LCD_send_data(uint32_t data);        // send one char to screen


int ijSwap(int i){ // swaps the value of i and j
	int j;
	if(i == 0){
		j = 3;
	} else if (i == 1){
		j = 2;
	} else if (i ==2) {
		j = 1;
	} else if (i == 3) {
		j = 0;
	}
	return j;
}
uint32_t Exp(int base, int pow){ // does exponents base^pow
	uint32_t num = 1;
	
	for (int i = pow; i > 0; i--){
		num *= base;
	};
	return num;
	
};

uint32_t bitToHex(char bin[]){ //converts 4 binary bits to hex
	uint32_t bit = 0x0;
	int j = 0;
	for(int i = 3; i >=0; i--){
		if(bin[i] ==1){
			j = ijSwap(i);
			bit +=Exp(2,j);
		}
	}
	return bit;
};

uint32_t binToHex(char bin[], int length){ //converts a larger than 4 bit binary number (of specified length) into a hex number
	int place = 0x10;
	int pow = 0;
	int n = 0;
	char bit[5];
	uint32_t hex = 0x0;
	for(int i = 0; i <=(length - 1); i++){ //takes 4 bits of the binary number and converts it into one hexadecimal digit
		bit[n] = bin[i];
		n++;
		if(i%3 == 0){ //passes the array onto the 4 bit converter and places the recult in its proper hexedecimal place
			place *= Exp(place, pow);
			hex = place *bitToHex(bit);
			n = 0;
			pow++;
		} 
	}
	return hex;
};

void bitParcer(char bigStr[], char *lilStr, int length, int start, int stop){ //takes the selected range of bits from the larger string and puts it into the smaller string
	if(stop - start > length){
		stop = start + length;
	}
	int n = 0;
	for(int i = start; i < stop; i++){
		lilStr[n] = bigStr[i];
		n++;
	}
	return;
}

void displayString(uint32_t inString[], int strLength){
	for(int j=0; j < strLength; j++){
		LCD_send_data(inString[j]);
	};
	return;
};

	
