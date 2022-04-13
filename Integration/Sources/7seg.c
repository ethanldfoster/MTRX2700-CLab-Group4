#include <mc9s12dp256.h>
#include <hidef.h>      /* common defines and macros */

#include <string.h>
#include <stdlib.h>
#include "serial.h"
#include "parser.h"


void enable_7seg(int num){

  byte output_codes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                         0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
 
  /*configure the appropriate ports*/
  PTP  = 0x07;        
  DDRB = 0xFF;       
  DDRP = 0xFF;
  
  /*write the output code to portb*/      
  PORTB  = output_codes[num];
}

/*simple function to clear the 7seg*/
void clear_7seg(void){
  PORTB = 0;
}


/*simples implementation of a 1ms delay*/
void delay_ms(unsigned int time){
  int i, j;
  
  for(i = 0; i < time; i++){
    for(j = 0; j < 4000; j++);
  }
}