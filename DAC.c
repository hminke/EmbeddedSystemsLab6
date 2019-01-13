// DAC.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Implementation of the 4-bit digital to analog converter
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC

//DAC bit 0 - PB0
//DAC bit 1 - PB1
//DAC bit 2 - PB2
//DAC bit 3 - PB3

#include "DAC.h"
#include "tm4c123gh6pm.h"

#define GPIO_PORTB_OUT          (*((volatile unsigned long *)0x4000503C)) //bits 3-0


// **************DAC_Init*********************
// Initialize 4-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){
	volatile unsigned long delay;
	
	SYSCTL_RCGC2_R |= 0x02;      				// 1) B
	delay = SYSCTL_RCGC2_R;      				// 2) no need to unlock
	GPIO_PORTB_AMSEL_R &= ~0xF; 				// 3) disable analog function on PB3-0
  GPIO_PORTB_PCTL_R &= ~0x0000FFFF; 	// 4) enable regular GPIO
  GPIO_PORTB_DIR_R |= 0xF;    				// 5) outputs on PB3-0
  GPIO_PORTB_AFSEL_R &= ~0xF; 				// 6) regular function on PB3-0
  GPIO_PORTB_DEN_R |= 0xF;    				// 7) enable digital on PB3-0
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){
  GPIO_PORTB_DATA_R = data;
}
