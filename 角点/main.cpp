#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#define corners_window "corners_window"
#define  source_window "source_window"
Mat src, src_gray, dst_norm_scaled;
int thresh=255, maxCorners=80;
int max_thresh = 255, maxTrackbar = 200;
void cornerHarris_demo(int, void*)
{
	src = imread("7.bmp");
	//src = imread("1.jpg");
	cvtColor(src, src_gray, CV_RGB2GRAY);
	Mat dst, dst_norm;
	dst = Mat::zeros(src.size(), CV_32FC1);
	/// Detector parameters  
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;
	/// Detecting corners  
	cornerHarris(src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT);
	/// Normalizing  
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled);
	/// Drawing a circle around corners  
	for (int j = 0; j < dst_norm.rows; j++)
	{
		for (int i = 0; i < dst_norm.cols; i++)
		{
			if ((int)dst_norm.at<float>(j, i) > thresh)
			{
				circle(dst_norm_scaled, Point(i, j), 5, Scalar(0), 2, 8, 0);
				circle(src, Point(i, j), 5, Scalar(255, 0, 0), -1, 8, 0);
			}
		}
	}
	/// Showing the result  
	imshow(corners_window, dst_norm_scaled);
	imshow(source_window, src);
}
void cornerShiTomasi_demo(int, void*)
{
	src = imread("7.bmp");
	//src = imread("1.jpg");
	cvtColor(src, src_gray, CV_RGB2GRAY);
	if (maxCorners < 1) { maxCorners = 1; }
	/// Parameters for Shi-Tomasi algorithm  
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	/// Copy the source image  
	Mat cormat;
	/// Apply corner detection :Determines strong corners on an image.  
	goodFeaturesToTrack(src_gray,
		corners,
		maxCorners,
		qualityLevel,
		minDistance,
		Mat(),
		blockSize,
		useHarrisDetector,
		k);
	/// Draw corners detected  
	for (int i = 0; i < corners.size(); i++){
		circle(dst_norm_scaled, corners[i], 5, Scalar(255), 2, 8, 0);
		circle(src, corners[i], 4, Scalar(0, 255, 0), 2, 8, 0);
	}
	cout << corners.size() << endl;
	/// Show what you got  
	imshow(corners_window, dst_norm_scaled);
	imshow(source_window, src);
	imwrite("jiegou.bmp", src);
}
int main(int argc, char *argv[])
{
	src = imread("7.bmp");
	//src = imread("1.jpg");
	if (src.empty())
		return -1;
	
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);
	createTrackbar("Max  corners:", source_window, &maxCorners, maxTrackbar, cornerShiTomasi_demo);

	namedWindow(corners_window, CV_WINDOW_AUTOSIZE);
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	cornerHarris_demo(0, 0);
	//cornerShiTomasi_demo(0, 0);
	Mat img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	if (img.empty())
		return -1;
	namedWindow("lena", CV_WINDOW_AUTOSIZE);
	imshow("lena", img);
	waitKey(0);
	return 0;
}
