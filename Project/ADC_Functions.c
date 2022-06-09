#include "MKL25Z4.h"
#include "UART_Functions.h"
#include "LCD_Functions.h"

enum ADC_channel{SE0 = 0x00, SE4ab = 0x04, SE3 = 0x03, SE7a = 0x07, SE8 = 0x08, SE9 = 0x09, SE12 = 0x0C, SE13 = 0x0D}; 
enum ADC_mux{A = 0, B = 1};


void Init_ADC(void){
		//enable clock for ADC and Ports E and D
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;	

    //Select analog for pin
    PORTE->PCR[20] &= ~PORT_PCR_MUX_MASK;
    PORTE->PCR[20] |= PORT_PCR_MUX(0);
		PORTE->PCR[21] &= ~PORT_PCR_MUX_MASK;
    PORTE->PCR[21] |= PORT_PCR_MUX(0);
		PORTE->PCR[22] &= ~PORT_PCR_MUX_MASK;
    PORTE->PCR[22] |= PORT_PCR_MUX(0);
		PORTE->PCR[23] &= ~PORT_PCR_MUX_MASK;
    PORTE->PCR[23] |= PORT_PCR_MUX(0);
		PORTE->PCR[29] &= ~PORT_PCR_MUX_MASK;
    PORTE->PCR[29] |= PORT_PCR_MUX(0);
		PORTB->PCR[0] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[0] |= PORT_PCR_MUX(0);
		PORTB->PCR[1] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[1] |= PORT_PCR_MUX(0);
		PORTB->PCR[2] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[2] |= PORT_PCR_MUX(0);
		PORTB->PCR[3] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[3] |= PORT_PCR_MUX(0);
		


    //Bus clock input
    //ADC0->CFG1 = ADC_CFG1_ADLPC_MASK | ADC_CFG1_ADLSMP_MASK | ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0);

    //voltage references 
    //ADC0->SC2 = ADC_SC2_REFSEL(0);
	
		
	
		//Configure the SIM SOPT7 register
		SIM->SOPT7 |= SIM_SOPT7_ADC0ALTTRGEN(1); //Alternate trigger selected
    SIM->SOPT7 |= SIM_SOPT7_ADC0PRETRGSEL(0); //Pre-trigger A
		//SIM->SOPT7 |= SIM_SOPT7_ADC0PRETRGSEL(1); //Pre-trigger B
    SIM->SOPT7 |= SIM_SOPT7_ADC0TRGSEL(9); //TPM1 overflow trigger
		
		//configure the ADC SC1A register 
		ADC0_SC1A |= ADC_SC1_AIEN(0); //conversion complete inturrupt disabled
		ADC0_SC1A |= ADC_SC1_DIFF(0); // single-ended conversions and input channels
		ADC0_SC1A &= ~ADC_SC1_ADCH_MASK; //set input to 0
		
		//configure the ADC SC1B register 
		ADC0_SC1B |= ADC_SC1_AIEN(0); //conversion complete inturrupt disabled
		ADC0_SC1B |= ADC_SC1_DIFF(0); // single-ended conversions and input channels
		ADC0_SC1B &= ~ADC_SC1_ADCH_MASK; //set input to 0
		
		//configure the ADC CFG1 register
		ADC0_CFG1 |= ADC_CFG1_ADLPC(0); //Normal power configuration
		ADC0_CFG1 |= ADC_CFG1_ADIV(0); //divide ratio 1
		ADC0_CFG1 |= ADC_CFG1_ADLSMP(0); // Short sample time
		ADC0_CFG1 |= ADC_CFG1_MODE(1); // single ended 12-bit conversion
		ADC0_CFG1 |= ADC_CFG1_ADICLK(1); // (bus clock)/2
		
        //configure the ADC SC2 register
		ADC0_SC2 |= ADC_SC2_ADTRG(0); //software trigger 
		ADC0_SC2 |= ADC_SC2_ACFE(0); // No compare function
		ADC0_SC2 |= ADC_SC2_DMAEN(0); // DMA disabled
		ADC0_SC2 |= ADC_SC2_REFSEL(0); // Default voltage reference pin pair
		
        //configre the ADC SC3 register
		ADC0_SC3 |= ADC_SC3_ADCO(0); // AVGE = 1 after initiating conversion
		ADC0_SC3 |= ADC_SC3_AVGE(1); // hardware average function enabled
		ADC0_SC3 |= ADC_SC3_AVGS(3); // 16 sampled averaged
    
    /* Enable Interrupts */
	  NVIC_SetPriority(ADC0_IRQn, 3); //0,64,128 or 192
	  NVIC_ClearPendingIRQ(ADC0_IRQn);
	  NVIC_EnableIRQ(ADC0_IRQn);
}

void scan_ADC(uint32_t *array){
	//int i = 0;
	uint32_t channel = SE0;
	uint32_t mux = A;
	char DEBUG[] = "The value is:  ";
	
		for (int i = 0; i < 9; i++){
			ADC0_CFG2 = ADC_CFG2_MUXSEL(mux);
			ADC0->SC1[0] = channel;
			while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)){}
			array[i] = ADC0->R[0] & 0xFFF;
				//Print_String(DEBUG);
				print_base10(array[i], 4);
				Print_Newline();
				switch (channel){
					case SE0:
						channel = SE4ab;
						mux = A;
						break;
					case SE4ab:
						channel = SE3;
						mux = A;
						break;
					case SE3:
						channel = SE7a;
						mux = A;
						break;
					case SE7a:
						channel = SE8;
						mux = A;
						break;
					case SE8:
						channel = SE9;
						mux = A;
						break;
					case SE9:
						channel = SE12;
						mux = A;
						break;
					case SE12:
						channel = SE13;
						mux = A;
						break;
					case SE13:
						channel = SE4ab;
						mux = B;
						break;
					default:
						channel = SE0;
						mux = A;
						break;
				}
			//i++;
			delayMs(10);
		}
	/*	for(int i = 0; i < 9; i++){
			if(i%3 == 0){
				Print_Newline();
			}
			print_base10(array[i], 4);
			delayMs(5);
			while(!(UART2_S1 & 0x80)){}
			UART2_Transmit(0x20);
			UART2_Transmit(0x20);
		}*/
}


void ADC_IRQHandler(void) {;
		//clear pending IRQ
	NVIC_ClearPendingIRQ(ADC0_IRQn);

}
