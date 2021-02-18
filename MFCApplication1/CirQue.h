#ifndef CIR_QUE_H
#define CIR_QUE_H

#include "obj.h"

class SingleObj;

class CirQue
{
public :
	SingleObj **grpObj;			// 物品数组
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
	unsigned int capArray;	// 物品容量，指最多可以放多少东西进队列
	unsigned int lengthQue;	// 队列长度，当前队列长度
};


#endif // !CIR_QUE_H

