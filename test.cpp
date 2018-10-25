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

String img_name_path;
string file_name;

char local_path[100];
int flag = 0;

string country[6] = {"Incheon", "Seoul", "Gwangju", "Busan", "Jeju", "Daegu"}; 

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
	 
	img_name_path = buf.c_str(); // java argument

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

	string str = "../darknet_face/darknet detector test ../darknet_face/data/obj.data ../darknet_face/yolo-obj.cfg ../darknet_face/backup/yolo-obj_1400.weights "+file_name;

	system(str.c_str());

	ifstream read;
	read.open("Itisabouttheface.txt");
	
	char stringfornumber[sizeof(read)];
	read.getline(stringfornumber,sizeof(read));
				
	//make int number
	int numberforpercent = stoi(stringfornumber);
	cout<< "\n what is percent  :: "<<numberforpercent<<endl; // check using print
	read.close();
	system("rm Itisabouttheface.txt");

	if(numberforpercent < 90)//not criminal
	{
		Mat ATM_image1 = imread("atm_gui.png");

		namedWindow("ck_frame",CV_WINDOW_NORMAL);
		setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
		imshow("ck_frame",ATM_image1);
		waitKey(10);
		while(1)
		{
			int c = waitKey(0);
			if ((char)c == 'r') //restart system
			{
				return;
			}
		}
	}else{ // case : criminal (hwayoung)
		
		string java_path_argument = "java DetectingCriminal 1 "+img_name_path+" "+numberforpercent;
		//system("java DetectingCriminal 1 %s %s",img_name_path,stringfornumber);
		system(java_path_argument.c_str());
	}
}

void imshow_retake()
{
	Mat Imageforsun = imread("predictions_mask_sun.jpg");
	
	namedWindow("ck_frame",CV_WINDOW_NORMAL);
	setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	imshow("ck_frame",Imageforsun);
	waitKey(20);
}

void CountDownForTakingPhotos(VideoCapture _capture){
	Mat streamFrame;
	
	// notify taking a photo
	for(volatile int i=60; i>-1; i--){
		_capture >> streamFrame;

		if(!streamFrame.empty()){
			putText(streamFrame, 
				"Ready for taking photos",
				Point(25,50), // rocate
				FONT_HERSHEY_COMPLEX, // font
				1.4, // scale 2.0 = 2x bigger
 				Scalar(255,255,255), // B,G,R color
				4, // line thickness(optional)
				CV_AA // anti-alias(optional)
				);

			putText(streamFrame, 
				"Take off your accessory",
				Point(65,100), // rocate
				FONT_HERSHEY_COMPLEX, // font
				1.2, // scale 2.0 = 2x bigger
 				Scalar(255,255,255), // B,G,R color
				3, // line thickness(optional)
				CV_AA // anti-alias(optional)
				);
			namedWindow("ck_frame",CV_WINDOW_NORMAL);
			setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);	
			imshow("ck_frame",streamFrame);

			waitKey(10);
		}
	}
	// count down
	volatile int count = 3;
	for(volatile int i=50; i>-1; i--){

		_capture >> streamFrame;
		
		if(!streamFrame.empty()){
			putText(streamFrame, 
				to_string(count),
				Point(200,400), // rocate
				FONT_HERSHEY_SCRIPT_SIMPLEX, // font
				15.0, // scale 2.0 = 2x bigger
 				Scalar(255,255,255), // B,G,R color
				30, // line thickness(optional)
				CV_AA // anti-alias(optional)
				);
			namedWindow("ck_frame",CV_WINDOW_NORMAL);
			setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);	
			imshow("ck_frame",streamFrame);
			
			waitKey(20);	
		}
	}

	count =2;
	for(volatile int i=50; i>-1; i--){

		_capture >> streamFrame;
		
		if(!streamFrame.empty()){
			putText(streamFrame, 
				to_string(count),
				Point(200,400), // rocate
				FONT_HERSHEY_SCRIPT_SIMPLEX, // font
				15.0, // scale 2.0 = 2x bigger
 				Scalar(255,255,255), // B,G,R color
				30, // line thickness(optional)
				CV_AA // anti-alias(optional)
				);	
			namedWindow("ck_frame",CV_WINDOW_NORMAL);
			setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
			imshow("ck_frame",streamFrame);

			waitKey(20);	
		}
	}

	count=1;
	for(volatile int i=30; i>-1; i--){

		_capture >> streamFrame;
		
		if(!streamFrame.empty()){
			putText(streamFrame, 
				to_string(count),
				Point(200,400), // rocate
				FONT_HERSHEY_SCRIPT_SIMPLEX, // font
				15.0, // scale 2.0 = 2x bigger
 				Scalar(255,255,255), // B,G,R color
				30, // line thickness(optional)
				CV_AA // anti-alias(optional)
				);
			namedWindow("ck_frame",CV_WINDOW_NORMAL);
			setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);	
			imshow("ck_frame",streamFrame);			
			
			waitKey(20);	
		}
	}
}

