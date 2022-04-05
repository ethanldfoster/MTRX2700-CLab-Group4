#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "isr_vectors.c"

void serialRegisters(void);
__interrupt void serialISR(void);

char buffer[500];
int j = 0;

void main(void) 
{
  serialRegisters();
  EnableInterrupts;
  
  for(;;);
}

void serialRegisters(void) 
{
  // Set baud rate to 9600
  SCI1BDL = 0x9C;
  SCI1BDH = 0;
  
  // No fancy stuff needed
  SCI1CR1 = 0;
  
  // 2C = 0010110, Enable receive interrupt, transmit, receive
  SCI1CR2 = 0x2C;
}
