#ifndef CIR_QUE_H
#define CIR_QUE_H

#include "obj.h"

typedef struct obj singleObj;// 前向声明

typedef struct CircuitQueue
{
	SingleObj **grpObj;			// 物品数组

	int front;
	int rear;
	unsigned int capArray;	// 物品容量，指最多可以放多少东西进队列
	unsigned int lengthQue;	// 队列长度，当前队列长度
}CirQue;

CirQue *CreateCirQue(unsigned int size);
int PushBack(CirQue *CQ, SingleObj *obj);
int Pop(CirQue *CQ);
unsigned int Length(CirQue* CQ);
int isEmpty(CirQue *CQ);
int isFull(CirQue *CQ);
void TraQue(CirQue *CQ, void (* process)(CirQue *, int ));

#endif // !CIR_QUE_H

