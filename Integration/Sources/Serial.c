#include <mc9s12dp256.h>
#include <hidef.h>      /* common defines and macros */

#include <string.h>
#include "serial.h"


// InitialiseSerial - Initialise the serial port SCI1
// Input: baudRate is tha baud rate in bits/sec

void serial_setup(int baudRate, SerialPort *serial_port) {
  
  // Baud rate calculation from datasheet
  switch(baudRate){
	case BAUD_9600:
      *(serial_port->baud_high)=0;
      *(serial_port->baud_low)=156;
	  break;
	case BAUD_19200:
      *(serial_port->baud_high)=0;
      *(serial_port->baud_low)=78;
	  break;
	case BAUD_38400:
      *(serial_port->baud_high)=0;
      *(serial_port->baud_low)=39;
	  break;
	case BAUD_57600:
      *(serial_port->baud_high)=0;
      *(serial_port->baud_low)=26;
	  break;
	case BAUD_115200:
      *(serial_port->baud_high)=0;
      *(serial_port->baud_low)=13;
	  break;
  }
  
  /*No funny business*/
  *(serial_port->control_register_1) = 0x00;
}

/*enables interrupts for when data register is full*/
void configure_recieve_interrupts(SerialPort *serial_port){
  *(serial_port->control_register_2) = 0x2C;
  return;
}

/*enables interrupts for when data register is 'empty'*/
void configure_transmit_interrupts(SerialPort *serial_port){
  *(serial_port->control_register_2) = SCI1CR2_RE_MASK|SCI1CR2_TE_MASK|SCI1CR2|SCI1CR2_SCTIE_MASK;
  return;
}

/*function used to take input from serial port and store in buffer, fnishing when
the variable bookend appears in the serial port data register*/
void read_char(SerialPort *serial_port, char* buffer, char bookend, int* string_ready){
  /*used to index the storage buffer*/
  static int counter = 0;
  
  /*read the data in and reset the interrupt flag*/
  volatile char reset = *(serial_port->status_register);
  char out = *(serial_port->data_register);
  
  /*when input is a backspace clear the data a decrement the index*/
  if(out == '\b'){
    if(counter > 0){
      buffer[counter] = '\0';      
      counter--;
    
    }
    return;
  }
  
  /*after checks, save the serial data into the buffer*/
  buffer[counter] = out;
  
  /*check to see if input is complete, if so raise flag*/
  if(out == bookend){
    *string_ready = 1;
    counter = 0;
    return;
  }
  
  /*if input isnt complete increment counter and return*/
  counter++;
  
  /*error checking for if the buffer overflows*/
  if(counter >= MAX_INPUT_LEN){
    clear_buffer(MAX_INPUT_LEN, in_buffer);	
    print_command("Maximum input length exceeded", 1);
  }
    
  return;
}


/*function to feed the dog until serial input is completed*/
char *get_next_input(void){
  while(!string_ready){
    _FEED_COP();
  }
  
  /*reset flag for next input*/
  string_ready = 0;  
  
  /*return the serial input*/
  return in_buffer;
}


/*general function to clear a buffer of specified length*/
void clear_buffer(int len, char buffer[]){
  
  while(len >= 0){
    buffer[len] = '\0';
    len--;
  }
}

/*sends a single char to the serial output*/
void send_char(SerialPort *serial_port, char data){
  while((*(serial_port->status_register) & SCI1SR1_TDRE_MASK) == 0){
  }
  *(serial_port->data_register) = data;
}


/*takes a string and outputs to a serial port, string is bookended by variable character*/
void send_message(SerialPort* serial_port, char* message, char bookend){
  /*since function is called by interrupts and sends one char at a time,
  a persistent variable is needed to index the output message*/
  static int index = 0;
  
  /*store the next character to output*/
  char next_char = *(message+index);
  
  /*if character is not the last one*/
  if(next_char != bookend){    
    
    /*output and increment index*/
    send_char(serial_port, next_char);
    index++;
    
  }else{
    
    /*output bookend char and reset index*/
    send_char(serial_port, bookend);
    index = 0;
    
    /*check if the message should be output again*/
    if(repetitions > 1){
      /*if yes decrement and leave interrupts enable*/
      repetitions--;
        
    }else{
      /*if no disable transmit interrupts*/
      *(serial_port->control_register_2) ^= 0b10000000;
      
    }
  }
  
  
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void serial_ISR(void){

  /*if the interrupt was from transmit flag, transmit the message*/
  if(*(serial_port.control_register_2) & (0b10000000)){
  
    send_message(&serial_port, trans_buffer, bookend);
            
  }else{
    /*otherwise the interrupt came from incoming serial data, so read that*/
    read_char(&serial_port, in_buffer, bookend, &string_ready);
  }
}


