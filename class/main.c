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
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xCD;		//���ö�ʱ��ֵ
	TH0 = 0xD4;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1; //ʹ�ܶ�ʱ��0�ж�
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

