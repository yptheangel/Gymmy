
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/video.hpp>
using namespace cv;
using namespace std;

Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor

// Define colors
Scalar colorB = Scalar(255, 0, 0);
Scalar colorG = Scalar(0, 255, 0);
Scalar colorR = Scalar(0, 0, 255);

// Init boolean
bool isAboveLine = false; 

// Init integer
int counter = 0;

// Init point
Point prevCenter; 
Point c1;
Point c2;

Mat frame, blurred, copyFrame, test;

string ToString(double val);
void checkIfCrossedLine(Point &center);

// Detect Skin from YCrCb
Mat DetectYCrCb(Mat img, Scalar min, Scalar max) {
    Mat skin;
    cvtColor(img, skin, cv::COLOR_BGR2YCrCb);
    inRange(skin, min, max, skin);
    Mat rect_12 = getStructuringElement(cv::MORPH_RECT, Size(12,12) , Point(6,6));
    erode(skin, skin, rect_12,Point(),1);
    Mat rect_6 = getStructuringElement(cv::MORPH_RECT, Size(6,6) , Point(3,3));
    dilate(skin,skin,rect_6,Point(),2);
    return skin;    
}

void DetectContour(Mat img){
    Mat drawing = Mat::zeros( img.size(), CV_8UC3 );
    Mat defect_test = Mat::zeros( img.size(), CV_8UC3 );

    vector<vector<Point> > contours;
    vector<vector<Point> > bigContours;
    vector<Vec4i> hierarchy;

    findContours(img,contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE, Point());

	
    if(contours.size()>0)
    {
        vector<std::vector<int> >hull( contours.size() );
        vector<vector<Vec4i> > convDef(contours.size() );
        vector<vector<Point> > hull_points(contours.size());
        vector<vector<Point> > defect_points(contours.size());
	vector<Rect> boundRect( contours.size() );

	//cout << "New Image:" << endl;
	//cout << "---------------------START--------------------" << endl;
        for( int i = 0; i < contours.size(); i++ )
        {
		
		boundRect[i] = boundingRect( Mat(contours[i]) ); // generate bounding rectangle around contours
		double size = contours[i].size(); // get size of each contour
		double b = boundRect[i].width; // get bounding rectangle width
		double c = boundRect[i].height; // get bounding rectangle height
		double area_rect = b*c; // get area of bounding rectangle
		
		// size >= 100 && area_rect >= 15000 && area_rect <= 40000 && b >= c + 50 && b < 250
		if(size >= 100 && area_rect >= 15000 && b >= c + 50){
			
			convexHull( contours[i], hull[i], false );
                	convexityDefects( contours[i],hull[i], convDef[i]);
			double hull_size = hull[i].size(); // get size of convex hull array
			//cout << convDef[i].size() << endl;
			for(int k=0;k<hull[i].size();k++) {           
                    		int ind=hull[i][k];
                    		hull_points[i].push_back(contours[i][ind]);
                	}
			
                	for(int k=0;k<convDef[i].size();k++) {          
                    		if(convDef[i][k][3] <= 20000 && convDef[i][k][3] > 3000) // filter defects by depth
                    		{
                    			int ind_0=convDef[i][k][0];
                    			int ind_1=convDef[i][k][1];
                    			int ind_2=convDef[i][k][2];
                    			defect_points[i].push_back(contours[i][ind_2]);
					double Angle1 = atan2(contours[i][ind_2].y - contours[i][ind_0].y,contours[i][ind_2].x - contours[i][ind_0].x) * 180.0 / CV_PI;
					double Angle2 = atan2(contours[i][ind_2].y - contours[i][ind_1].y,contours[i][ind_2].x - contours[i][ind_1].x) * 180.0 / CV_PI;
					
					/* Init center position and draws a circle around it (used to determine when dumbbell has crossed line) */
					Point center(boundRect[i].tl().x + b/2, boundRect[i].tl().y + c - 5);
					
					//contourArea(hull_points[i]) > 0.57*area_rect && ((Angle1 > 100 && Angle1 < 140) && (Angle2 > 0 && Angle2 < 40))
					if( contourArea(hull_points[i]) > 0.5*area_rect ){
						//cout << contourArea(hull_points[i]) << endl;
						//cout << area_rect << endl;
						cout << convDef[i][k] << endl;
						cout << "" << endl;
						cout << "Angle1: " + ToString(Angle1) << endl;
						cout << "Angle2: " + ToString(Angle2) << endl;
						cout << "" << endl;
						
						/* Logic method for determining each count (direction and region based) */
						if(prevCenter != Point(0)){
							if(prevCenter.y > center.y && center.y < 240 && !isAboveLine ){
								isAboveLine = true;
								++counter;
							}
						checkIfCrossedLine(center);			
						}
						prevCenter = center; // make previous center position the new center position

						cv::circle(drawing,contours[i][ind_0],5,Scalar(255,0,0),-1);
                    				cv::circle(drawing,contours[i][ind_1],5,Scalar(0,255,0),-1);
                    				cv::circle(drawing,contours[i][ind_2],5,Scalar(0,0,255),-1);
                    				cv::line(drawing,contours[i][ind_2],contours[i][ind_0],Scalar(0,0,255),1);
                    				cv::line(drawing,contours[i][ind_2],contours[i][ind_1],Scalar(255,255,0),1);
		
						cv::circle(defect_test,contours[i][ind_0],5,Scalar(255,0,0),-1);
                    				cv::circle(defect_test,contours[i][ind_1],5,Scalar(0,255,0),-1);
                    				cv::circle(defect_test,contours[i][ind_2],5,Scalar(0,0,255),-1);
                    				cv::line(defect_test,contours[i][ind_2],contours[i][ind_0],Scalar(0,0,255),1);
                    				cv::line(defect_test,contours[i][ind_2],contours[i][ind_1],Scalar(255,255,0),1);
						drawContours( defect_test, hull_points, i, colorR, 1, 8, vector<Vec4i>(), 0, Point() );

						drawContours( drawing, contours, i, colorG, 1, 8, vector<Vec4i>(), 0, Point() );
                				drawContours( drawing, hull_points, i, colorR, 1, 8, vector<Vec4i>(), 0, Point() );
						rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), Scalar(0,255,255), 1, 8, 0 ); 
						/* Write Mat to image files */
						imwrite( "Image_original.jpg", frame );
						imwrite( "Image_final.jpg", drawing );
						imwrite( "Image_final_defect.jpg", defect_test );
						
					}
                    		}
                	}
			
			
			
			
                	
		}
                
        }
    }
	//cout << "----------------------END---------------------" << endl;
    imshow( "Hull demo", drawing );
    imshow( "Defects Test", defect_test );
    imshow( "Video", frame);
}


