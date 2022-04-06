#ifndef SERIAL_HEADER
#define SERIAL_HEADER


// function to initialise the timer
void Serial_read (void);

// Timer interrupt definition
__interrupt void SC1_ISR(void);


#endif
