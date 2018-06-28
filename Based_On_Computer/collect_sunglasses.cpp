#include "opencv2/opencv.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/* 함수 */
void collect_trainImage(Mat& trainingData, Mat& labels, int Nimages);
void write_traindata(string fn, Mat trainingData, Mat classes);

void main() {
	Mat trainingData, labels;
	collect_trainImage(trainingData, labels, 70); // 학습 데이터 생성
	write_traindata("SVMDATA.xml", trainingData, labels);     // 파일 저장
}

void collect_trainImage(Mat& trainingData, Mat& labels, int Nimages) {  // Nimages= 35 + 35
	for (int i = 0; i < Nimages; i++) {
		printf("이미지 출력해볼게 %d.png\n",i);
		string fname = format("C:\\Users\\wwwo3\\source\\repos\\OpenCV Test\\OpenCV Test\\trainimage\\%d.png",i);
		//"C:\\opencv-3.4\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml"
		Mat img = imread(fname,0);
		CV_Assert(img.data);

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