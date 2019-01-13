// Lab13.c
// Author: Heather Minke, Ajem McConico, and Justin Treece
// Lab 6
// Start Date: 5/1/2018
// Last Modified Date: 5/2/2018
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// edX Lab 13 
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC
// Port E bits 3-0 have 4 piano keys

#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "DAC.h"
#include "Piano.h"
#include "TExaS.h"
#include "SysTick.h"

unsigned long state;
const uint8_t wave[32]={8,9,11,12,13,14,14,15,15,15,14,14,13,12,
11,9,8,7,5,4,3,2,2,1,1,1,2,2,3,4,5,7};

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delay(unsigned long msec);
void change(unsigned long input);
void makeTone(void);

int main(void){ // Real Lab13 

  TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210,ScopeOn); // activate grader and set system clock to 80 MHz
// PortE used for piano keys, PortB used for DAC        
  Sound_Init(); // initialize SysTick timer and DAC
  Piano_Init();
  EnableInterrupts();  // enable after all initialization are done
  while(1){                
// input from keys to select tone
		change(Piano_In());
		makeTone();
  }
}

// Inputs: Number of msec to delay
// Outputs: None
void makeTone(void){
	if (state != 3){
		static uint32_t i = 0;
		i = (i + 1) % 0x20;
		DAC_Out(wave[i]);
		if (state == 2){
			SysTick_Wait(7584);  //tone E0
		}
		if (state == 1){
			SysTick_Wait(5682);  //tone A0
	}
		if (state == 0){
			SysTick_Wait(4257);  //tone D
		}
	}			
	
}
void change(unsigned long input){
	if(input == 0){
		state = 0;
	}
	if(input == 2){
		state = 2;
	}
	if(input == 1){
		state = 1;
	}
	if(input == 3){
		state = 3;
	}
}
void delay(unsigned long msec){ 
  unsigned long count;
  while(msec > 0 ) {  // repeat while there are still delay
    count = 16000;    // about 1ms
    while (count > 0) { 
      count--;
    } // This while loop takes approximately 3 cycles
    msec--;
  }
}
