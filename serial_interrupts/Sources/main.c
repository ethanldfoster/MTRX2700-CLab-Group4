#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "Serial.h"
#include <string.h>

int string_ready = 0;
char out_buffer[256];
char trans_buffer[256];
char bookend = '\r';
volatile int test = 0;

//SerialPort serial_port = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};
SerialPort serial_port = {&SCI0BDH, &SCI0BDL, &SCI0CR1, &SCI0CR2, &SCI0DRL, &SCI0SR1};


/*1 for recieving, 0 for transmitting*/
int mode = 0;

void main(void) 
{
  char *command;

  /*Set baud rate and control register 1*/
  serial_setup(BAUD_9600, &serial_port);
  
  if(mode){
    
    /*setup serial port for recieve interrupts*/
    configure_serial_interrupts(&serial_port);

    EnableInterrupts;
  
    command = get_next_command();
         
  }else{
    strcpy(trans_buffer, "This is a test");
    *(serial_port.control_register_2) = SCI1CR2_RE_MASK|SCI1CR2_TE_MASK|SCI1CR2|SCI1CR2_SCTIE_MASK;
    
    EnableInterrupts;   
    
  }
  
  
  
  for(;;){
    _FEED_COP();    
    
        
  }
}


