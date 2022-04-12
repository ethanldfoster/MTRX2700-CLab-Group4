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


void enable_speaker(void);
void disable_speaker(void);
void inbetween_delay(void);
void delay1(void);
void delay2(void);
void delay3(void);
void songPlay(int songNumber);
void print_seg(int songNumber);

__interrupt void TC5_ISR(void);



#endif