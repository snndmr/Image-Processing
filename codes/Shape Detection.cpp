#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

const char *WINDOW_NAME_MAIN = "Main Window";

void detect(Mat image, vector<Point> &contour, vector<Point> &approx) {
	double length = arcLength(contour, true);
	approxPolyDP(contour, approx, 0.04 * length, true);

	String text;
	if(approx.size() == 3) {
		text = "Triangle";
	} else if(approx.size() == 4) {
		Rect rect = boundingRect(contour);
		text = rect.width / rect.height * 1.0 > 0.95 && rect.width / rect.height * 1.0 < 1.05 ? "Square" : "Rectangle";
	} else if(approx.size() == 5) {
		text = "Pentagon";
	} else {
		text = "Circle";
	}

	RotatedRect rect = minAreaRect(contour);
	putText(image, text, Point2f(rect.center.x, rect.center.y), FONT_HERSHEY_DUPLEX, .5, Scalar(255, 255, 255));
}

Mat preprocess(Mat image) {
	Mat instant;
	cvtColor(image, instant, COLOR_BGR2GRAY);
	medianBlur(instant, instant, 5);
	threshold(instant, instant, 60, 255, THRESH_BINARY);
	return instant;
}

int main(int argc, const char *argv[]) {
	if(argc != 2) {
		cout << format("You must specify %s as an argument", argv[1]);
		return EXIT_FAILURE;
	}

	Mat image = imread(argv[1]);
	if(image.empty()) {
		cout << format("Image %s could not be opened", argv[1]);
		return EXIT_FAILURE;
	}

	vector<vector<Point>> approx;
	vector<vector<Point>> contours;
	findContours(preprocess(image), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	approx.resize(contours.size());

	for(int contourIdx = 0; contourIdx < contours.size(); contourIdx++) {
		detect(image, contours[contourIdx], approx[contourIdx]);
		drawContours(image, contours, contourIdx, Scalar(255, 255, 255), 2);
	}

	namedWindow(WINDOW_NAME_MAIN, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME_MAIN, image);
	waitKey(0);

	return EXIT_SUCCESS;
}