void retake_picture(VideoCapture _capture)
{
	Mat streamFrame;

	flag = 0;

	//imshow_retake();

	Mat Imageforsun = imread("predictions_sun_mask.jpg");

	putText(Imageforsun, 
		"Take off your accessory",
		Point(50,100), // rocate
		FONT_HERSHEY_COMPLEX, // font
		1.3, // scale 2.0 = 2x bigger
 		Scalar(0,0,255), // B,G,R color
		4, // line thickness(optional)
		CV_AA // anti-alias(optional)

		);
	namedWindow("ck_frame",CV_WINDOW_NORMAL);
	setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	imshow("ck_frame", Imageforsun);
	
	waitKey(1800); // 100ms

	volatile int count = 3;
	for(volatile int i=50; i>-1; i--){

		_capture >> streamFrame;
		
		if(!streamFrame.empty()){
			putText(streamFrame, 
				to_string(count),
				Point(200,400), // rocate
				FONT_HERSHEY_SCRIPT_SIMPLEX, // font
				15.0, // scale 2.0 = 2x bigger
 				Scalar(0,0,255), // B,G,R color
				30, // line thickness(optional)
				CV_AA // anti-alias(optional)
				);
			namedWindow("ck_frame",CV_WINDOW_NORMAL);
			setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);	
			imshow("ck_frame",streamFrame);
			
			waitKey(20);	
		}
	}

	count =2;
	for(volatile int i=50; i>-1; i--){

		_capture >> streamFrame;
		
		if(!streamFrame.empty()){
			putText(streamFrame, 
				to_string(count),
				Point(200,400), // rocate
				FONT_HERSHEY_SCRIPT_SIMPLEX, // font
				15.0, // scale 2.0 = 2x bigger
 				Scalar(0,0,255), // B,G,R color
				30, // line thickness(optional)
				CV_AA // anti-alias(optional)
				);	
			namedWindow("ck_frame",CV_WINDOW_NORMAL);
			setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
			imshow("ck_frame",streamFrame);

			waitKey(20);	
		}
	}

	count=1;
	for(volatile int i=30; i>-1; i--){

		_capture >> streamFrame;
		
		if(!streamFrame.empty()){
			putText(streamFrame, 
				to_string(count),
				Point(200,400), // rocate
				FONT_HERSHEY_SCRIPT_SIMPLEX, // font
				15.0, // scale 2.0 = 2x bigger
 				Scalar(0,0,255), // B,G,R color
				30, // line thickness(optional)
				CV_AA // anti-alias(optional)
				);
			namedWindow("ck_frame",CV_WINDOW_NORMAL);
			setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);	
			imshow("ck_frame",streamFrame);			
			
			waitKey(20);	
		}
	}

	system("clear");
}

void image_view()
{
	while(1)
	{
		Mat ATM_main_image = imread("atm_gui_main.png");
		Mat ATM_help_image = imread("img.png");

		namedWindow("ck_frame",CV_WINDOW_NORMAL);
		setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
		imshow("ck_frame",ATM_main_image);
		waitKey(10);
		
		int c = waitKey(0);
		if ((char)c == 'h') //help
		{ 
			while(1)
			{
				namedWindow("ck_frame",CV_WINDOW_NORMAL);
				setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
				imshow("ck_frame",ATM_help_image);
				waitKey(10);

				int c = waitKey(0);
				if ((char)c == 27) //end for esc
				{
					break;
				}
			}
		}
		else if ((char)c == 27) //end for esc
		{
			return;
		}
	}
}

		


/** @function main */
int main(int argc, const char** argv)
{
	//system("java atmView");
	
	while(1)
	{
		// 1. ATM System start image
		image_view();

		// 2. connecting cam
		// Create OpenCV capture object. ensure it works.
		//cv::VideoCapture capture(pipeline, cv::CAP_GSTREAMER);
		cv::VideoCapture capture("/dev/video0");
		if (!capture.isOpened()) {
			std::cout << "Connection failed";
			return -1;
		}		

		// 3. before taking photos of a user
		// count down
		CountDownForTakingPhotos(capture);

		// initiate variables
		Mat frame;
		int i=0;
		int numberforpercent = 0;
		flag =-1;

		// 4. capture a photo
		capture >> frame;
		//capture.read(frame);
	
		while(1)
		{
			if(flag<0)
			{
				capture.read(frame);

				putText(frame, 
					"DETECTING ACC...",
					Point(90,100), // rocate
					FONT_HERSHEY_COMPLEX, // font
					1.5, // scale 2.0 = 2x bigger
 					Scalar(255,255,255), // B,G,R color
					5, // line thickness(optional)
					CV_AA // anti-alias(optional)
					);
				namedWindow("ck_frame",CV_WINDOW_NORMAL);
				setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
        			imshow("ck_frame", frame);
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

					putText(frame, 
						"DETECTING ACC...",
						Point(90,100), // rocate
						FONT_HERSHEY_COMPLEX, // font
						1.5, // scale 2.0 = 2x bigger
 						Scalar(255,255,255), // B,G,R color
						5, // line thickness(optional)
						CV_AA // anti-alias(optional)
						);

					namedWindow("ck_frame",CV_WINDOW_NORMAL);
					setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
					imshow("ck_frame", frame);
					
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

				string str = "./darknet detector test data/obj.data yolo-obj.cfg backup/yolo-obj_600.weights "+file_name;
			
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

					putText(frame, 
						"DETECTING FACE...",
						Point(90,100), // rocate
						FONT_HERSHEY_COMPLEX, // font
						1.5, // scale 2.0 = 2x bigger
 						Scalar(255,255,255), // B,G,R color
						5, // line thickness(optional)
						CV_AA // anti-alias(optional)
						);

					namedWindow("ck_frame",CV_WINDOW_NORMAL);
					setWindowProperty("ck_frame",WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
					imshow("ck_frame", frame);
					waitKey(20);
					
					compare_facetoface();
					break;
				}
				
			}
		}
		//int c = waitKey(0);
		//if ((char)c == 'c') { break; }

	}
	}
	return 0;
}
