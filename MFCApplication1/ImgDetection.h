#ifndef IMG_DETECTION_H
#define IMG_DETECTION_H

#include "HObject.h"

typedef struct sImgBack
{
	int resultType;			// ���
	int flawType;			// ȱ������
	HObject *img[4];
}imgBack;

imgBack * imageProcessing(HObject &img, int i);




#endif // !IMG_DETECTION_H

