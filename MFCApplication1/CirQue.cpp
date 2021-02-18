#include "CirQue.h"
#include "obj.h"
#include "Init.h"

CirQue::CirQue(unsigned int size)
{

	//CirQue *CQ = (CirQue *)malloc(sizeof(CirQue));			// 赋予结构体CirQue空间
	//grpObj = (SingleObj **)malloc(sizeof(SingleObj *)*size);	// 赋予数组grpObj空间
	grpObj = (SingleObj **)new SingleObj*[size];

	// 清空队列
	for (int i = 0; i < size; i++) {
		//CQ->grpObj[i] = (SingleObj *)malloc(sizeof(SingleObj));
		grpObj[i] = nullptr;
	}
	
	front = 0;			// 头指针
	rear = 0;			// 尾指针
	capArray = size;	// 能够容纳多少物品
	lengthQue = 0;		// 队列长度
}

CirQue::~CirQue()
{
	if (grpObj != NULL) {
		for (int i = 0; i < QUESIZE; i++) {
			delete grpObj[i];
		}
		delete[] grpObj;
	}
}

// 插入
int CirQue::PushBack(SingleObj *obj)
{
	// 队满
	if (this->isFull())
		return 0;
	// 插入
	if (grpObj[rear] == nullptr) {
		grpObj[rear] = obj;
		rear = (rear + 1) % capArray;
		lengthQue++;
		return 1;
	}
	return 0;
}
// 删除
int CirQue::Pop()
{
	// 队空
	if (isEmpty())
		return 0;
	// 删除头元素
	if (grpObj[front] != nullptr) {
		int tempFront = front;
		front = (front + 1) % capArray; // 头指针更新
		free(grpObj[tempFront]);		// 释放空间
		grpObj[tempFront] = nullptr;			
		lengthQue--;
		return 1;
	}
	
	return 0;
}
// 长度
unsigned int CirQue::GetLength()
{
	return lengthQue;
}
// 空
int CirQue::isEmpty()
{
	return front == rear;
}
// 满
int CirQue::isFull()
{
	return front == (rear + 1) % capArray;
}

// 遍历
void CirQue::TraQue(void(*process)(CirQue *, int))
{
	int i = front;
	while (i != rear) {
		// 处理第i个
		(*process)(this, i);
		// 递进
		i = (i + 1) % capArray;
	}
}

// 头对象
SingleObj *CirQue::GetFront()
{
	return grpObj[front];
}

// 创建循环队列
//CirQue *CreateCirQue(unsigned int size)
//{
//	CirQue *CQ = (CirQue *)malloc(sizeof(CirQue));					// 赋予结构体CirQue空间
//	CQ->grpObj = (SingleObj **)malloc(sizeof(SingleObj *)*size);	// 
//
//	// 将整个队列都赋值空间
//	for (int i = 0; i < size; i++) {
//		CQ->grpObj[i] = (SingleObj *)malloc(sizeof(SingleObj));
//		CQ->grpObj[i] = nullptr;
//	}
//	
//	CQ->front = 0;			// 头指针
//	CQ->rear = 0;			// 尾指针
//	CQ->capArray = size;	// 能够容纳多少物品
//	CQ->lengthQue = 0;		// 队列长度
//
//	return CQ;
//}