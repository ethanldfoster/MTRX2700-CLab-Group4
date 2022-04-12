#include <mc9s12dp256.h>
#include <hidef.h>      /* common defines and macros */

#include <string.h>
#include <stdlib.h>
#include "serial.h"
#include "parser.h"

char param1[MAX_INPUT_LEN - 1];
char param2[MAX_INPUT_LEN];

/*This function determines which command has been given,
takes in the required parameters and executes the commands*/
void parse_command(char* command){

    /*declare required variables*/
    char* function = (char*)malloc(5 * sizeof(char));
    
    
    int i, k;

    /*isolate the command keyword*/
    for(i = 0; i < COMMAND_LENGTH; i++){
      strncat(function, (command + i), 1);
    }
    
    
    /*begin if-else ladder to determine command keyword*/
    if(!strcmp(function, "print")){
      char* message;
      char* reps;
    
      /*get message to transmit and clear buffer*/
      message = get_next_input();
      strcpy(param1, message);
      i = strlen(reps);
      clear_buffer(i, in_buffer);
     
     /*get number of times to transmit message*/
      reps = get_next_input();
      strcpy(param2, reps);
      
      /*use parameters to call print command function*/  
      print_command(param1, atoi(param2));   
      
    }else if(!strcmp(function, "music")){
      char* song_num;
      char* reps;
      
      /*get song number to play*/
      song_num = get_next_input();
      strcpy(param1, song_num);
      i = strlen(song_num);
      clear_buffer(i, in_buffer);
     
      /*get number of times to play song*/
      reps = get_next_input();
      strcpy(param2, reps);
      i = strlen(reps);
      clear_buffer(i, in_buffer);
      
      /*enable the speaker*/
      enable_speaker();
      
      /*play the song the specified number of times*/
      for(k = 0; k < atoi(param2); k++){
        
        songPlay(atoi(param1));
      }
      
      /*disable speaker*/
      disable_speaker();
      
    }else{
      /*in case the command is not valid, output error message*/
      clear_buffer(MAX_INPUT_LEN, trans_buffer);
      print_command("Please enter a valid function", 1);
      
    }

    return;

}


/*called to transmit via serial using interrupts*/
void print_command(char* message, int times){ 
  /*load the output buffer*/ 
  strcpy(trans_buffer, message);
  
  /*specify how many times to repeat*/
  repetitions = times;
  
  /*enable interrupts*/
  configure_transmit_interrupts(&serial_port);
  return;
}
  
