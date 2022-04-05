#include <mc9s12dp256.h>

#include "Serial.h"



void serial_setup(int baudRate, SerialPort *serial_port){
  
  switch(baudRate){
    case BAUD_9600:
      *(serial_port->BaudHigh) = 0;
      *(serial_port->BaudLow) = 156;
      break;

  *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK | SCI1CR2_TE_MASK;
  *(serial_port->ControlRegister1) = 0x00;
}

void serial_interrupt_setup(SerialPort *serial_port){
  *(serial_port->control_register_2) |= 0b00100000;
}

char serial_read_char(SerialPort *sci, char end_char){
  
  char out;
  
  volatile char reset = *(sci->status_register);
  out = *(sci->data_register);
  
  if(out == end_char){
    
    string_ready = 1;
    return out;
  }
  
  
  return out;
  
}

char* get_next_command(void){
  
  while(!string_ready){
    
    _FEED_COP();
  }
  
  return buffer;
}


void serial_ISR(void){

  static int counter = 0;
  
  char out = serial_read_char(serial_port, end_char);
  
  buffer[counter] = out;
  
  counter++;
  
}



