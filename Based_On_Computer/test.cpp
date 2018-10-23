#include "/home/nvidia/opencv/modules/objdetect/include/opencv2/objdetect.hpp"
#include "/home/nvidia/opencv/modules/imgproc/include/opencv2/imgproc/imgproc.hpp"
#include "/home/nvidia/opencv/include/opencv2/opencv.hpp"
#include "/home/nvidia/NVIDIA_CUDA-8.0_Samples/6_Advanced/interval/boost/config/no_tr1/cmath.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <ctime>
#include <fstream>
//#include <pthread.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay(Mat frame, VideoCapture capture);

/** Global variables */
String face_cascade_name = "/home/nvidia/opencv/data/haarcascades_cuda/haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "/home/nvidia/opencv/data/haarcascades_cuda/haarcascade_eye_tree_eyeglasses.xml";
String mouth_cascade_name = "/home/nvidia/opencv/data/haarcascades_cuda/haarcascade_mcs_mouth.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
CascadeClassifier mouth_cascade;
std::string window_name = "Capture - Face detection";
RNG rng(12345);
string buf; // capture image name
char path[100] = "/home/nvidia/darknet/pictures/";

string file_name;

char local_path[100];
int flag = 0;

std::string get_tegra_pipeline(int width, int height, int fps) {
	return "nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(width) + ", height=(int)" 
		+ std::to_string(height) + ", format=(string)I420, framerate=(fraction)" + std::to_string(fps) 
		+ "/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

const std::string currentDateTime()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d_%T", &tstruct);
	//strftime(buf, sizeof(buf), "%Y-%m-%d_%X", &tstruct);
	
	return buf;
}

void capture_face(Mat frame, VideoCapture capture)
{
	capture.read(frame);

	//capture.read(frame);
        buf = currentDateTime();

        strcpy(local_path, path);
        strcat(local_path, buf.c_str());
        strcat(local_path, ".jpg");
        
        imwrite(local_path, frame);
	file_name = local_path;
	if(flag == 0)
		flag = 1;

}

void compare_facetoface()
{
	system("clear");
	cout<<"\nIt's time to compare your face!!\n"<<endl;

	//string str = "../darknet_face/darknet detector test ../darknet_face/data/obj.data ../darknet_face/yolo-obj.cfg ../darknet_face/backup/yolo-obj_1400.weights "+file_name;
	
	string str = "../darknet_face/darknet detector demo ../darknet_face/data/obj.data ../darknet_face/yolo-obj.cfg ../darknet_face/backup/yolo-obj_1400.weights ""nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink""";

	//darknet yolo demo cfg/yolo-face.cfg yolo-face_final.weights "nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink"
	system(str.c_str());

	ifstream read;
	read.open("Itisabouttheface.txt");
	
	char stringfornumber[sizeof(read)];
	read.getline(stringfornumber,sizeof(read));
				
	//make int number
	int numberforpercent = stoi(stringfornumber)
;
	cout<< "\n what is percent  :: "<<numberforpercent<<endl; // check using print
	read.close();
	system("rm Itisabouttheface.txt");

	cout<<"\nIt's time to end your face !!\n"<<endl;
}

void imshow_retake()
{
	Mat Imageforsun = imread("predictions_mask_sun.jpg");
	imshow("wrong_detection",Imageforsun);
}

