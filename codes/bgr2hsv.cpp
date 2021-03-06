#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

const String WINDOW_NAME_ORIGINAL = "Origininal";
const String WINDOW_NAME_FIND_COLOR = "Find Color";

const String TRACKBAR_NAME_HUE = "Hue";
const String TRACKBAR_NAME_SAT = "Sat";
const String TRACKBAR_NAME_VAL = "Val";

int hue = 5;
int sat = 40;
int val = 40;

const int MAX_HUE = 180;
const int MAX_SAT = 255;
const int MAX_VAL = 255;

Scalar TOLERANCE = Scalar(hue, sat, val);

struct Bound {
	Scalar lower;
	Scalar upper;
	Scalar middle;
};

Mat findColor(Mat image, const Scalar &lowerBound, const Scalar &upperBound) {
	Mat hsv, mask, output;

	cvtColor(image, hsv, COLOR_BGR2HSV);
	inRange(hsv, lowerBound, upperBound, mask);
	copyTo(image, output, mask);
	return output;
}

Bound findBounds(Mat image) {
	Mat hsv, bgr(1, 1, CV_8UC3, mean(image));
	cvtColor(bgr, hsv, COLOR_BGR2HSV);

	Bound boundary;
	boundary.middle = mean(hsv);
	boundary.lower = Scalar(boundary.middle) - TOLERANCE;
	boundary.upper = Scalar(boundary.middle) + TOLERANCE;
	return boundary;
}

Point init;
void onMouse(int event, int x, int y, int flag, void *userdata) {
	if(event == EVENT_LBUTTONDOWN) {
		init = Point(x, y);
	}

	if(flag == EVENT_LBUTTONDOWN) {
		Mat instant = (*(Mat *) userdata).clone();
		rectangle(instant, init, Point(x, y), Scalar(255, 255, 255), 2);
		imshow(WINDOW_NAME_ORIGINAL, instant);
	}

	if(event == EVENT_LBUTTONUP) {
		Bound bound = findBounds((*(Mat *) userdata)(Rect(init, Point(x, y))));
		cout << "\n\n Bounds: {\n\t" << "lower: " << bound.lower << "\n\tupper: " << bound.upper << "\n\tmiddle:" << bound.middle << "\n }";
		imshow(WINDOW_NAME_FIND_COLOR, findColor(*(Mat *) userdata, bound.lower, bound.upper));
	}
}

void onChange(int pos, void *userdata) {
	TOLERANCE = Scalar(hue, sat, val);
	imshow(WINDOW_NAME_ORIGINAL, *(Mat *) userdata);
}

int main(int argc, const char *argv[]) {
	Mat image = imread(argv[1]);
	if(image.empty()) {
		cout << format("%s could not be opened!", argv[1]);
		return EXIT_FAILURE;
	}

	namedWindow(WINDOW_NAME_ORIGINAL, WINDOW_FREERATIO);
	createTrackbar(TRACKBAR_NAME_HUE, WINDOW_NAME_ORIGINAL, &hue, MAX_HUE, onChange, &image);
	createTrackbar(TRACKBAR_NAME_SAT, WINDOW_NAME_ORIGINAL, &sat, MAX_SAT, onChange, &image);
	createTrackbar(TRACKBAR_NAME_VAL, WINDOW_NAME_ORIGINAL, &val, MAX_VAL, onChange, &image);
	setMouseCallback(WINDOW_NAME_ORIGINAL, onMouse, &image);
	imshow(WINDOW_NAME_ORIGINAL, image);
	waitKey(0);
	return EXIT_SUCCESS;
}
