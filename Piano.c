// Piano.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// There are four keys in the piano
// Daniel Valvano
// December 29, 2014

// Port E bits 3-0 have 4 piano keys

//Piano key 0 - PE0
//Piano key 1 - PE1
//Piano key 2 - PE2

#include "Piano.h"
#include "tm4c123gh6pm.h"

#define KEYS										(*((volatile unsigned long *)0x40024034))
#define GPIO_PORTE_IN           (*((volatile unsigned long *)0x40024034)) //bits 0, 2,3

	
unsigned long Input;

// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){ 
	volatile unsigned long delay;
	
  SYSCTL_RCGC2_R |= 0x10;      				// 1) E
  delay = SYSCTL_RCGC2_R;      				// 2) no need to unlock
	GPIO_PORTE_AMSEL_R &= ~0xD; 				// 3) disable analog function on PE2-0
  GPIO_PORTE_PCTL_R &= ~0x0000FF0F; 	// 4) enable regular GPIO
  GPIO_PORTE_DIR_R &= ~0xD;   				// 5) inputs on PE2-0
  GPIO_PORTE_AFSEL_R &= ~0xD; 				// 6) regular function on PE2-0
  GPIO_PORTE_DEN_R |= 0xD;    				// 7) enable digital on PE2-0
}
// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed
unsigned long Piano_In(void){
  Input = KEYS;
	
	if(Input == 0x01){
		Input = 0;							//key 0 is pressed
	}
	else if(Input == 0x08){
		Input = 1;							//key 1 is pressed
	}
	else if(Input == 0x04){
		Input = 2;							//key 2 is pressed
	}
	else{
		Input = 3;							//no key is pressed
	}
	
  return Input; 
}
