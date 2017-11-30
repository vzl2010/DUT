#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <calib3d.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	//Mat img = imread("1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img = imread("7.bmp", CV_LOAD_IMAGE_COLOR);
	if (img.empty())
		return -1;
	Mat gray;
	cvtColor(img, gray, CV_RGB2GRAY);
	//threshold(gray, gray, 0, 255, CV_THRESH_OTSU);
	imshow("gray", gray);
	vector<Point2f>corners;
	bool ret = findChessboardCorners(gray, Size(5, 7), corners, CALIB_CB_ADAPTIVE_THRESH|CALIB_CB_NORMALIZE_IMAGE);
	//TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS,40,0.1);
	//cornerSubPix(gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);
	drawChessboardCorners(img, cv::Size(5,7), corners, ret);
	cout << corners << endl;
	namedWindow("lena", CV_WINDOW_AUTOSIZE);
	imshow("lena", img);
	waitKey(0);
	return 0;
}
