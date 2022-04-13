#include <mc9s12dp256.h>
#include <hidef.h>      /* common defines and macros */

#include <string.h>
#include <stdlib.h>
#include "serial.h"
#include "parser.h"
#include "music.h"

// Global Value to all changing notes
int currentNote = 0;

// Song List
int starWars[36]  = {A,2,A,2,A,2,F,1,C,1,A,2,F,1,C,1,A,3,E,2,E,2,E,2,F,1,C,1,A,2,F,1,C,1,A,3};  // 18 note imperial march in c major, number represent lnegth of notes, 1 = quaver, 2 = crotchet, 3 = half note
int pirates[32] = {A,1,C,1,D,2,D,2,D,1,E,1,F,2,F,2,F,1,G,1,E,2,E,2,D,1,C,1,C,1,D,3};            //16 notes pirates of caribbean
int greenSleeves[36] = {F,3,G,2,A,3,B,1,A,2,G,3,E,2,C,3,D,1,E,2,F,3,D,2,D,3,C,1,D,2,E,3,C,2,A,3};

void enable_speaker(void){
   __asm(sei);         //  Disable Interrupts Globally
    DDRB = 0xFF;        //  PORTB Output
    DDRP = 0xFF;        //  PORTP Output to Seven Segment Display
    PTP  = 0x07;        //  Write number of the song on 7-segment LEDs.
     
 
    TSCR1 = 0x80;       // Timer Enable
    TIOS  = 0x20;       // Select Channel 5 for output compare
    TCTL1 = 0x04;       // Toggle PT5 pin upon match
    TIE   = 0x20;       // Enable Interrupt for Channel 5
    TFLG1 = 0x20;       // Clear C5F
    __asm(cli);          // Enable Interrupts Globally
}

void disable_speaker(void){
   __asm(sei);         //  Disable Interrupts Globally
    DDRB = 0x00;        //  PORTB Output
    DDRP = 0x00;        //  PORTP Output to Seven Segment Display
    PTP  = 0x00;        //  Write number of the song on 7-segment LEDs.
     
 
    TSCR1 = 0x00;       // Timer Enable
    TIOS  = 0x00;       // Select Channel 5 for output compare
    TCTL1 = 0x00;       // Toggle PT5 pin upon match
    TIE   = 0x00;       // Enable Interrupt for Channel 5
    TFLG1 = 0x00;       // Clear C5F
    __asm(cli);          // Enable Interrupts Globally
}

//Given the clock rate of 24mHz and the precaler set to 0 the no of clock cycles for a quaver or quater not delay is 100 therefore
// the program loops through 100 clock cycles

void delay1(void)
{

 int i;
 
 TSCR1 = 0x80;                            // Enable Timer
 TSCR2 = 0x00;                            // No interrupt, No Prescale
 
                                        
 for(i=0; i<100; ++i){                    // Count Value, 100 clock cycles which is around 0.3 seconds for a quaver length note
                 
  TFLG2 = 0x80;                           // Clear TOF
                            
  while(!(TFLG2 & TFLG2_TOF_MASK)){
    _FEED_COP();                              // Wait for overflow flag to be raised
  }
 }
 
}

//given a crotched has the length of 2 quavers this delay is just 200 clock cycles instead of 100 making it 2x longer

void delay2(void)
{

 int i;

 TSCR1 = 0x80;                            // Enable Timer
 TSCR2 = 0x00;  
                           // No interrupt, No Prescaler
 for(i=0; i<200; ++i) {                  // Count Value
 
  TFLG2 = 0x80;                           // Clear TOF
 
  while(!(TFLG2 & TFLG2_TOF_MASK)){
     _FEED_COP();         // Wait for overflow flag to be raised
  }
 }
 
}

//given the half not has the length of 4 quavers this is 4x the no of lcokc cycles or 400 to loop through for the delay

