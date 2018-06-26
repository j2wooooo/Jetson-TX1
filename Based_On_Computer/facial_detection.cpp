#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay(Mat frame);

/** Global variables */
String face_cascade_name = "C:\\opencv-3.4\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "C:\\opencv-3.4\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";
String mouth_cascade_name = "C:\\opencv-3.4\\sources\\data\\haarcascades\\haarcascade_mcs_mouth.xml";

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
CascadeClassifier mouth_cascade;
string window_name = "Capture - Face detection";
const int BORDER = 8;  // Border between GUI elements to the edge of the image.
RNG rng(12345);

// Draw text into an image. Defaults to top-left-justified text, but you can give negative x coords for right-justified text,
// and/or negative y coords for bottom-justified text.
// Returns the bounding rect around the drawn text.
Rect drawString(Mat img, string text, Point coord, Scalar color, float fontScale = 0.6f, int thickness = 1, int fontFace = FONT_HERSHEY_COMPLEX)
{
	// Get the text size & baseline.
	int baseline = 0;
	Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;

	// Adjust the coords for left/right-justified or top/bottom-justified.
	if (coord.y >= 0) {
		// Coordinates are for the top-left corner of the text from the top-left of the image, so move down by one row.
		coord.y += textSize.height;
	}
	else {
		// Coordinates are for the bottom-left corner of the text from the bottom-left of the image, so come up from the bottom.
		coord.y += img.rows - baseline + 1;
	}
	// Become right-justified if desired.
	if (coord.x < 0) {
		coord.x += img.cols - textSize.width + 1;
	}

	// Get the bounding box around the text.
	Rect boundingRect = Rect(coord.x, coord.y - textSize.height, textSize.width, baseline + textSize.height);

	// Draw anti-aliased text.
	putText(img, text, coord, fontFace, fontScale, color, thickness, CV_AA);

	// Let the user know how big their text is, in case they want to arrange things.
	return boundingRect;
}

/** @function main */
int main(int argc, const char** argv)
{
	//-- 1. Load the cascades
	if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading\n"); return -1; };
	if (!eyes_cascade.load(eyes_cascade_name)) { printf("--(!)Error loading\n"); return -1; };
	if (!mouth_cascade.load(mouth_cascade_name)) { printf("--(!)Error loading\n"); return -1; };

	VideoCapture cap;
	Mat frame;

	if (argc > 1) cap.open(argv[1]);
	else cap.open(0);

	if (argc>1) cap.open(argv[1]); // some vid passed as cmdline arg
	else cap.open(0);              // by default use webcam
	while (cap.isOpened() && cap.read(frame))
	{
		
		detectAndDisplay(frame);
		
		imshow(window_name, frame);

		int c = waitKey(10);
		if ((char)c == 'c') { break; }
	}

	return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);

		Mat faceROI = frame_gray(faces[i]);
		std::vector<Rect> eyes;
		std::vector<Rect> mouth;

		//-- In each face, detect eyes
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
		mouth_cascade.detectMultiScale(faceROI, mouth, 1.1, 5, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(frame, center, radius, Scalar(255, 0, 0), 4, 8, 0);
		}

		Rect rcHelp;
		if (mouth.size()<1) {
			// Draw it with a black background and then again with a white foreground.
			// Since BORDER may be 0 and we need a negative position, subtract 2 from the border so it is always negative.
			float txtSize = 0.4;
			drawString(frame, "Take Off The Cold Mask Please", Point(BORDER, -BORDER - 2), CV_RGB(0, 0, 0), txtSize);  // Black shadow.
			rcHelp = drawString(frame, "Take Off The Cold Mask Please", Point(BORDER + 1, -BORDER - 1), CV_RGB(0, 0, 0), txtSize);  // White text.
		}
		else{
			for (size_t k = 0; k<mouth.size(); k++)
			{
				Point pt1(mouth[0].x + faces[i].x, mouth[0].y + faces[i].y);
				Point pt2(pt1.x + mouth[0].width, pt1.y + mouth[0].height);
				rectangle(frame, pt1, pt2, Scalar(255, 255, 255), 4, 8, 0);
			}
		}
		
	}
	//-- Show what you got
	//imshow(window_name, frame);
}

