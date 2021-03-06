/*----------------------------------------------------------------------------*/
/*  LCD initialization and data transfer routines                             */
/*       4-bit bus version                                                    */
/*  Filename: lcd_lib_4bit_20b.c                                                  */
/*  Author:   Larry Aamodt                                                    */
/*  Version:  1/25/19 written                                                 */
/*            1/28/19 updated                                                 */
/*            1/29/20 updated for wtr 2020 project                            */
/*            2/12/20 revised LCD control signal port & pins                  */
/*  Compiler: Keil uVision5                                                   */
/*  Hardware: NXP Freedom board and a 16 line, 2 row LCD display              */
/*            PORT B  bits 1,2,3 used for control                             */
/*            PORT C  bits 0,1,2,3 used for data                            */
/*  Software note:  A software loop is used for time delay generation         */
/*        Port B and E clocks must be turned on before calling these routines */
/*  Function use:   call LCD_command to move the cursor, clear screen, etc.   */
/*                  call LCD_send_data to send one ASCII character code       */
/*----------------------------------------------------------------------------*/
#include <stdint.h>
#include <MKL25Z4.h>

#define LCD_EN              0x00000002    // PTB1 LCD enable 
#define LCD_RW              0x00000004    // PTB2 LCD read/write
#define LCD_RS              0x00000008    // PTB3 LCD RS
#define LCD_LOW4_MASK       0x0000000F    // low 4 bits of a command
#define LCD_UPPER4_MASK     0x000000F0    // upper 4 bits of a command
#define LCD_MASK            0x0000000F    // PortC bits 0-3
#define LCD_DATA_PINS       0x0000000F    // PortC LCD data pins
#define LCD_CNTRL_PINS      0x0000000E    // PortB LCD control pins

/*----------------------------------------------------------------------------
  LCD functions 
 *----------------------------------------------------------------------------*/
void LCD_command(uint32_t command);       // use to send LCD commands
void LCD_send_data(uint32_t data);        // use to send one char to screen
void delayMs(uint32_t n);
void pulse_the_LCD_enable(void);
void LCD_init(void);

/*----------------------------------------------------------------------------
  Initialize the LCD in 4-bit bus mode.         L.Aamodt
 *----------------------------------------------------------------------------*/
void LCD_init(void)
{
  // Note: you need to turn on Port B and C clocks prior to calling this routine

	uint32_t k;

     // First set up bits in GPIO Port C used by the LCD
	for (k=0; k<4; k++) {                  // make ports GPIO
	PORTC->PCR[k] &= ~PORT_PCR_MUX_MASK;    // 4 LCD data bits
	PORTC->PCR[k] |= PORT_PCR_MUX(1);
	}
	
	for (k=1; k<4; k++) {                   // make ports GPIO
	PORTB->PCR[k] &= ~PORT_PCR_MUX_MASK;    //   LCD control 3-bits 
	PORTB->PCR[k] |= PORT_PCR_MUX(1);	
	}
	
	PTC->PDDR |= LCD_DATA_PINS;             // set ports to output
	PTB->PDDR |= LCD_CNTRL_PINS;

	PTB->PCOR = LCD_RW | LCD_RS | LCD_EN;   // clear R/W, RS, and EN	
		// Now initialize the LCD itself
	delayMs(00);
	PTC->PCOR = LCD_MASK;                   // clear output data bits to 0
	PTC->PSOR = (0x3);                   // put a wake-up value on bus
	delayMs(10);
	pulse_the_LCD_enable();
	delayMs(1);
	pulse_the_LCD_enable();
	delayMs(1);
	pulse_the_LCD_enable();
	delayMs(1);
	PTC->PCOR = LCD_MASK;                   // clear output data bits to 0
	PTC->PSOR = (0x2);                   // initialize to 4-bit bus mode
	delayMs(10);
	pulse_the_LCD_enable();
	LCD_command(0x28);                      // Set to 4-bit/2-line/5x7pixels
	LCD_command(0x10);                      // 
	LCD_command(0x0F);                      // Display on, cursor on and blink
	//LCD_command(0x06);                      //
}
/*----------------------------------------------------------------------------
  Send a command to the LCD                      L.Aamodt
 *----------------------------------------------------------------------------*/
void LCD_command(uint32_t command)
{
	PTB->PCOR = LCD_RW | LCD_RS | LCD_EN;   // clear R/W, RS, and EN
	PTC->PCOR = LCD_MASK;                   // clear output data bits to 0
	PTC->PSOR = (command & LCD_UPPER4_MASK)>>4; // output upper 4 bits of command
	pulse_the_LCD_enable();
	PTC->PCOR = LCD_MASK;                   // clear output data bits
	PTC->PSOR = (command & LCD_LOW4_MASK);   // output lower 4 bits
	pulse_the_LCD_enable();
	if (command < 4)
		delayMs(3);                           // command 1 and 2 need 1.64ms
	else
		delayMs(1);                           // all others 40us
}
/*----------------------------------------------------------------------------
   Pulse the LCD enable line                    L.Aamodt
 *----------------------------------------------------------------------------*/
void pulse_the_LCD_enable(void)
{
	PTB->PSOR = LCD_EN;                     // assert enable
	delayMs(1);
	PTB->PCOR = LCD_EN;                     // de-assert enable
}

/*----------------------------------------------------------------------------
   Send data (one character, using ASCII code) to the LCD      L.Aamodt
 *----------------------------------------------------------------------------*/
void LCD_send_data(uint32_t data)
{
	PTB->PCOR = LCD_RW | LCD_EN;            // clear R/W, RS, and EN
	PTB->PSOR = LCD_RS;                     // set RS high
	PTC->PCOR = LCD_MASK;                   // clear output data bits to 0
	PTC->PSOR = (data & LCD_UPPER4_MASK)>>4;   // output upper 4 bits of command
	pulse_the_LCD_enable();
	PTC->PCOR = LCD_MASK;                   // clear output data bits
	PTC->PSOR = (data & LCD_LOW4_MASK);  // output lower 4 bits
	pulse_the_LCD_enable();
}
/*----------------------------------------------------------------------------
  Delay, used with the LCD routines.  Delay specified in units of milliseconds
      The inner loop max count should be 3500 for 20.97 MHZ system clock rate
      or 8000 for 48 MHZ system clock rate                      L.Aamodt
 *----------------------------------------------------------------------------*/
void delayMs(uint32_t n)
{
uint32_t i;
uint32_t j;
for(i=0; i < n; i++)
		for(j=0; j < 8000; j++) {}
}
