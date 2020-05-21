#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;

const char* WINDOW_NAME = "Hough Line Transform";
const char* TRACKBAR_NAME = "Threshold";

const int MAX_POS_THRESHOLD = 255;

int posOfThreshold = 0;

void onChange(int, void* userdata) {
	Mat instant = (*(Mat*) userdata).clone();

	std::vector<Vec4i> lines;
	HoughLinesP(instant, lines, 1, CV_PI / 180, posOfThreshold, 50, 10);

	for(auto i : lines) {
		line(instant, Point(i[0], i[1]), Point(i[2], i[3]), 255, 3, LINE_AA);
	}
	imshow(WINDOW_NAME, instant);
}

int main(int argc, char** argv) {
	Mat source = imread(argv[1], IMREAD_GRAYSCALE);

	if(source.empty()) {
		return EXIT_FAILURE;
	}

	Canny(source, source, 50, 100);
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar(TRACKBAR_NAME, WINDOW_NAME, &posOfThreshold, MAX_POS_THRESHOLD, onChange, &source);
	imshow(WINDOW_NAME, source);
	waitKey(0);
	return EXIT_FAILURE;
}