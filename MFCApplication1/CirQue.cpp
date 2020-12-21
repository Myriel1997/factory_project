#include "init.h"
#include <malloc.h>

// ����ѭ������
CirQue *CreateCirQue(unsigned int size)
{
	CirQue *CQ = (CirQue *)malloc(sizeof(CirQue));
	CQ->grpObj = (SingleObj **)malloc(sizeof(SingleObj *)*size);
	

	for (int i = 0; i < size; i++) {
		CQ->grpObj[i] = (SingleObj *)malloc(sizeof(SingleObj));
		CQ->grpObj[i] = nullptr;
	}
	
	CQ->front = 0;			// ͷָ��
	CQ->rear = 0;			// βָ��
	CQ->capArray = size;	// �ܹ����ɶ�����Ʒ
	CQ->lengthQue = 0;		// ���г���

	return CQ;
}
// ����
int PushBack(CirQue *CQ, SingleObj *obj)
{
	// ����
	if (isFull(CQ))
		return 0;
	// ����
	if (CQ->grpObj[CQ->rear] == nullptr) {
		CQ->grpObj[CQ->rear] = obj;
		CQ->rear = (CQ->rear + 1) % CQ->capArray;
		CQ->lengthQue++;
		return 1;
	}
	return 0;
}
// ɾ��
int Pop(CirQue *CQ)
{
	// �ӿ�
	if (isEmpty(CQ))
		return 0;
	// ɾ��ͷԪ��
	if (CQ->grpObj[CQ->front] != nullptr) {
		int front = CQ->front;
		CQ->front = (CQ->front + 1) % CQ->capArray; // ͷָ�����
		free(CQ->grpObj[front]);				// �ͷſռ�
		CQ->grpObj[CQ->front] = nullptr;			
		CQ->lengthQue--;
		return 1;
	}
	
	return 0;
}
// ����
unsigned int Length(CirQue* CQ)
{
	return CQ->lengthQue;
}
// ��
int isEmpty(CirQue *CQ)
{
	return CQ->front == CQ->rear;
}
// ��
int isFull(CirQue *CQ)
{
	return CQ->front == (CQ->rear + 1) % CQ->capArray;
}

// ����
void TraQue(CirQue *CQ, void(*process)(CirQue *, int))
{
	int i = CQ->front;
	while (i != CQ->rear) {
		// �����i��
		(*process)(CQ, i);
		// �ݽ�
		i = (i + 1) % CQ->capArray;
	}
}