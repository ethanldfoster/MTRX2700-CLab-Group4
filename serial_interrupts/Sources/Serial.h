#ifndef SERIAL_H
#define SERIAL_H

typedef struct _SerialPort {
  byte *baud_high;
  byte *baud_low;
  byte *control_register_1;
  byte *control_register_2;
  byte *data_register;
  byte *status_register;
} SerialPort;

extern SerialPort serial_port;
extern char end_char;
extern char buffer[];


enum {
  BAUD_9600,
  BAUD_19200,
  BAUD_38400,
  BAUD_57600,
  BAUD_115200
};



#endif