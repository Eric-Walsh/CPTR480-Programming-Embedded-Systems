#ifndef SWITCHES_H
#define SWITCHES_H
#include "gpio_defs.h"

// Switches is on port A for interrupt support
#define SW1_POS (1)
#define SW2_POS (2)

// Function prototypes
extern void init_switch(void);

// Shared variables
extern volatile unsigned count;

#endif
// *******************************ARM University Program Copyright � ARM Ltd 2013*************************************   
