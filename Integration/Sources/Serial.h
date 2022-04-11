#ifndef SERIAL_H
#define SERIAL_H

typedef struct SerialPort {
  byte *baud_high;
  byte *baud_low;
  byte *control_register_1;
  byte *control_register_2;
  byte *data_register;
  byte *status_register;
} SerialPort;

/*The following global variables are used in the ISR*/
extern SerialPort serial_port;
extern char in_buffer[];
extern int string_ready;
extern char bookend;
extern char trans_buffer[];
extern int repetitions;

enum {
  BAUD_9600,
  BAUD_19200,
  BAUD_38400,
  BAUD_57600,
  BAUD_115200
};


void serial_setup(int baudRate, SerialPort *serial_port);
void configure_recieve_interrupts(SerialPort *serial_port);
void configure_transmit_interrupts(SerialPort *serial_port);
void read_char(SerialPort *serial_port, char* buffer, char bookend, int* string_ready);
char *get_next_input(void);
void clear_buffer(int len);
void send_char(SerialPort *serial_port, char data);
void send_message(SerialPort* serial_port, char* message, char bookend);

__interrupt void serial_ISR(void);

#endif