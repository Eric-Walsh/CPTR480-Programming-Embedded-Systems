#include "MKL25z4.h"
#include "gpio_defs.h"

void init_SPI1(void);

void SPIsend(uint32_t data);

uint32_t SPIsendRec(uint32_t addr, uint32_t data);

void Test_SPI_Loopback(void);
