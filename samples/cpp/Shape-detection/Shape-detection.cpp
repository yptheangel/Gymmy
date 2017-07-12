#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

//Mat image; Mat greyImg;
int thresh = 100;
int max_thresh = 255;

int main()
{
	cv::Mat image = cv::imread("shape-detection.png");
	//image = cv::imread("shape-detection.png");
	cv::Mat greyImg;	

	cv::namedWindow("Shape",cv::WINDOW_NORMAL);
	cv::imshow("Shape",image);
	
	cv::cvtColor(image, greyImg, cv::COLOR_BGR2GRAY);
	cv::namedWindow("GreyImg",cv::WINDOW_NORMAL);
	cv::imshow("GreyImg",greyImg);
	
 	//cv::blur( greyImg, greyImg, Size(3,3) );
	
	Canny(greyImg, greyImg, 100, 200, 3);
    	/// Find contours   
    	vector<vector<Point> > contours;
    	vector<Vec4i> hierarchy;
    	RNG rng(12345);
    	cv::findContours( greyImg, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    	
	/// Draw contours
    	Mat drawing = Mat::zeros( greyImg.size(), CV_8UC3 );
    	for( int i = 0; i< contours.size(); i++ )
    	{
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        cv::drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
    } 
	
	imshow("Result window", drawing);
	
	cv::waitKey();
	return 0;
}
