#include "opencv2/opencv.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/* 함수 */
void collect_trainImage(Mat& trainingData, Mat& labels, int Nimages);
void write_traindata(string fn, Mat trainingData, Mat classes);
Mat preprocessing(Mat& image);

void main() {
	Mat trainingData, labels;
	collect_trainImage(trainingData, labels, 70); // 학습 데이터 생성
	write_traindata("SVMDATA.xml", trainingData, labels);     // 파일 저장
}

void collect_trainImage(Mat& trainingData, Mat& labels, int Nimages) {  // Nimages= 35 + 35
	/*
	string fname = format("C:\\Users\\wwwo3\\source\\repos\\OpenCV Test\\OpenCV Test\\trainimage\\%d.png", 38);
	Mat img = imread(fname, IMREAD_COLOR);
	CV_Assert(img.data);
	
	//if (img.empty()) {
	//	printf("couldn't load image !\n");
	//	return;
	//}
	//else {
		preprocessing(img);
	//}
	
	*/

	
	for (int i = 0; i < Nimages; i++) {
	printf("이미지 출력해볼게 %d.png\n",i);
	string fname = format("C:\\Users\\wwwo3\\source\\repos\\OpenCV Test\\OpenCV Test\\trainimage\\%d.png",i);
	//"C:\\opencv-3.4\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml"
	Mat img = imread(fname, IMREAD_COLOR);
	CV_Assert(img.data);
	cvtColor(img, img, CV_BGR2GRAY);

	Mat tmp = img.reshape(1, 1);  // 학습 영상을 1행 데이터로 만들기
	int label = (i < 35) ? 1 : 0;  // 0~69번 이미지는 선글라스, 70~139번 이미지는 선글라스 아닌거
	trainingData.push_back(tmp);
	labels.push_back(label);
	}
	trainingData.convertTo(trainingData, CV_32FC1);
	
}

void write_traindata(string fn, Mat trainingData, Mat classes) {
	FileStorage fs(fn, FileStorage::WRITE); // 저장모드
	fs << "trainingData" << trainingData; // 학습 데이터 행렬 저장
	fs << "classes" << classes; // 레이블값 행렬 저장
	fs.release();
}

Mat preprocessing(Mat& image) {  // 이미지 학습시키기 전에 전처리해야하는데 이게 맞는지 모르겠음
	Mat gray, th_img, morph;
	Mat kernel(5, 15, CV_8UC1, Scalar(1));  // 닫힘 연산 마스크
	
	imshow("origin image", image);
	//waitKey(0);
	if (image.empty()) {
		
	}
	else {

		// 에러 이유 : image has different type 
		//cvtColor(image, gray, CV_BGR2HSV);
		//cvtColor(image, gray, CV_RGB2HSV);
		cvtColor(image, gray, CV_BGR2GRAY);
		imshow("gray image", gray);
		waitKey(0);
		

		/*
		if (image.channels() ==3) {  // 데스크톱 3채널 BGR
			cvtColor(image, gray, CV_BGR2GRAY);
		}
		else {  // 모바일 4채널 BGRA
			cvtColor(image, gray, CV_BGRA2GRAY);
		}
		*/
		
		//blur(gray, gray, Size(5, 5)); // 블러링
		//Sobel(gray, gray, CV_8U, 1, 0, 3); // 소벨 에지 검출

		threshold(gray, th_img, 120, 255, THRESH_BINARY); //이진화 수행
		morphologyEx(th_img, morph, MORPH_CLOSE, kernel, Point(-1, -1), 2); // 열림 연산 수행

		imshow("th_img", th_img), imshow("morph", morph);
		return morph;
	}

	/*
	//cvtColor(image, gray, COLOR_BGR2GRAY);
	
	//cvtColor(image, gray, CV_BGR2GRAY);  // 명암도 영상 변환
	blur(gray, gray, Size(5, 5)); // 블러링
	Sobel(gray, gray, CV_8U, 1, 0, 3); // 소벨 에지 검출

	threshold(gray, th_img, 120, 255, THRESH_BINARY); //이진화 수행
	morphologyEx(th_img, morph, MORPH_CLOSE, kernel, Point(-1,-1), 2); // 열림 연산 수행
	
	imshow("th_img", th_img), imshow("morph", morph);
	return morph;*/
}
