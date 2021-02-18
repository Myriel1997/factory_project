#ifndef CIR_QUE_H
#define CIR_QUE_H

#include "obj.h"

class SingleObj;

class CirQue
{
public :
	SingleObj **grpObj;			// ��Ʒ����
public:
	CirQue(unsigned int size);
	~CirQue();
	int PushBack(SingleObj *obj);
	int Pop();
	unsigned int GetLength();
	int isEmpty();
	int isFull();
	SingleObj *CirQue::GetFront();
	void TraQue(void (* process)(CirQue *, int ));
	
private:
	int front;
	int rear;
	unsigned int capArray;	// ��Ʒ������ָ�����ԷŶ��ٶ���������
	unsigned int lengthQue;	// ���г��ȣ���ǰ���г���
};


#endif // !CIR_QUE_H

