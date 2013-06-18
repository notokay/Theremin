
#include <cstdio>
#include <string>
#include <opencv/highgui.h>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char ** argv)
{
	int CalibCircleRadius = 50;
	
	// Load the image from file
	Mat SignalImage = imread("turret.png", CV_LOAD_IMAGE_UNCHANGED);
	if(SignalImage.empty())
	{
		cout << "failed to load signal image" << endl;
		return -1;
	}
	
	//Draw the Circle
	Mat Circle = SignalImage.clone();
	Point imagecenter = Point(SignalImage.cols/2, SignalImage.rows/2);
	Scalar circlecolor = CV_RGB(255,0,0);
	circle(Circle,imagecenter, CalibCircleRadius, circlecolor, 8, 0);
	//Show the Signal Image with Circle
	namedWindow("SignalImageCircle", CV_WINDOW_AUTOSIZE);
	imshow("SignalImageCircle", Circle);
	
	
	//Draw the Rectangle
	Mat Rectangle = SignalImage.clone();
	Point RectPt1 = Point((SignalImage.cols)/2 - CalibCircleRadius, (SignalImage.rows)/2 - CalibCircleRadius);
	Point RectPt2 = Point((SignalImage.cols)/2 + CalibCircleRadius, (SignalImage.rows)/2 + CalibCircleRadius);
	rectangle(Rectangle, RectPt1, RectPt2, circlecolor, 1, 8, 0);
	//Show the Signal Image with Rectangle
	namedWindow("SignalImageRectangle", CV_WINDOW_AUTOSIZE);
	imshow("SignalImageRectangle", Rectangle);
	
	//Crop the Signal Image to the rectangle
	Mat croppedROI = SignalImage(Rect(RectPt1,RectPt2));
 	namedWindow("CroppedROI", CV_WINDOW_AUTOSIZE);
	imshow("CroppedROI", croppedROI);
	waitKey(0);

		return 0;
	}
