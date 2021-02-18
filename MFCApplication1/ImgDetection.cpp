#include <opencv2\opencv.hpp>
#include "CirQue.h"
#include "LTDMC.h"
#include "ImgDetection.h"

using namespace cv;
using namespace std;

Mat maskImg[4];
float checksize1;
float checksize2;
float checksize3;
float savesize[4][3] = { {624,212,151},{634,241,172},{0,0,0},{875,332,233} };

extern CMFCApplication1Dlg *dlg1;	// 总类的指针
/***HObject Mat互转***/
HObject Mat2HObject(const cv::Mat& image)
{
	HObject Hobj = HObject();
	int hgt = image.rows;
	int wid = image.cols;
	int i;
	//  CV_8UC3  
	if (image.type() == CV_8UC3)
	{
		vector<cv::Mat> imgchannel;
		split(image, imgchannel);
		cv::Mat imgB = imgchannel[0];
		cv::Mat imgG = imgchannel[1];
		cv::Mat imgR = imgchannel[2];
		uchar* dataR = new uchar[hgt * wid];
		uchar* dataG = new uchar[hgt * wid];
		uchar* dataB = new uchar[hgt * wid];
		for (i = 0; i < hgt; i++)
		{
			memcpy(dataR + wid * i, imgR.data + imgR.step * i, wid);
			memcpy(dataG + wid * i, imgG.data + imgG.step * i, wid);
			memcpy(dataB + wid * i, imgB.data + imgB.step * i, wid);
		}
		GenImage3(&Hobj, "byte", wid, hgt, (Hlong)dataR, (Hlong)dataG, (Hlong)dataB);
		delete[]dataR;
		delete[]dataG;
		delete[]dataB;
		dataR = NULL;
		dataG = NULL;
		dataB = NULL;
	}
	//  CV_8UCU1  
	else if (image.type() == CV_8UC1)
	{
		uchar* data = new uchar[hgt * wid];
		for (i = 0; i < hgt; i++)
			memcpy(data + wid * i, image.data + image.step * i, wid);
		GenImage1(&Hobj, "byte", wid, hgt, (Hlong)data);
		delete[] data;
		data = NULL;
	}
	return Hobj;
}

cv::Mat HObject2Mat(HObject Hobj)
{
	HTuple htCh;
	HString cType;
	cv::Mat Image;
	ConvertImageType(Hobj, &Hobj, "byte");
	CountChannels(Hobj, &htCh);
	Hlong wid = 0;
	Hlong hgt = 0;
	if (htCh[0].I() == 1)
	{
		HImage hImg(Hobj);
		void* ptr = hImg.GetImagePointer1(&cType, &wid, &hgt);//GetImagePointer1(Hobj, &ptr, &cType, &wid, &hgt);
		int W = wid;
		int H = hgt;
		Image.create(H, W, CV_8UC1);
		unsigned char* pdata = static_cast<unsigned char*>(ptr);
		memcpy(Image.data, pdata, W * H);
	}
	else if (htCh[0].I() == 3)
	{
		void* Rptr;
		void* Gptr;
		void* Bptr;
		HImage hImg(Hobj);
		hImg.GetImagePointer3(&Rptr, &Gptr, &Bptr, &cType, &wid, &hgt);
		int W = wid;
		int H = hgt;
		Image.create(H, W, CV_8UC3);
		vector<cv::Mat> VecM(3);
		VecM[0].create(H, W, CV_8UC1);
		VecM[1].create(H, W, CV_8UC1);
		VecM[2].create(H, W, CV_8UC1);
		unsigned char* R = (unsigned char*)Rptr;
		unsigned char* G = (unsigned char*)Gptr;
		unsigned char* B = (unsigned char*)Bptr;
		memcpy(VecM[2].data, R, W * H);
		memcpy(VecM[1].data, G, W * H);
		memcpy(VecM[0].data, B, W * H);
		cv::merge(VecM, Image);
	}
	return Image;
}


