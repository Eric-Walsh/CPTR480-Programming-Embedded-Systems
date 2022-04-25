#include <MKL25Z4.h>
#include <stdio.h>
#include <string.h>

int ijSwap(int i);

uint32_t Exp(int base, int pow);

uint32_t bitToHex(char bin[]);

uint32_t binToHex(char bin[], int length);

void bitParcer(char bigStr[], char *lilStr, int length, int start, int stop);

void displayString(uint32_t inString[], int strLength);

void delayMs(uint32_t n); 

void LCD_command(uint32_t command);
