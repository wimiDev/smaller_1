#include"smaller.h"

TIMER timer1;
TIMER timer2;
TIMER timer4;
unsigned char issend = 1;
unsigned char id = 1;
unsigned int session = 1;

void smallerinit()
{ 	
	TimerMangerInit(&_tmg);
	DumpTimerManager(&_tmg);
	CreateTimer(&_tmg,1,1,&timer1callback,&timer1); 
	DumpTimerManager(&_tmg);	
	if (issend)
	{
		CreateTimer(&_tmg,2,5,&timer2callback,&timer2);
		CreateTimer(&_tmg,4,10,&timer4callback,&timer4);
	}
	else
	{
		CreateTimer(&_tmg,2,1,&timer3callback,&timer2);
	}
	SendString("smallerinit\r\n");
	DumpTimerManager(&_tmg);
}

void timer1callback()
{
	 SendString("timer1\r\n");
	 NRF24L01Int();
	 EnableTimer(&_tmg,1,0);
}
void timer2callback()
{	  
	//48,49,50..都会溢出
	char dat1[4]={'5','5','5','5'};
	//unsigned char id = 1;
	dat1[0] = id+'0';	
	dat1[1] = session + '0';	
	dat1[2] = 9 + '0';
	dat1[3] = 0;	
//	 SendString(dat1);	
//	 SendString("\r\n");
	 NRFSetTxMode(dat1);//内存溢出
	 while(CheckACK());	//检测是否发送完毕  
	 SendString("timer2:\r\n");
//	 SendString(dat1);
//	 SendString("\r\n");
}
void timer3callback()
{	
	unsigned char index = 0;
	//SendString("timer3:");
	NRFSetRXMode();//设置为接收模式
	GetDate();//开始接受数
	RevTempDate[4]=0;
	SendString(RevTempDate);
	SendString("\r\n");
//	if(1)
//	{
//		
//	}
	for(index=0;index<4;index++)
	{
		RevTempDate[index] = 0;
	}
}
void timer4callback()
{	 
	session++;
//	dat1[0] = session;
	 if (session > 20)
		{
			session=1;
		}
	 SendString("timer4\r\n");
}
