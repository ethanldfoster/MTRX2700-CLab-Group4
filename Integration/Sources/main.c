#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Serial.h"
#include "parser.h"
#include "music.h"
#include <string.h>
#include <stdlib.h>

// Global Value to all changing notes
int currentNote = 0;
int notfinished = 0;
unsigned char overflow = 0;

/*Global variables used for interrupts*/
int string_ready = 0;
char in_buffer[256];
char trans_buffer[256];
int repetitions = 1;

/*Set the desired terminating character and output message*/
char bookend = '\r';

/*Select which serial port to use*/
SerialPort serial_port = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};
//SerialPort serial_port = {&SCI0BDH, &SCI0BDL, &SCI0CR1, &SCI0CR2, &SCI0DRL, &SCI0SR1};

char *temp;
char command[256];

void main(void) {
   int i;
   
  
   /*Set baud rate and control register 1*/
  serial_setup(BAUD_9600, &serial_port);
  
  /*setup serial port for recieve interrupts*/
  configure_recieve_interrupts(&serial_port);
  
 	EnableInterrupts;


  for(;;) {
   	/*Assign the serial input*/
    temp = get_next_input();
    strcpy(command, temp);
    i = strlen(temp);
    clear_buffer(i);
 
  
    parse_command(command);
  
    _FEED_COP(); /* feeds the dog */
  } 
}
