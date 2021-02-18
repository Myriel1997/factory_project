#ifndef IMG_DETECTION_H
#define IMG_DETECTION_H

#include "HObject.h"

typedef struct sImgBack
{
	int resultType;			// 结果
	int flawType;			// 缺陷类型
	HObject *img[4];
}imgBack;

imgBack * imageProcessing(HObject &img, int i);




#endif // !IMG_DETECTION_H

