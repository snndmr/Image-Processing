#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

const Scalar lowerBound(100, 200, 200);
const Scalar upperBound(120, 255, 255);

Mat preprocess(Mat image) {
	Mat hsv, mask, output;

	cvtColor(image, hsv, COLOR_BGR2HSV);
	inRange(hsv, lowerBound, upperBound, mask);

	copyTo(image, output, mask);
	cvtColor(output, output, COLOR_BGR2GRAY);
	medianBlur(output, output, 5);
	return output;
}

int main(int argc, char **argv) {
	if(argc != 2) {
		cout << " You must enter image as an argument" << endl;
		return EXIT_FAILURE;
	}

	Mat image = imread(argv[1]);
	if(image.empty()) {
		cout << "Error loading image " << argv[1] << endl;
		return EXIT_FAILURE;
	}

	vector<vector<Point>> contours;
	findContours(preprocess(image), contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	for(int i = 0; i < contours.size(); i++) {
		RotatedRect rect = minAreaRect(contours[i]);
		putText(image, format("%d", i + 1), Point2f(rect.center.x - 5, rect.center.y + 5), FONT_HERSHEY_DUPLEX, .75, Scalar(255, 255, 255), 2);
	}

	imshow("Image", image);
	waitKey(0);
	return EXIT_SUCCESS;
}