void delay3(void)
{

 int i;
 
 TSCR1 = 0x90;                        // Timer Enable
 TSCR2 = 0x00;                        // No Interrupt, No Prescale
 
 for(i=0; i<400; ++i) {              // Count Value
 
  TFLG2 = 0x80;                       // Clear TOF
 
  while(!(TFLG2 & TFLG2_TOF_MASK)){
     _FEED_COP();               // Wait for overflow flag to be raised
  }
 }
 
}

//this dealy is extremely short and is used to sperate the notes so that repeat notes are distinguished not one constant long note.
void inbetween_delay(void)
{
   
   int i;
   
   TSCR1 = 0x80;
   TSCR2 = 0x00;
   
   for(i=0; i<25; i++){
     TFLG2 = 0x80;
     while(!(TFLG2 & TFLG2_TOF_MASK)){
       _FEED_COP();
     }
   }
   
   
}


void songPlay(int songNumber)
{
  int i;

    if(songNumber == 1)                      // PTH = 00000001
    {  
       
      for(i = 0; i < 36; i++){
                                 
         currentNote = starWars[i];         // Sound First Song
         PORTB = currentNote;                // Light PORTB LEDs according to the music.
         print_seg(songNumber);
         i++;
         
         if(starWars[i] == 1){
            delay1();
         }
         if(starWars[i] == 2){
            delay2();
         }
         if(starWars[i] == 3){
            delay3();
         }
         
         //this puts a very short delay in between notes so that you can tell the difference between repeated notes
         currentNote = rest;
         PORTB = currentNote;
         print_seg(songNumber);
         inbetween_delay();
         
      }
    }
   
      if(songNumber == 2)                      // PTH = 00000001
    {  
       
      for(i = 0; i < 32; i++){
                                 
        currentNote = pirates[i];         // Sound First Song
         PORTB = currentNote;                // Light PORTB LEDs according to the music.
         print_seg(songNumber);                    // Write 1 number to number of song on 7-segment LEDs.
         i++;
         
         if(pirates[i] == 1){
            delay1();
         }
         if(pirates[i] == 2){
            delay2();
         }
         if(pirates[i] == 3){
            delay3();


         }
         
         //this puts a very short delay in between notes so that you can tell the difference between repeated notes
         currentNote = rest;
         PORTB = currentNote;
         print_seg(songNumber);
         inbetween_delay();
         
      }
    }
    
    if(songNumber == 3)                      // PTH = 00000001
    {  
       
      for(i = 0; i < 36; i++){
                                 
        currentNote = greenSleeves[i];         // Sound 3rd Song
         PORTB = currentNote;                // Light PORTB LEDs according to the music.
         print_seg(songNumber);                    // Write 1 number to number of song on 7-segment LEDs.
         i++;
         
         if(greenSleeves[i] == 1){
            delay1();
         }
         if(greenSleeves[i] == 2){
            delay2();
         }
         if(greenSleeves[i] == 3){
            delay3();


         }
         
         //this puts a very short delay in between notes so that you can tell the difference between repeated notes
         currentNote = rest;
         PORTB = currentNote;
         print_seg(songNumber);
         inbetween_delay();
         
      }
    }
    

        
 
}



void print_seg(int songNumber){
  

    if(songNumber == 1)                  
    {  
       

        PORTB = 0x06;                     // Write 1 number to number of song on 7-segment LEDs.
 
    }
    if(songNumber == 2)                  
    {  
       

        PORTB = 0x5B;                     // Write 1 number to number of song on 7-segment LEDs.
 
    }
    
    if(songNumber == 3)                  
    {  
       

        PORTB = 0x4F;                     // Write 1 number to number of song on 7-segment LEDs.
 
    }

       
    
}

/*BELOW ARE THE INTERRUPT ISR'S*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED
// Interrupt Service Routine to Output Compare 
__interrupt void TC5_ISR(void)
{
 
 TC5   = TC5 + currentNote;             // Update to TC5
 TFLG1 = 0x20;                        // Clear C5F

}