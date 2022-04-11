#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "timers.h"


#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void UnimplementedISR(void)
{
   /* Unimplemented ISRs trap.*/
   asm BGND;
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void serialISR() 
{
  int j, i;
  int k = 0;
  char outputString[12] = " detected\r\n";
  
  // Check if data is received. The RDRF flag
  if (SCI1SR1 & 0x20) 
  {
    // End of sentence? Look for a carriage return
    if (SCI1DRL == 0x0D) 
    {
      // Don't do anything unless you are ready to send data. The TDRE flag
      // May not need this line since I do it again below
      while(!(SCI1SR1 & 0x80));
      
      // Go through all characters in buffer
      for (k = 0; k < j; k++) 
      {
        // Wait for data to be ready
        while(!(SCI1SR1 & 0x80));
        
        // Write to serial
        SCI1DRL = buffer[k];
        
        // Write the rest of the appended string
        for (i = 0; i < 12; i++) 
        {
          while(!(SCI1SR1 & 0x80));
          SCI1DRL = outputString[i];
        }
      }
      
      // Reset buffer
      j = 0;
    } 
    
    // Store each character of sentence in buffer
    else
    {
      buffer[j] = SCI1DRL;
      j = j + 1;
    }
  }
}



typedef void (*near tIsrFunc)(void);
const tIsrFunc _vect[] @0xFF80 = {     /* Interrupt table */
        UnimplementedISR,                 /* vector 0x40 */
        UnimplementedISR,                 /* vector 0x3F */
        UnimplementedISR,                 /* vector 0x3E */
        UnimplementedISR,                 /* vector 0x3D */
        UnimplementedISR,                 /* vector 0x3C */
        UnimplementedISR,                 /* vector 0x3B */
        UnimplementedISR,                 /* vector 0x3A */
        UnimplementedISR,                 /* vector 0x39 */
        UnimplementedISR,                 /* vector 0x38 */
        UnimplementedISR,                 /* vector 0x37 */
        UnimplementedISR,                 /* vector 0x36 */
        UnimplementedISR,                 /* vector 0x35 */
        UnimplementedISR,                 /* vector 0x34 */
        UnimplementedISR,                 /* vector 0x33 */
        UnimplementedISR,                 /* vector 0x32 */
        UnimplementedISR,                 /* vector 0x31 */
        UnimplementedISR,                 /* vector 0x30 */
        UnimplementedISR,                 /* vector 0x2F */
        UnimplementedISR,                 /* vector 0x2E */
        UnimplementedISR,                 /* vector 0x2D */
        UnimplementedISR,                 /* vector 0x2C */
        UnimplementedISR,                 /* vector 0x2B */
        UnimplementedISR,                 /* vector 0x2A */
        UnimplementedISR,                 /* vector 0x29 */
        UnimplementedISR,                 /* vector 0x28 */
        UnimplementedISR,                 /* vector 0x27 */
        UnimplementedISR,                 /* vector 0x26 */
        UnimplementedISR,                 /* vector 0x25 */
        UnimplementedISR,                 /* vector 0x24 */
        UnimplementedISR,                 /* vector 0x23 */
        UnimplementedISR,                 /* vector 0x22 */
        UnimplementedISR,                 /* vector 0x21 */
        UnimplementedISR,                 /* vector 0x20 */
        UnimplementedISR,                 /* vector 0x1F */
        UnimplementedISR,                 /* vector 0x1D */
        UnimplementedISR,                 /* vector 0x1C */
        UnimplementedISR,                 /* vector 0x1B */
        UnimplementedISR,                 /* vector 0x1A */
        PORTH_ISR,                 /* vector 0x19 (PORT H) */
        UnimplementedISR,                 /* vector 0x18 (PORT J) */
        UnimplementedISR,                 /* vector 0x17 (ATD1) */
        UnimplementedISR,                 /* vector 0x16 (ATD0) */
        serialISR, /* vector 0x15 (SCI1) */
        UnimplementedISR,                 /* vector 0x14 (SCI0) */
        UnimplementedISR,                 /* vector 0x13 */
        UnimplementedISR,                 /* vector 0x12 */
        UnimplementedISR,                 /* vector 0x11 */
        UnimplementedISR,                 /* vector 0x10 (TOF) */
        UnimplementedISR,                          /* vector 0x0F (TIE, C7I)  */
        UnimplementedISR,                 /* vector 0x0E (TIE, C6I)  */
        UnimplementedISR,                 /* vector 0x0C (TIE, C5I)  */
        UnimplementedISR,                 /* vector 0x0C (TIE, C4I)  */
        UnimplementedISR,                 /* vector 0x0B (TIE, C3I)  */
        UnimplementedISR,                 /* vector 0x0A (TIE, C2I)  */
        UnimplementedISR,                 /* vector 0x09 (TIE, C1I)  */
        UnimplementedISR,                 /* vector 0x08 (TIE, C0I) */
        UnimplementedISR,                 /* vector 0x07 (RTIE) */
        UnimplementedISR,                 /* vector 0x06 */
        UnimplementedISR,                 /* vector 0x05 */
        UnimplementedISR,                 /* vector 0x04 */
        UnimplementedISR,                 /* vector 0x03 */
        UnimplementedISR,                 /* vector 0x02 */
        UnimplementedISR,                 /* vector 0x01 */
       // _Startup                          /* vector 0x00 (RESET) */
   };
