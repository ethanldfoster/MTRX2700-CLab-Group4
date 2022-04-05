#include <hidef.h> 
#include "derivative.h" 



// 7 Song Notes                      
#define C	 45977
#define D	 45570
#define E	 36363
#define F  34280
#define G  30612
#define A	 27272
#define B	 24490


// Song List
int starWars[36]  = {A,2,A,2,A,2,F,1,C,1,A,2,F,1,C,1,A,3,E,2,E,2,E,2,F,1,C,1,A,2,F,1,C,1,A,3};  // 18 note imperial march in c major, number represent lnegth of notes, 1 = quaver, 2 = crotchet, 3 = half note
int pirates[32] = {A,1,C,1,D,2,D,2,D,1,E,1,F,2,F,2,F,1,G,1,E,2,E,2,D,1,C,1,C,1,D,3};            //16 notes pirates of caribbean
  


// Global Value to all changing notes
int musicNote = 0;
unsigned char readValueSC;
unsigned char overflow = 0;
 
void songPlay(int); 
// Interrupt for Output Compare            
interrupt(((0x10000 - Vtimch5)/2)-1) void TC5_ISR(void);

// Interrupt for Serial Communication
interrupt(((0x10000 - Vsci0)/2)-1) void SCI0_ISR(void);

// Interrupt for Timer Overflow 
interrupt(((0x10000 - Vtimovf)/2)-1) void TOF_ISR(void);


void SCI0_INIT(void)
{
 
 SCI0BDH = 0x00;  // Must be assigned
 SCI0BDL = 26;    // Set 9600 baud rate to new boards
 SCI0CR1 = 0x00;  // 8 Bit, no parity
 SCI0CR2 = 0xAC;  // Enable trans, recevive (0x04), send(0x08), receive+send (0x0C) 
                  // And Interrupt
}


// Interrupt Service Routine to Output Compare 
interrupt(((0x10000 - Vtimch5)/2)-1) void TC5_ISR(void)
{
 
 TC5   = TC5 + musicNote;             // Update to TC5 
 TFLG1 = 0x20;                        // Clear C5F

}

// Interrupt Service Routine to Serial Communication
interrupt (((0x10000-Vsci0)/2)-1) void SCI0_ISR(void)
{
  
   if(SCI0SR1_RDRF_MASK & SCI0SR1)   // Wait to Receive
     readValueSC = SCI0DRL;          // Save Value
}



// Interrupt Service Routine to Timer Overflow 
interrupt(((0x10000 - Vtimovf)/2)-1) void TOF_ISR(void) 
{
  overflow++;                       // Increment Count
  TFLG2 = TFLG2 | TFLG2_TOF_MASK;   // Clear Flag
}


//
// TCNT max value is 65.536
//
// So 1 cyle is equal to 65.536 / 24mHz 
//
// 1 cyle = 65.536/24.000.000 = 2.73 ms
//

// Timer Counter to 0.5 sn

void delay_1sn(void) 
{

 int i;
 
 TSCR1 = 0x80;                            // Enable Timer
 TSCR2 = 0x00;                            // No interrupt, No Prescale
                                          // Count Value
 for(i=0; i<180; ++i) {                  
  TFLG2 = 0x80;                           // Clear TOF
  while(!(TFLG2 & TFLG2_TOF_MASK));       // Wait for overflow flag to be raised 
 }
 
}

// 1s delay implemented by using Timer Overflow Property of Timer Module.
// Timer Counter to 5 sn
// 
//    2.73  ms    ==  65536
//    5.000 ms    == 120029304,029304 is bigger than 65536
//
// Thus, count value is eqaul to 120029304 / 65536 = 1831.5018

void delay_2sn(void) 
{

 int i;

 TSCR1 = 0x80;                            // Enable Timer 
 TSCR2 = 0x00;                            // No interrupt, No Prescale
 
 for(i=0; i<366; ++i) {                  // Count Value
 
  TFLG2 = 0x80;                           // Clear TOF
 
  while(!(TFLG2 & TFLG2_TOF_MASK));       // Wait for overflow flag to be raised
 }
 
}

