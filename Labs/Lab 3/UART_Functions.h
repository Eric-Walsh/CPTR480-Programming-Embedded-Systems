#include "MKL25z4.h"

void init_UART2();

void UART2_Transmit(uint32_t data);

void Print_String(char string[]);

void delayMs(uint32_t n);

void Print_Newline(void);

void print_base10(uint32_t data, uint32_t numdig);