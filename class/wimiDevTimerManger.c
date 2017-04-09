
#include"wimiDevTimerManger.h"
 TIMERMANGER _tmg;

 void TimerMangerInit(TIMERMANGER* __timerManger)
 {	
 	unsigned char index=0;
	__timerManger->_size=0;
	__timerManger->_count=0;
	__timerManger->_maxcount=100;
	for(index=0;index<_TIMERPOOL_MAXSIZE;++index)
	{
		__timerManger->_TIMERPOOL[index]._time=0;
		__timerManger->_TIMERPOOL[index]._timeNow=0;
		__timerManger->_TIMERPOOL[index]._enable=0;
	    __timerManger->_TIMERPOOL[index]._id=0;
	    __timerManger->_TIMERPOOL[index]._callback=0;
	}
 }
 void timerpump(TIMERMANGER* __timerManger)
 {
 	__timerManger->_count++;
 }
 void ClockDistributer(TIMERMANGER* __timerManger)
 {
	 if(__timerManger->_count>=__timerManger->_maxcount)
	 {
	 	__timerManger->_count=0;
		TimerEventDistributer(__timerManger);
	 }
 }
void TimerEventDistributer(TIMERMANGER* __timerManger)
{
	unsigned char index=0;		
	for(index=0;index<__timerManger->_size;++index)
	{  	
	   __timerManger->_TIMERPOOL[index]._timeNow++;
	   if( __timerManger->_TIMERPOOL[index]._timeNow >= __timerManger->_TIMERPOOL[index]._time &&
		   __timerManger->_TIMERPOOL[index]._enable)
	   {
		  __timerManger->_TIMERPOOL[index]._timeNow=0;
	   	  __timerManger->_TIMERPOOL[index]._callback();
	   }
	}
}

 void CreateTimer(TIMERMANGER* __timerManger,unsigned char id,unsigned char time,TimerCallBack callback,TIMER *timerout)
 {	
 	if(__timerManger->_size >= _TIMERPOOL_MAXSIZE)
	{
		SendString("_size to big\r\n");
		return;
	}
	timerout=&__timerManger->_TIMERPOOL[__timerManger->_size];
	__timerManger->_size ++;
	timerout->_id=id;
	timerout->_time=time;
	timerout->_enable=1;
	timerout->_callback = callback;
 }
 void EnableTimer(TIMERMANGER* __timerManger,unsigned char id,unsigned char enable)
 {
 	unsigned char index =0;
	for(index = 0;index<__timerManger->_size;index++)
	{
		if(__timerManger->_TIMERPOOL[index]._id == id)
		{
			__timerManger->_TIMERPOOL[index]._enable = enable;
		}
	}
 }
 void RemoveTimer(TIMERMANGER* __timerManger,unsigned char id)
 {
 	int _index=0;
	//≤È’“
	while(_index<__timerManger->_size)
	{
		if(__timerManger->_TIMERPOOL[_index]._id == id)
		{
			 __timerManger->_size--;
			 break;
		}
		_index++;
	}
	//…ÓøΩ±¥
	for(;_index<__timerManger->_size;_index++)
	{
		__timerManger->_TIMERPOOL[_index]._time=__timerManger->_TIMERPOOL[_index+1]._time;
		__timerManger->_TIMERPOOL[_index]._timeNow=__timerManger->_TIMERPOOL[_index+1]._timeNow;
		__timerManger->_TIMERPOOL[_index]._enable=__timerManger->_TIMERPOOL[_index+1]._enable;
	    __timerManger->_TIMERPOOL[_index]._id=__timerManger->_TIMERPOOL[_index+1]._id;
	    __timerManger->_TIMERPOOL[_index]._callback=__timerManger->_TIMERPOOL[_index+1]._callback;
	}
 }
 void DumpTimerManager(TIMERMANGER* _tmg)
 {
 	  char str[20];
 	  SendString("--------DumpTimerManager-------\r\n");
	  sprintf(str,"size = %d",(int)_tmg->_size);
	   SendString(str);SendString("\r\n");//SendData(_tmg->_size+'0');

	  sprintf(str,"count = %d",_tmg->_count);
	  SendString(str);SendString("\r\n");

	  sprintf(str,"maxcount = %d",_tmg->_maxcount);
	  SendString(str);SendString("\r\n");
	  sprintf(str,"poolsize = %d",(int)sizeof(_tmg->_TIMERPOOL));
	  SendString(str);SendString("\r\n");
	  SendString("--------end-------\r\n");

 }