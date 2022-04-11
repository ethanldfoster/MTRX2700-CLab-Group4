#include <mc9s12dp256.h>
#include <hidef.h>      /* common defines and macros */

#include <string.h>
#include "Serial.h"

char test_char = '0';

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
  
  
  *(serial_port->control_register_1) = 0x00;
}

void configure_serial_interrupts(SerialPort *serial_port){
  *(serial_port->control_register_2) = 0x2C;
}

void read_char(SerialPort *serial_port, char* buffer, char bookend, int* string_ready){
  static int counter = 0;
  
  volatile char reset = *(serial_port->status_register);
  char out = *(serial_port->data_register);
  
  buffer[counter] = out;
  
  if(out == bookend){
    *string_ready = 1;
    counter = 0;
    return;
  }
  
  counter++;
  return;
}


char *get_next_command(void){
  while(!string_ready){
    _FEED_COP();
  }
  
  return out_buffer;
}

void send_char(SerialPort *serial_port, char data){

  while((*(serial_port->status_register) & SCI1SR1_TDRE_MASK) == 0){
  }
  *(serial_port->data_register) = data;
}

void send_message(SerialPort* serial_port, char* message, char bookend){
  static int index = 0;
  if(index < 14){
    
    test_char = *(message+index);
    send_char(serial_port, test_char);
    index++;
  }else{
  
    send_char(serial_port, bookend);
    index = 0;
    *(serial_port->control_register_2) ^= 0b10000000;
  }
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void serial_ISR(void){

  if(*(serial_port.control_register_2) & (0b10000000)){
  
    send_message(&serial_port, trans_buffer, bookend);
            
  }else{
    read_char(&serial_port, out_buffer, bookend, &string_ready);
  }
}


