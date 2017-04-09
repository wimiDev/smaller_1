#ifndef __WIMIDEVTIMERMANGER_H_
#define __WIMIDEVTIMERMANGER_H_

#include"wimiDevTimerStruct.h"
#define _TIMERPOOL_MAXSIZE 4
#include"global.h"
//定时器管理结构
typedef struct 
{
  unsigned char _size;	//定时器池当前大小
  unsigned int _count;
  unsigned int _maxcount;
 TIMER _TIMERPOOL[_TIMERPOOL_MAXSIZE];//定时器池
}TIMERMANGER;

extern TIMERMANGER _tmg;
//定时器管理初始化
extern void TimerMangerInit(TIMERMANGER* _timerManger);
//
extern void timerpump(TIMERMANGER* _timerManger);
//定时分发器
extern void ClockDistributer(TIMERMANGER* _timerManger);
//定时器池管理，定时触发
extern void TimerEventDistributer(TIMERMANGER* _timerManger);

//创建一个定时器
extern void CreateTimer(TIMERMANGER* _timerManger,unsigned char id,unsigned char _timer,TimerCallBack _callback,TIMER *timer);
//暂停/激活一个定时器
extern void EnableTimer(TIMERMANGER* __timerManger,unsigned char id,unsigned char enable);
extern void RemoveTimer(TIMERMANGER* __timerManger,unsigned char id);
extern void DumpTimerManager(TIMERMANGER* _timerManger);
#endif