int main( int argc, char** argv )
{

    VideoCapture capture(0);
    namedWindow( "Hull demo", cv::WINDOW_AUTOSIZE ); 
    namedWindow( "Defects Test", cv::WINDOW_AUTOSIZE );
    namedWindow( "Video", cv::WINDOW_AUTOSIZE );

	//create Background Subtractor objects
    	pMOG2 = createBackgroundSubtractorMOG2(10, 16, false); //MOG2 approach

    if (capture.isOpened()){
        while(true)
        {
            capture >> frame;
            // Blur background
	    GaussianBlur(frame, blurred, Size(17,17), 0, 0);

	    // Draw a threshold line on original image
  	    line( frame, Point( 0, 240 ), Point( 640, 240), Scalar( 0, 255, 255 ),  2, 8 );

	//get the frame number and write it on the original frame
        rectangle(frame, cv::Point(10, 2), cv::Point(170,30), cv::Scalar(255,255,255), -1);
        string disp = "Counter: " + ToString(counter);
        putText(frame, disp.c_str(), cv::Point(15, 25), FONT_HERSHEY_SIMPLEX, 0.75 , cv::Scalar(153, 50, 204));
	//get the frame number and write it on the original frame

            //Mat skinYCrCb = DetectYCrCb(frame,Scalar(0, 100, 80), Scalar(255, 185, 135));
		
		 //update the background model using background image subtraction
        	pMOG2->apply(blurred, test);
		Canny( test, test, 75, 200, 5 );
		
		//imshow( "Hull Demo", test);
            DetectContour(test);

            int c = waitKey(10);
            if( (char)c == 27 ) 
            { 
                break; 
            } 
        }
    }
    cv::destroyAllWindows();
    return 0;
}

// Convert double to string
string ToString(double val){
    stringstream stream;
    stream << val;
    return stream.str();
}

// Modifies boolean value isAboveLine to prevent multiple counts
void checkIfCrossedLine(Point &center){
	float y = center.y;
	if(y > 240){
		isAboveLine = false;
	}
}