// 2s delay implemented by using Timer Overflow Property of Timer Module.
// Timer Counter to 10 sn
// 
// 2.73  ms   ==    65536
// 10.000 ms  ==    240058608,058660 is bigger than 65536
//
// Thus, count value is equal to 240058608,058660 / 65536 = 3663.0036

void delay_3sn(void) 
{

 int i;
 TSCR1 = 0x80;                        // Timer Enable
 TSCR2 = 0x00;                        // No Interrupt, No Prescale
 
 for(i=0; i<720; ++i) {              // Count Value
 
  TFLG2 = 0x80;                       // Clear TOF
 
  while(!(TFLG2 & TFLG2_TOF_MASK));   // Wait for overflow flag to be raised
 }
 
}


//////////////////////////// Main Function //////////////////////////////////////////////

void main(void) 
{
    
    
    
    
    __asm(sei);         //  Disable Interrupts Globally 
    DDRB = 0xFF;        //  PORTB Output
    DDRH = 0x00;        //  PORTH Input
    DDRP = 0xFF;        //  PORTP Output to Seven Segment Display
    PTP  = 0x07;        //  Write number of the song on 7-segment LEDs.
      
  
    TSCR1 = 0x80;       // Timer Enable
    TIOS  = 0x20;       // Select Channel 5 for output compare
    TCTL1 = 0x04;       // Toggle PT5 pin upon match
    TIE   = 0x20;       // Enable Interrupt for Channel 5
    TFLG1 = 0x20;       // Clear C5F
    __asm(cli);          // Enable Interrupts Globally
   
   

      
///////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                   //
// Play 3 different songs for 15 seconds according to what is selected at the two least significant  //
// DIP switches (00, 01, 10, 11).                                                                    //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////
      
      if(PTH == 0x01){                  // If PTH value is 1, then sound first song
         songPlay(1);                   // Call Sound Function
      }
     
         
      if(PTH == 0x02){                  // If PTH value is 2, then sound second song
         songPlay(2);                   // Call Sound Function to second song
      }
           
      if(PTH == 0x03)  {                // If PTH value is 3, then sound third song
        songPlay(3);                    // Call Sound Function to third song
      }
      
     // End
     
     
     
     
     //current song to play
     songPlay(1);
} 




//
// Sound Function
// Play 3 different songs for 15 seconds according to what is selected 
// at the two least significant DIP switches (00, 01, 10, 11).
//

void songPlay(int songNumber)
{
  int i;
	
    	if(songNumber == 1)                      // PTH = 00000001 
    	{   
    	    
    	  	for(i = 0; i < 36; i++){
    	  	                             
        		musicNote = starWars[i];         // Sound First Song
        	  PORTB = musicNote;                // Light PORTB LEDs according to the music.
        	  PORTB = 0x06;                     // Write 1 number to number of song on 7-segment LEDs.
        	  i++;
        	  
        	  if(starWars[i] == 1){
        	     delay_1sn();
        	  }
        	  if(starWars[i] == 2){
        	     delay_2sn();
        	  }
        	  if(starWars[i] == 3){
        	     delay_3sn();
        	  }
        	  
    	  	}
    	}
    	
     	if(songNumber == 2)                      // PTH = 00000001 
    	{   
    	    
    	  	for(i = 0; i < 32; i++){
    	  	                             
        		musicNote = pirates[i];         // Sound First Song
        	  PORTB = musicNote;                // Light PORTB LEDs according to the music.
        	  PORTB = 0x06;                     // Write 1 number to number of song on 7-segment LEDs.
        	  i++;
        	  
        	  if(pirates[i] == 1){
        	     delay_1sn();
        	  }
        	  if(pirates[i] == 2){
        	     delay_2sn();
        	  }
        	  if(pirates[i] == 3){
        	     delay_3sn();
        	  }
        	  
    	  	}
    	}
    	
    //add song 2 and 3 run code here
  	
}


