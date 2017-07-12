#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

int main()
{
	cv::Mat image = cv::imread("potato.png");
	cv::namedWindow("Potato",cv::WINDOW_NORMAL);
	cv::imshow("Potato",image);
	cv::waitKey();
	return 0;
}
