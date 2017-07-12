#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat ImgOri;
	Mat ImgGray;
	Mat ImgBlur;
	Mat ImgCanny;

        VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.

	ImgOri = imread("./potato.png");
	if (ImgOri.empty()){
		cout<< "error: image file not found\n!";
		return(0);
	}
	cvtColor(ImgOri, ImgGray, CV_BGR2GRAY);
	GaussianBlur(ImgGray, ImgBlur, Size(5,5),1.5);
	Canny(ImgBlur,ImgCanny,100,200);

	namedWindow("ImgOri",CV_WINDOW_NORMAL);
	namedWindow("ImgGray",CV_WINDOW_NORMAL);
	namedWindow("ImgBlur",CV_WINDOW_NORMAL);
	namedWindow("ImgCanny",CV_WINDOW_NORMAL);

	imshow("ImgOri",ImgOri);
	imshow("ImgGray",ImgGray);
	imshow("ImgBlur",ImgBlur);
	imshow("ImgCanny",ImgCanny);

/*        if (!stream1.isOpened()) { //check if video device has been initialised
        cout << "cannot open camera";
        }

//unconditional loop
        //while (true) 
        while(stream1.isOpened())
                {
                Mat cameraFrame;
                if(!stream1.read(cameraFrame))
                        break;
                imshow("cam", cameraFrame);
                if (waitKey(33)== 27)
                break;
                }
                return 0;
}
 *//
	waitKey(0);
	return(0);
}      
