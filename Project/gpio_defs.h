#ifndef GPIO_DEFS_H
#define GPIO_DEFS_H

#include "MKL25z4.h"

#define clear_screen 0x01
#define cursor_left 0x10
#define cursor_right 0x14
#define cursor_line1 0x80
#define cursor_line2 0xC0

#define sw1 1
#define sw2 2
#define sw3 4 //DO NOT USE
#define sw4 5
#define sw5 4


#define MASK(x) (1UL << (x))
#define SW1_NOT_PRESSED (PTA->PDIR & MASK(sw1))
#define SW1_PRESSED (~(PTA->PDIR) & MASK(sw1))
#define SW2_NOT_PRESSED (PTA->PDIR & MASK(sw2))
#define SW2_PRESSED (~(PTA->PDIR) & MASK(sw2))
#define SW3_NOT_PRESSED (PTA->PDIR & MASK(sw3))
#define SW3_PRESSED (~(PTA->PDIR) & MASK(sw3))
#define SW4_NOT_PRESSED (PTA->PDIR & MASK(sw4))
#define SW4_PRESSED (~(PTA->PDIR) & MASK(sw4))
#define SW5_NOT_PRESSED (PTA->PDIR & MASK(sw5))
#define SW5_PRESSED (~(PTA->PDIR) & MASK(sw5))

#ifndef Q_MAX_SIZE
#define Q_MAX_SIZE (256)
#endif

typedef struct {
	uint8_t Data[Q_MAX_SIZE];
	unsigned int Head;
	unsigned int Tail;
	unsigned int Size;
} volatile Q_T;

enum state_type{Init, CalcPath, ObCheck, Follow, Avoid, ReCalc, Finish};

#endif
// *******************************ARM University Program Copyright � ARM Ltd 2013*************************************   
