#ifndef CIR_QUE_H
#define CIR_QUE_H

#include "obj.h"

typedef struct obj singleObj;// ǰ������

typedef struct CircuitQueue
{
	SingleObj **grpObj;			// ��Ʒ����

	int front;
	int rear;
	unsigned int capArray;	// ��Ʒ������ָ�����ԷŶ��ٶ���������
	unsigned int lengthQue;	// ���г��ȣ���ǰ���г���
}CirQue;

CirQue *CreateCirQue(unsigned int size);
int PushBack(CirQue *CQ, SingleObj *obj);
int Pop(CirQue *CQ);
unsigned int Length(CirQue* CQ);
int isEmpty(CirQue *CQ);
int isFull(CirQue *CQ);
void TraQue(CirQue *CQ, void (* process)(CirQue *, int ));

#endif // !CIR_QUE_H

