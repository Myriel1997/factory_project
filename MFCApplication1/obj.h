#ifndef OBJ_H
#define OBJ_H

#include "CirQue.h"
#include "DHGrabExport.h"

typedef struct CircuitQueue CirQue;// ǰ������

typedef struct obj
{
	HObject *img[CAMNUM];	// ͼƬָ��
	long position;			// ��Ʒ��ǰλ��
	long infrEncode;		// ��Ʒ��������ʱ��������ֵ
	int res[CAMNUM];		// ���������Ƭ��ý����0-NG��1-UN��-1-OK
	int finalRes;			// ��Ʒ�������0-NG��1-UN��-1-OK
	bool isCheckEnding;		// ��¼�Ƿ�����ϣ�0-δ��ϣ�1-���
	bool camGot[CAMNUM];	// ��¼������Ѿ��Ը���Ʒ�������0-�Ĺ�1-δ��
}SingleObj;

SingleObj *CreateObj();
void CamProcess(CirQue* CQ, int i);
void SpoutOKProcess(CirQue* CQ, int i);
void SpoutNGProcess(CirQue* CQ, int i);

#endif // !OBJ_H
