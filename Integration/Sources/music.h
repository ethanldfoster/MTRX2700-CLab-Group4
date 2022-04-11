#ifndef MUSIC_H
#define MUSIC_H

// 7 Song Notes                      
#define C 45977
#define D 45570
#define E 36363
#define F  34280
#define G  30612
#define A 27272
#define B 24490
#define rest 00000

// Global Value to all changing notes
extern int currentNote;
extern int notfinished;
extern unsigned char overflow;



void music_setup(void);
void inbetween_delay(void);
void delay1(void);
void delay2(void);
void delay3(void);
void songPlay(int songNumber);
void print_seg(int songNumber);

__interrupt void TC5_ISR(void);
__interrupt void TOF_ISR(void);


#endif