//三点求圆心以及半径
pair<Point, float> CircleThru3Dots(Point pt1, Point pt2, Point pt3)
{
	double x1 = pt1.x, x2 = pt2.x, x3 = pt3.x;
	double y1 = pt1.y, y2 = pt2.y, y3 = pt3.y;
	double a = x1 - x2;
	double b = y1 - y2;
	double c = x1 - x3;
	double d = y1 - y3;
	double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
	double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
	double det = b * c - a * d;
	if (fabs(det) < 1e-5)
	{
		float radius = -1;
		cout << "cannot find circle center";
	}

	double x0 = -(d * e - b * f) / det;
	double y0 = -(a * f - c * e) / det;
	float radius = hypot(x1 - x0, y1 - y0);
	Point circle_center = Point(x0, y0);
	return make_pair(circle_center, radius);
}

/***** 求两点间距离*****/
float getDistance(Point pointO, Point pointA)
{
	float distance;
	distance = powf((pointO.x - pointA.x), 2) + powf((pointO.y - pointA.y), 2);
	distance = sqrtf(distance);
	return distance;
}

/****尺寸检测算法****/
imgBack*  sizeCheck(Mat roi_img, Mat maskimg, int id, imgBack *result) {
	Mat cutimg;
    Point startpoint;
    if (id==0) {
        cutimg = roi_img(Range(650, 957), Range(226, 1651));
        startpoint = Point(226, 650);
    }
    else if(id==1) {
        cutimg = roi_img(Range(471, 978), Range(363, 1410));
        startpoint = Point(363, 471);
    }
    else if (id==2) {
        cutimg = roi_img(Range(275, 841), Range(95, 1574));
        startpoint = Point(95, 275);
    }
    else{
        cutimg = roi_img(Range(275, 841), Range(95, 1574));
        startpoint = Point(95, 275);
    }
	
	//模板画布
	Mat dstImg;
	dstImg.create(cutimg.dims, cutimg.size, cutimg.type());
	//模板匹配
	matchTemplate(cutimg, maskimg, dstImg, 0);

	Point minPoint;//
	Point maxPoint;//
	double* minVal = 0;
	double* maxVal = 0;

	//minPoint左上角点 maxPoint右下角点
	minMaxLoc(dstImg, minVal, maxVal, &minPoint, &maxPoint);

	//Point subcircle_center = Point(minPoint.x + maskimg.cols / 2, minPoint.y + maskimg.rows / 2);//模板匹配之后roi的圆心，模糊圆心
	//Point circle_center = Point(circle_center_rough.x - search_area + subcircle_center.x + 1, circle_center_rough.y - search_area + subcircle_center.y + 1);//根据模板的圆心映射到原图像中
	//circle(roi_img, subcircle_center, 2, Scalar(123, 123, 123), 1);
	//rectangle(roi_img, minPoint, Point(minPoint.x + maskimg.cols, minPoint.y + maskimg.rows), Scalar(123, 123, 123), 1, 8);//minPoint代表匹配区域左上角的点
	//circle(roi_img, subcircle_center, 0, Scalar(123, 123, 123), 1);
	Mat gray_img, binaryimg;
	//cvtColor(roi_img, gray_img, COLOR_BGR2GRAY);//转换图片为灰度图
	threshold(roi_img, binaryimg, 0, 255, THRESH_OTSU);//二值化
	//bitwise_not(binaryimg, binaryimg);
	int leftStartX = minPoint.x+ startpoint.x;
    int leftStarty = minPoint.y+ startpoint.y;
	Point leftMidLong, rightMidLong, topMidx, bottomMidy, topMid2x, bottomMid2y;
	for (int i = leftStartX; i < leftStartX + maskimg.cols; i++) {
		int leftmidy = (leftStarty + maskimg.rows / 2);
		if (binaryimg.at<uchar>(Point(i, leftmidy)) == 0) {
			leftMidLong.x = i;
			leftMidLong.y = leftmidy;
			break;
		}
	}
	for (int i = leftStartX + maskimg.cols-1; i > leftStartX; i--) {
		int leftmidy = (leftStarty + maskimg.rows / 2);
		if (binaryimg.at<uchar>(Point(i, leftmidy)) == 0) {
			rightMidLong.x = i;
			rightMidLong.y = leftmidy;
			break;
		}
	}
	for (int i = leftStarty; i < leftStarty + maskimg.rows; i++) {
		int topmidx = (leftStartX + maskimg.cols / 2);
		if (binaryimg.at<uchar>(Point(topmidx, i)) == 0) {
			topMidx.x = topmidx;
			topMidx.y = i;
			break;
		}
	}
	for (int i = leftStarty + maskimg.rows-1; i > leftStarty; i--) {
		int topmidx = (leftStartX + maskimg.cols / 2);
		if (binaryimg.at<uchar>(Point(topmidx, i)) == 0) {
			bottomMidy.x = topmidx;
			bottomMidy.y = i;
			break;
		}
	}
	for (int i = leftStarty; i < leftStarty + maskimg.rows; i++) {
		int topmidx = (leftStartX + maskimg.cols / 5);
		if (binaryimg.at<uchar>(Point(topmidx, i)) == 0) {
			topMid2x.x = topmidx;
			topMid2x.y = i;
			break;
		}
	}
	for (int i = leftStarty + maskimg.rows-1; i > leftStarty; i--) {
		int topmidx = (leftStartX + maskimg.cols / 5);
		if (binaryimg.at<uchar>(Point(topmidx, i)) == 0) {
			bottomMid2y.x = topmidx;
			bottomMid2y.y = i;
			break;
		}
	}
	rectangle(roi_img, Point(leftStartX , leftStarty), Point(leftStartX + maskimg.cols, leftStarty + maskimg.rows), Scalar(123, 123, 123), 5, 8);
	line(roi_img, leftMidLong, rightMidLong, Scalar(33, 33, 133), 5);
	line(roi_img, topMidx, bottomMidy, Scalar(33, 33, 133), 5);
	line(roi_img, topMid2x, bottomMid2y, Scalar(33, 33, 133), 5);
	

	
	//int pointpixel = roi_img.at<uchar>(leftMidLong);
	//namedWindow("OUTPUT", WINDOW_KEEPRATIO);
	//imshow("OUTPUT", roi_img);
	//waitKey(0);
	
			checksize1 = savesize[id][0];
			checksize2 = savesize[id][1];
			checksize3 = savesize[id][2];
	
	float length = getDistance(leftMidLong, rightMidLong);
	float width1 = getDistance(topMidx, bottomMidy);
	float width2 = getDistance(topMid2x, bottomMid2y);
	result->resultType = OK;
	String showmsg="OK";
	if (abs(checksize1 - length) > 20 || abs(checksize2 - width1) > 20 || abs(checksize3 - width2) >20) {
		result->resultType = NG;
		showmsg="NG";
	}
	rectangle(roi_img, Point(100,0), Point(500,300), Scalar(255, 255, 255), -1, 4);
	 putText(roi_img,showmsg,Point(100,200),FONT_HERSHEY_SIMPLEX,10,CV_RGB(0,0,0),15);
	//putText(roi_img,to_string(static_cast<long long>(checksize1)),Point(100,200),FONT_HERSHEY_SIMPLEX,5,CV_RGB(0,0,0),10);
	//putText(roi_img,to_string(static_cast<long long>(length)),Point(100,300),FONT_HERSHEY_SIMPLEX,5,CV_RGB(0,0,0),10);
	//putText(roi_img,to_string(static_cast<long long>(getDistance(topMidx, bottomMidy))),Point(100,300),FONT_HERSHEY_SIMPLEX,5,CV_RGB(0,0,0),10);
	//putText(roi_img,to_string(static_cast<long long>(getDistance(topMid2x, bottomMid2y))),Point(100,400),FONT_HERSHEY_SIMPLEX,5,CV_RGB(0,0,0),10);

	HObject trunBackImg = Mat2HObject(roi_img);
	result->img[id] = &trunBackImg;
	// 显示图片
	dlg1->showPic(trunBackImg, id);
	return result;
}

/****尺寸检测算法****/
imgBack * imageProcessing(HObject &img, int i)
{
	imgBack *result = (imgBack *)malloc(sizeof(imgBack));
	Mat CvImg;
	CvImg = HObject2Mat(img);
	result = sizeCheck(CvImg, maskImg[i], i, result);
	if (i == 2) {
		result->resultType = OK;
	}
	return result;
}