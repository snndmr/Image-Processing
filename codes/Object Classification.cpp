#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

Mat pattern;

Mat removeLight(Mat frame) {
	Mat aux, frame32, pattern32;
	frame.convertTo(frame32, CV_32F);
	pattern.convertTo(pattern32, CV_32F);
	aux = 1 - (frame32 / pattern32);
	aux.convertTo(aux, CV_8U, 255);
	return aux;
}

Mat preprocess(Mat frame) {
	if(frame.channels() == 3)
		cvtColor(frame, frame, COLOR_RGB2GRAY);

	medianBlur(frame, frame, 3);
	threshold(removeLight(frame), frame, 30, 255, THRESH_BINARY);
	return frame;
}

bool readFolder(String folder) {
	VideoCapture images;

	if(images.open(folder) == false) {
		cout << "Can not open the folder images" << endl;
		return false;
	}

	Mat frame;
	for(int imageIndex = 0; images.read(frame); imageIndex += 1) {
		imshow("asd", preprocess(frame));
		waitKey(100);
	}
}

int main(int argc, const char** argv) {
	Mat image = imread(argv[1], IMREAD_GRAYSCALE);
	pattern = imread(argv[2], IMREAD_GRAYSCALE);

	if(image.empty()) {
		cout << "Error loading image " << argv[1] << endl;
		return EXIT_FAILURE;
	}

	if(pattern.empty()) {
		cout << "Error loading image " << argv[2] << endl;
		return EXIT_FAILURE;
	}
	medianBlur(pattern, pattern, 3);

	readFolder("data/nut/tuerca_%04d.pgm");
	waitKey(0);
	return EXIT_SUCCESS;
}
