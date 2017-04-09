#ifndef __SMALLER_H_
#define __SMALLER_H_
#include"global.h"

extern	TIMER timer1;
extern  TIMER timer2;
extern  TIMER timer4;
extern unsigned char issend;
extern unsigned int session;
extern  char dat1[4];
extern	void smallerinit();
extern	void timer1callback();
extern	void timer2callback();
extern	void timer3callback();
extern	void timer4callback();

#endif