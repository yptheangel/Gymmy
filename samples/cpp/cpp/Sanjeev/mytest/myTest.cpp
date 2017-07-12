/*
* File:   myTest.cpp
* Author: Sanjeev
*
* Created on 3 JANUARY, 2017, 9:57 AM
*/

#include <opencv2/imgcodecs/imgcodecs.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat cameraFrame; 
Mat im_gray;
int thresh = 100;
int max_thresh = 200;
RNG rng(12345);

void thresh_callback(int, void* );
 
int main() 
{
	VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.
	//namedWindow( "Your cam", WINDOW_AUTOSIZE ); 	

	/*
	if (!stream1.isOpened()) { //check if video device has been initialised
	cout << "cannot open camera";
	}
	*/

 
	//unconditional loop
	//while (true) 
	while(stream1.isOpened()){
		
		if(!stream1.read(cameraFrame))
		break;					
		imshow("Your cam", cameraFrame); // show original image

		/*
		// show black and white image
		cvtColor( cameraFrame, im_gray, COLOR_BGR2GRAY );
  		blur( im_gray, im_gray, Size(9,9) );
		const char* source_window = "B&W Cam";
  		namedWindow( source_window, WINDOW_AUTOSIZE );
  		imshow( source_window, im_gray );
		

		createTrackbar( " Threshold:", "Source", &thresh, max_thresh, thresh_callback );
		thresh_callback( 0, 0 );
		*/
		
		if (waitKey(33)== 27)		
		//if (waitKey(30) >= 0) 
		break;
		
		
	}
	
	
	return 0;
}

void thresh_callback(int, void* ){
  Mat threshold_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  threshold( im_gray, threshold_output, thresh, max_thresh, THRESH_BINARY );
  findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
  vector<vector<Point> > contours_poly( contours.size() );
  vector<Rect> boundRect( contours.size() );
  vector<Point2f>center( contours.size() );
  vector<float>radius( contours.size() );
  for( size_t i = 0; i < contours.size(); i++ )
  {
    approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
    boundRect[i] = boundingRect( Mat(contours_poly[i]) );
    minEnclosingCircle( contours_poly[i], center[i], radius[i] );
  }
  Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );

  for( size_t i = 0; i< contours.size(); i++ )
  {
    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    drawContours( drawing, contours_poly, (int)i, Scalar(255,0,0), 1, 8, vector<Vec4i>(), 0, Point() );
    rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
    circle( drawing, center[i], (int)radius[i], Scalar(0,255,0), 2, 8, 0 );

  }

  namedWindow( "Contours", WINDOW_NORMAL );
  imshow( "Contours", drawing );
}
