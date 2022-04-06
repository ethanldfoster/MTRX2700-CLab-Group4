#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

void serialRegisters(void);
interrupt 21 void serialISR();

char buffer[500];
int j = 0;

void main() 
{
  serialRegisters();
  EnableInterrupts;
  
  for(;;){
    _FEED_COP();
  }
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

interrupt 21 void serialISR() 
{
  int i;
  int k = 0;
  char outputString[12] = " detected\r\n";
  
  // Check if data is received. The RDRF flag
  if (SCI1SR1 & 0x20) 
  {
    // End of sentence? Look for a carriage return
    if (SCI1DRL == 0x0D) 
    {
      // Don't do anything unless you are ready to send data. The TDRE flag
      // May not need this line since I do it again below
      while(!(SCI1SR1 & 0x80));
      
      // Go through all characters in buffer
      for (k = 0; k < j; k++) 
      {
        // Wait for data to be ready
        while(!(SCI1SR1 & 0x80));
        
        // Write to serial
        SCI1DRL = buffer[k];
        
        // Write the rest of the appended string
        for (i = 0; i < 12; i++) 
        {
          while(!(SCI1SR1 & 0x80));
          SCI1DRL = outputString[i];
        }
      }
      
      // Reset buffer
      j = 0;
    } 
    
    // Store each character of sentence in buffer
    else
    {
      buffer[j] = SCI1DRL;
      j = j + 1;
    }
  }
}