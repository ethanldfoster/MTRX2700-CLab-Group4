#ifndef PARSER_H
#define PARSER_H

#define NUM_PARAMS 10
#define COMMAND_LENGTH 5

extern SerialPort serial_port;
extern char trans_buffer[];
extern int repetitions;

void parse_command(char* command);
int parse_parameters(char* command, char* parameters[]);
void print_command(char* message, int times);

#endif