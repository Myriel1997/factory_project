#ifndef OBJ_H
#define OBJ_H

#include "init.h"
#include "HObject.h"

class CirQue;// ǰ������

class SingleObj {
public:
	SingleObj();
	~SingleObj() {};
public:
	HObject *img[CAMNUM];	// ͼƬָ��
	long position;			// ��Ʒ��ǰλ��
	long infrEncode;		// ��Ʒ��������ʱ��������ֵ
	int res[CAMNUM];		// ���������Ƭ��ý����0-NG��1-UN��-1-OK
	int finalRes;			// ��Ʒ�������0-NG��1-UN��-1-OK
	bool isCheckEnding[CAMNUM];		// ��¼�Ƿ�����ϣ�0-δ��ϣ�1-���
	bool camGot[CAMNUM];	// ��¼������Ѿ��Ը���Ʒ�������0-�Ĺ�1-δ��
	bool isChecking;		// �Ƿ����Ʒ���ڼ��
private:

};


void ObjPopToQue(CirQue* CQ);
void PicProcess(CirQue* CQ, int i);
void CamProcess(CirQue* CQ, int i);
void SpoutOKProcess(CirQue* CQ);
void SpoutNGProcess(CirQue* CQ);

//typedef struct obj
//{
//	HObject *img[CAMNUM];	// ͼƬָ��
//	long position;			// ��Ʒ��ǰλ��
//	long infrEncode;		// ��Ʒ��������ʱ��������ֵ
//	int res[CAMNUM];		// ���������Ƭ��ý����0-NG��1-UN��-1-OK
//	int finalRes;			// ��Ʒ�������0-NG��1-UN��-1-OK
//	bool isCheckEnding[CAMNUM];		// ��¼�Ƿ�����ϣ�0-δ��ϣ�1-���
//	bool camGot[CAMNUM];	// ��¼������Ѿ��Ը���Ʒ�������0-�Ĺ�1-δ��
//	bool isChecking;		// �Ƿ����Ʒ���ڼ��
//}SingleObj;

//SingleObj *CreateObj();

#endif // !OBJ_H
