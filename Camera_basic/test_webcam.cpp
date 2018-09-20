#include "/home/nvidia/opencv/modules/objdetect/include/opencv2/objdetect.hpp"
//#include "/home/nvidia/opencv/modules/highgui/include/opencv2/highgui.hpp"
#include "/home/nvidia/opencv/modules/imgproc/include/opencv2/imgproc/imgproc.hpp"
#include "/home/nvidia/opencv/include/opencv2/opencv.hpp"
#include "/home/nvidia/NVIDIA_CUDA-8.0_Samples/6_Advanced/interval/boost/config/no_tr1/cmath.hpp" 

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main()
{
	cv::VideoCapture capture("/dev/video1");
	if(!capture.isOpened()){
		std::cout<<"Connection failed";
		return -1;
	}

	Mat frame;
	while(1){
		capture>>frame;
		if (!frame.empty())
                {
                        imshow("webcam test", frame);

                }
                else
                {
                        printf(" --(!) No captured frame -- Break!"); break;
                }

                int c = waitKey(10);
                if ((char)c == 'c') { break; }

	}
	return 0;
}
