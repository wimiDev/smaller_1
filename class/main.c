#include"global.h"
#include"uart.h"
sbit KEY = P1^0	;

unsigned int timer = 0;
//TIMERMANGER _tmg;

void C51Timer0Init();
void init();
void main()
{
    init();
    while(1)
	{
		KEY=1;
		if(!KEY)
		{
			SendString("hello\r\n");
		}
		ClockDistributer(&_tmg);
	}
}
void init()
{
	uartinit();
	C51Timer0Init();
	TimerMangerInit(&_tmg);
	DumpTimerManager(&_tmg);
	smallerinit();
}
 void C51Timer0Init()
{  	
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初值
	TH0 = 0xD4;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1; //使能定时器0中断
    EA = 1;

}

void Timer0Interrupt() interrupt 1 using 2
{
	   
	   timerpump(&_tmg);
	   timer = (timer+1)%1000;
	   if(!timer)
	   {
	   	P54 = ~P54;
 	 
	   }
}

