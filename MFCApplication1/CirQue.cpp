#include "init.h"
#include <malloc.h>

// 创建循环队列
CirQue *CreateCirQue(unsigned int size)
{
	CirQue *CQ = (CirQue *)malloc(sizeof(CirQue));
	CQ->grpObj = (SingleObj **)malloc(sizeof(SingleObj *)*size);
	

	for (int i = 0; i < size; i++) {
		CQ->grpObj[i] = (SingleObj *)malloc(sizeof(SingleObj));
		CQ->grpObj[i] = nullptr;
	}
	
	CQ->front = 0;			// 头指针
	CQ->rear = 0;			// 尾指针
	CQ->capArray = size;	// 能够容纳多少物品
	CQ->lengthQue = 0;		// 队列长度

	return CQ;
}
// 插入
int PushBack(CirQue *CQ, SingleObj *obj)
{
	// 队满
	if (isFull(CQ))
		return 0;
	// 插入
	if (CQ->grpObj[CQ->rear] == nullptr) {
		CQ->grpObj[CQ->rear] = obj;
		CQ->rear = (CQ->rear + 1) % CQ->capArray;
		CQ->lengthQue++;
		return 1;
	}
	return 0;
}
// 删除
int Pop(CirQue *CQ)
{
	// 队空
	if (isEmpty(CQ))
		return 0;
	// 删除头元素
	if (CQ->grpObj[CQ->front] != nullptr) {
		int front = CQ->front;
		CQ->front = (CQ->front + 1) % CQ->capArray; // 头指针更新
		free(CQ->grpObj[front]);				// 释放空间
		CQ->grpObj[CQ->front] = nullptr;			
		CQ->lengthQue--;
		return 1;
	}
	
	return 0;
}
// 长度
unsigned int Length(CirQue* CQ)
{
	return CQ->lengthQue;
}
// 空
int isEmpty(CirQue *CQ)
{
	return CQ->front == CQ->rear;
}
// 满
int isFull(CirQue *CQ)
{
	return CQ->front == (CQ->rear + 1) % CQ->capArray;
}

// 遍历
void TraQue(CirQue *CQ, void(*process)(CirQue *, int))
{
	int i = CQ->front;
	while (i != CQ->rear) {
		// 处理第i个
		(*process)(CQ, i);
		// 递进
		i = (i + 1) % CQ->capArray;
	}
}