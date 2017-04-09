#ifndef __WIMIDEVTIMERMANGER_H_
#define __WIMIDEVTIMERMANGER_H_

#include"wimiDevTimerStruct.h"
#define _TIMERPOOL_MAXSIZE 4
#include"global.h"
//��ʱ������ṹ
typedef struct 
{
  unsigned char _size;	//��ʱ���ص�ǰ��С
  unsigned int _count;
  unsigned int _maxcount;
 TIMER _TIMERPOOL[_TIMERPOOL_MAXSIZE];//��ʱ����
}TIMERMANGER;

extern TIMERMANGER _tmg;
//��ʱ�������ʼ��
extern void TimerMangerInit(TIMERMANGER* _timerManger);
//
extern void timerpump(TIMERMANGER* _timerManger);
//��ʱ�ַ���
extern void ClockDistributer(TIMERMANGER* _timerManger);
//��ʱ���ع�����ʱ����
extern void TimerEventDistributer(TIMERMANGER* _timerManger);

//����һ����ʱ��
extern void CreateTimer(TIMERMANGER* _timerManger,unsigned char id,unsigned char _timer,TimerCallBack _callback,TIMER *timer);
//��ͣ/����һ����ʱ��
extern void EnableTimer(TIMERMANGER* __timerManger,unsigned char id,unsigned char enable);
extern void RemoveTimer(TIMERMANGER* __timerManger,unsigned char id);
extern void DumpTimerManager(TIMERMANGER* _timerManger);
#endif