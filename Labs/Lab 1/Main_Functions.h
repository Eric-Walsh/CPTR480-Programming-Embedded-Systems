#include <stdio.h>
#include <MKL25Z4.H>
#include "PIT_Functions.h"
#include "LCD_Functions.h"


void countToTime(uint32_t *min, uint32_t *sec, uint32_t *tenths);

uint32_t decToHex(int dec);

void decToClock(uint32_t min, uint32_t sec, uint32_t tenth, uint32_t *clock[]);

void placeSeperator(int dec, int *tens, int *ones);

void countToClock(uint32_t count);
