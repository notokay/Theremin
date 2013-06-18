
#include <cstdio>
#include <string>
#include <opencv/highgui.h>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char ** argv)
{
	
	IplImage * SignalImage = 0;
	IplImage * Circle = 0;
	IplImage * Rectangle = 0;
	//IplImage * Rectangle[10];
	int CalibCircleRadius = 40;
	// Load the image from file
	SignalImage = cvLoadImage("turret.png", CV_LOAD_IMAGE_UNCHANGED);
	if(!SignalImage){
		cout << "failed to load Signal Image" << endl;
		return -1;
	}
	
	Circle = cvCloneImage(SignalImage);
	//Circle = cvCreateImage(cvSize(SignalImage->width, SignalImage->height), SignalImage->depth, SignalImage->nChannels);
	//Draw the Circle
	Circle = cvCloneImage(SignalImage);
	CvPoint imagecenter = {SignalImage->width/2, SignalImage->height/2};
	CvScalar circlecolor = CV_RGB(255,155,122);
	cvCircle(Circle,imagecenter, CalibCircleRadius, circlecolor, 8, 0); 
	//Save the Signal Image with Circle
	if(!cvSaveImage("SignalCircle.jpg", Circle)){
		cout << "Could not save Circle" << endl;
	} else cout << "Circle Saved Successfully" << endl;
	
	//Draw Calibration Rectangle
	Rectangle = cvCloneImage(SignalImage);
	CvPoint RectPt1 = {((SignalImage->width)/2 - CalibCircleRadius), ((SignalImage->height)/2 - CalibCircleRadius)};
	CvPoint RectPt2 = {((SignalImage->width)/2 + CalibCircleRadius), ((SignalImage->height)/2 + CalibCircleRadius)};
	cvRectangle(Rectangle, RectPt1, RectPt2, circlecolor, 1, 8, 0);
	//Save the Signal Image with Rectangle
	if(!cvSaveImage("SignalRectangle.jpg", Rectangle)){
		cout << "Could not save Rectangle" << endl;
	} else cout << "Rectangle Saved Successfully" << endl;
	
	//Set the Region of Interest using Rectangle
	IplImage *SignalImageCopy = cvCloneImage(SignalImage);
	IplImage *ROICropped = cvCreateImage(cvSize(CalibCircleRadius*2, CalibCircleRadius*2), SignalImage->depth, SignalImage->nChannels);
	cvSetImageROI(SignalImageCopy, cvRect(SignalImage->width/2 - CalibCircleRadius,SignalImage->height/2 - CalibCircleRadius,CalibCircleRadius*2, CalibCircleRadius*2));
	cvCopy(SignalImageCopy,ROICropped);
	//Save the Cropped ROI Image
	if(!cvSaveImage("ROICropped.jpg", ROICropped)){
		cout << "Could not save Rectangle" << endl;
	} else cout << "ROICropped Saved Successfully" << endl;

	//obtainHistogram();
		//handRect = detectHand(pVideoFrame);
		
		//show the display image
		//	cvShowImage("Video", pImgToChange);
		
		//exit loop when a finger region is detected
		//if(handRect) break;
		
		//	if( (char)27 == cvWaitKey(1)) exit(0);
		
		// Using signals obtained from calibratioin signal to pinpoint and plot position of thing in a grid
		// initiate tracking... use template matching or histogram comparison to search around a given area for the shape found in calibration signal
		
		// Terminate video capture and free capture resources
	   cvReleaseImage(&SignalImage);
	   cvReleaseImage(&Circle);
	   cvReleaseImage(&Rectangle);
	   cvReleaseImage(&SignalImageCopy);
	   cvReleaseImage(&ROICropped);
		return 0;
	}
