#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
        VideoCapture capture(0);

        while(capture.isOpened()){
                
	Mat frameOri;
	Mat frameGray;
	Mat frameBlur;
	Mat frameCanny;

        if(!capture.read(frameOri))
        	break;

	cvtColor(frameOri, frameGray, CV_BGR2GRAY);
	GaussianBlur(frameGray, frameBlur, Size(5,5),1.5);
	Canny(frameBlur,frameCanny,100,200);

	namedWindow("FrameOri",CV_WINDOW_NORMAL);
	namedWindow("FrameGray",CV_WINDOW_NORMAL);
	namedWindow("FrameBlur",CV_WINDOW_NORMAL);
	namedWindow("FrameCanny",CV_WINDOW_NORMAL);

	imshow("FrameOri",frameOri);
	imshow("FrameGray",frameGray);
	imshow("FrameBlur",frameBlur);
	imshow("FrameCanny",frameCanny);

        if (waitKey(33)== 27)
        	break;
        }
        return 0;
}
 
