#include "CirQue.h"
#include "obj.h"
#include "Init.h"

CirQue::CirQue(unsigned int size)
{

	//CirQue *CQ = (CirQue *)malloc(sizeof(CirQue));			// ����ṹ��CirQue�ռ�
	//grpObj = (SingleObj **)malloc(sizeof(SingleObj *)*size);	// ��������grpObj�ռ�
	grpObj = (SingleObj **)new SingleObj*[size];

	// ��ն���
	for (int i = 0; i < size; i++) {
		//CQ->grpObj[i] = (SingleObj *)malloc(sizeof(SingleObj));
		grpObj[i] = nullptr;
	}
	
	front = 0;			// ͷָ��
	rear = 0;			// βָ��
	capArray = size;	// �ܹ����ɶ�����Ʒ
	lengthQue = 0;		// ���г���
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

// ����
int CirQue::PushBack(SingleObj *obj)
{
	// ����
	if (this->isFull())
		return 0;
	// ����
	if (grpObj[rear] == nullptr) {
		grpObj[rear] = obj;
		rear = (rear + 1) % capArray;
		lengthQue++;
		return 1;
	}
	return 0;
}
// ɾ��
int CirQue::Pop()
{
	// �ӿ�
	if (isEmpty())
		return 0;
	// ɾ��ͷԪ��
	if (grpObj[front] != nullptr) {
		int tempFront = front;
		front = (front + 1) % capArray; // ͷָ�����
		free(grpObj[tempFront]);		// �ͷſռ�
		grpObj[tempFront] = nullptr;			
		lengthQue--;
		return 1;
	}
	
	return 0;
}
// ����
unsigned int CirQue::GetLength()
{
	return lengthQue;
}
// ��
int CirQue::isEmpty()
{
	return front == rear;
}
// ��
int CirQue::isFull()
{
	return front == (rear + 1) % capArray;
}

// ����
void CirQue::TraQue(void(*process)(CirQue *, int))
{
	int i = front;
	while (i != rear) {
		// �����i��
		(*process)(this, i);
		// �ݽ�
		i = (i + 1) % capArray;
	}
}

// ͷ����
SingleObj *CirQue::GetFront()
{
	return grpObj[front];
}

// ����ѭ������
//CirQue *CreateCirQue(unsigned int size)
//{
//	CirQue *CQ = (CirQue *)malloc(sizeof(CirQue));					// ����ṹ��CirQue�ռ�
//	CQ->grpObj = (SingleObj **)malloc(sizeof(SingleObj *)*size);	// 
//
//	// ���������ж���ֵ�ռ�
//	for (int i = 0; i < size; i++) {
//		CQ->grpObj[i] = (SingleObj *)malloc(sizeof(SingleObj));
//		CQ->grpObj[i] = nullptr;
//	}
//	
//	CQ->front = 0;			// ͷָ��
//	CQ->rear = 0;			// βָ��
//	CQ->capArray = size;	// �ܹ����ɶ�����Ʒ
//	CQ->lengthQue = 0;		// ���г���
//
//	return CQ;
//}