void retake_picture(VideoCapture _capture)
{
	Mat streamFrame;

	flag = 0;

	//imshow_retake();

	Mat Imageforsun = imread("predictions_sun_mask.jpg");

	putText(Imageforsun, 
		"Take off your accessory",
		Point(250,100), // rocate
		FONT_HERSHEY_COMPLEX, // font
		2.0, // scale 2.0 = 2x bigger
 		Scalar(0,0,255), // B,G,R color
		4, // line thickness(optional)
		CV_AA // anti-alias(optional)

		);
	imshow("capture image", Imageforsun);
	waitKey(1800); // 100ms

	volatile int count = 3;
	for(volatile int i=50; i>-1; i--){

		_capture >> streamFrame;
		
		if(!streamFrame.empty()){
			putText(streamFrame, 
				to_string(count),
				Point(600,400), // rocate
				FONT_HERSHEY_PLAIN, // font
				15.0, // scale 2.0 = 2x bigger
 				Scalar(0,0,255), // B,G,R color
				8, // line thickness(optional)
				CV_AA // anti-alias(optional)
				);	
			imshow("capture image",streamFrame);
			waitKey(20);	
		}
		cout<<"volatile int i : "<<i<<endl;
	}

	count =2;
	for(volatile int i=50; i>-1; i--){

		_capture >> streamFrame;
		
		if(!streamFrame.empty()){
			putText(streamFrame, 
				to_string(count),
				Point(600,400), // rocate
				FONT_HERSHEY_PLAIN, // font
				15.0, // scale 2.0 = 2x bigger
 				Scalar(0,0,255), // B,G,R color
				8, // line thickness(optional)
				CV_AA // anti-alias(optional)
				);	
			imshow("capture image",streamFrame);
			waitKey(20);	
		}
	}

	count=1;
	for(volatile int i=30; i>-1; i--){

		_capture >> streamFrame;
		
		if(!streamFrame.empty()){
			putText(streamFrame, 
				to_string(count),
				Point(600,400), // rocate
				FONT_HERSHEY_PLAIN, // font
				15.0, // scale 2.0 = 2x bigger
 				Scalar(0,0,255), // B,G,R color
				8, // line thickness(optional)
				CV_AA // anti-alias(optional)
				);	
			imshow("capture image",streamFrame
);
			waitKey(20);	
		}
	}

	system("clear");
}


/** @function main */
int main(int argc, const char** argv)
{
	
	system("java atmView");

	/* ķ �ҷ����� */
	// Options
	int WIDTH = 1280;
	int HEIGHT = 720;
	int FPS = 30;

	// Define the gstream pipeline
	std::string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS);
	std::cout << "Using pipeline: \n\t" << pipeline << "\n";

	// Create OpenCV capture object. ensure it works.
	cv::VideoCapture capture(pipeline, cv::CAP_GSTREAMER);
	if (!capture.isOpened()) {
		std::cout << "Connection failed";
		return -1;
	}

	Mat frame;

	int i=0;

	int numberforpercent = 0;
	flag =-1;

	capture >> frame;
	capture.read(frame);
	
	while(1)
	{
		if(flag<0)
		{
			capture.read(frame);
        		imshow("capture image", frame);
			waitKey(20);
			flag++;
		}	
		else if(flag == 0)
		{
			//-- 3. Apply the classifier to the frame
			if (!frame.empty())
			{	
				if(flag==0)
				{
					capture_face(frame, capture); // im
					imshow("capture image", frame);
					waitKey(20);
				}
				//flag=1;
			}
			else
			{
				printf(" --(!) No captured frame -- Break!"); break;
			}

			if(flag == 1)
			{
			
				//file_name = "/home/nvidia/darknet/pictures/2018-10-15_05:50:04.jpg";
				//string str = "./darknet detector test data/obj.data yolo-obj.cfg backup/yolo-obj_600.weights "+file_name;

				string str = "./darknet detector demo data/obj.data yolo-obj.cfg backup/yolo-obj_600.weights ""nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink""";

//string str = "./darknet detector test data/obj.data yolo-obj.cfg backup/yolo-obj_600.weights  2018-10-15_05:47:50.jpg";
	//string str = "./darknet detector test data/obj.data yolo-obj.cfg backup/yolo-obj_600.weights v_mask.jpg";

			
				system(str.c_str());

				//read for checking percent ( from txt)
				ifstream read;
				read.open("Itisaboutthepercent.txt");
				char stringfornumber[sizeof(read)];
				read.getline(stringfornumber,sizeof(read));
	
				//make int number
				int numberforpercent = std::stoi(stringfornumber);
				cout<< "\n what is percent  :: "<<numberforpercent<<endl; // check using print
				read.close();

				//remove the txt file
				system("rm Itisaboutthepercent.txt");
				flag=99;
			    
				//use percent
				if( numberforpercent >= 37) // there is something
				{
					capture.read(frame);
					retake_picture(capture);
				}
				else if(numberforpercent < 37) // there is nothing -> compare face
				{	
					flag=99;
					capture.read(frame);
					
					compare_facetoface();
					return 0;
				}
				
			}
		}
		//int c = waitKey(0);
		//if ((char)c == 'c') { break; }

	}

	return 0;
}
