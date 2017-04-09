#ifndef __WIMIDEVTIMERSTRUCT_H_
#define __WIMIDEVTIMERSTRUCT_H_


	typedef  void (*TimerCallBack)();

	typedef struct{
			unsigned char _enable;
			unsigned char _id;
	  		unsigned char _time;
			unsigned char _timeNow;
			TimerCallBack _callback;
	}TIMER;

#endif