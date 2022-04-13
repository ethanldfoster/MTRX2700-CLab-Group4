#ifndef PARSER_H
#define PARSER_H

#define NUM_PARAMS 10
#define COMMAND_LENGTH 5

extern SerialPort serial_port;
extern char trans_buffer[];
extern int repetitions;
extern char bookend;

void parse_command(char* command);
int parse_parameters(char* command, char* parameters[]);


#endif