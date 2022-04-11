#include <mc9s12dp256.h>
#include <hidef.h>      /* common defines and macros */

#include <string.h>
#include <stdlib.h>
#include "Serial.h"
#include "parser.h"

char param1[100];
char param2[5];

void parse_command(char* command){

    char* function = (char*)malloc(5 * sizeof(char));
    char* arg1;
    char* arg2;
    
    int i, k;

    for(i = 0; i < COMMAND_LENGTH; i++){
      strncat(function, (command + i), 1);
    }
    
    
    
    if(!strcmp(function, "print")){
    
      
      arg1 = get_next_input();
      strcpy(param1, arg1);
      i = strlen(arg1);
      clear_buffer(i);
     
      arg2 = get_next_input();
      strcpy(param2, arg2);
         
      print_command(param1, atoi(param2));   
    }else{
      print_command("Please enter a valid function", 1);
      
    }

    return;

}



void print_command(char* message, int times){
  strcpy(trans_buffer, message);
  repetitions = times;
  configure_transmit_interrupts(&serial_port);
  return;
}
  
