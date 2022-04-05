char buffer[500];
int j = 0;

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "isr_vectors.c"
#include "Serial.h"


SerialPort serial_port = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};
char end_char = '\r';
char buffer[];

void main(void) 
{

  char *read_string;

  serial_setup(BAUD_9600, &serial_port);
  serial_interrupt_setup(&serial_port);

  EnableInterrupts;
  
  for(;;){
    _FEED_COP();
    
    read_string = get_new_command();
    
    
    
    
  }
}


