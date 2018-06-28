#include "opencv2/opencv.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

void read_trainData(string fn, Mat& trainingData, Mat& labels) {
	FileStorage fs(fn, FileStorage::READ); // 파일스토리지 객체 생성
	//CV_Assert(fs.isOpened()); // 예외처리
	
	fs["TrainingData"] >> trainingData; // 학습데이터 행렬로 읽기
	fs["classes"] >> labels; //레이블값 행렬로 읽기
	fs.release();
	trainingData.convertTo(trainingData, CV_32FC1); //float형 변환 -> SVM 학습하려면 데이터 행렬은 float형이여야함
	
}

Ptr<ml::SVM> SVM_create(int type, int max_iter, double epsilon) {
	Ptr<ml::SVM> svm = ml::SVM::create(); //SVM 객체선언 -> Ptr 클래스의 포인터
	// 이거 오류나서 수정

	/*SVM 학습하기위해 세부 파라미터 지정*/
	svm->setType(ml::SVM::C_SVC); //C-Support Vector Classification
	svm->setKernel(ml::SVM::LINEAR); // 선형 SVM
	svm->setGamma(1); // 커널함수의 감마값
	svm->setC(1);  // 최적화를 위한 C 파라미터

	TermCriteria criteria(type, max_iter, epsilon);
	// type : 반복 알고리즘의 방법 결정 (지금은 최대 1000번 반복 학습) 
	// -> CV_TERMCRIT_ITER : 반복횟수를 기준으로 반복 / CV_TERMCRIT_EPS : 정확도를 기준으로 반복
	// max_iter : 최대 반복수 반복알고리즘을 위한 조건으로 
	// epsilon : 정확도

	svm->setTermCriteria(criteria); // 학습 반복조건 지정
	return svm;
}

int main() {
	Mat trainingData, labels;
	read_trainData("C:\\Users\\wwwo3\\source\\repos\\OpenCV Test\\OpenCV Test\\SVMDATA.xml",trainingData,labels);
	if (trainingData.empty()) {
		printf("svmdata.xml 읽어오지 못했음\n");
	}
	
	// SVM 객체 선언
	Ptr<ml::SVM> svm = SVM_create(CV_TERMCRIT_ITER, 1000, 0); 
	svm->train(trainingData, ml::ROW_SAMPLE, labels); // 학습 수행
	svm->save("C:\\Users\\wwwo3\\source\\repos\\OpenCV Test\\OpenCV Test\\SVMtrain.xml");
	return 0;
}