#ifndef GPIO_DEFS_H
#define GPIO_DEFS_H

#define clear_screen 0x01
#define cursor_left 0x10
#define cursor_right 0x14
#define cursor_line1 0x80
#define cursor_line2 0xC0

#define sw1 1
#define sw2 2

#define MASK(x) (1UL << (x))
#define SW1_NOT_PRESSED (PTA->PDIR & MASK(sw1))
#define SW1_PRESSED (~(PTA->PDIR) & MASK(sw1))
#define SW2_NOT_PRESSED (PTA->PDIR & MASK(sw2))
#define SW2_PRESSED (~(PTA->PDIR) & MASK(sw2))

enum state_type{stateA,stateB,stateC,stateD,stateE,stateF,stateG,stateH,stateI};

#endif
// *******************************ARM University Program Copyright � ARM Ltd 2013*************************************   
