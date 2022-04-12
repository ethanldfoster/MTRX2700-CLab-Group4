#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "serial.h"
#include "parser.h"
#include "music.h"
#include <string.h>
#include <stdlib.h>



/*Global variables used for interrupts*/
int string_ready = 0;
char in_buffer[MAX_INPUT_LEN];
char trans_buffer[MAX_INPUT_LEN];
int repetitions = 1;

/*Set the desired terminating character*/
char bookend = '\r';

/*Select which serial port to use*/
SerialPort serial_port = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};
//SerialPort serial_port = {&SCI0BDH, &SCI0BDL, &SCI0CR1, &SCI0CR2, &SCI0DRL, &SCI0SR1};


char command[MAX_INPUT_LEN];

void main(void) {
   int i;
   char *temp;
    
    
  /*Set baud rate and control register 1*/
  serial_setup(BAUD_9600, &serial_port);
  
  /*setup serial port for recieve interrupts*/
  configure_recieve_interrupts(&serial_port);
  
 	EnableInterrupts;


  for(;;) {
   
    /*Get the next serial input*/
    temp = get_next_input();
    strcpy(command, temp);
    
    /*Clear the buffer for next input*/
    i = strlen(temp);
    clear_buffer(i , in_buffer);
 
    /*At this point the input is the command, so parse it*/
    parse_command(command);
  
    _FEED_COP(); /* feeds the dog */
  } 
}
