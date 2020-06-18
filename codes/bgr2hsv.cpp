#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

const Scalar TOLERANCE = Scalar(10, 36, 36);
const String WINDOW_NAME_ORIGINAL = "Origininal";
const String WINDOW_NAME_FIND_COLOR = "Find Color";

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
		imshow(WINDOW_NAME_FIND_COLOR, findColor(*(Mat *) userdata, bound.lower, bound.upper));
	}
}

int main(int argc, const char *argv[]) {
	Mat image = imread(argv[1]);
	if(image.empty()) {
		cout << format("%s could not be opened!", argv[1]);
		return EXIT_FAILURE;
	}

	namedWindow(WINDOW_NAME_ORIGINAL, WINDOW_AUTOSIZE);
	setMouseCallback(WINDOW_NAME_ORIGINAL, onMouse, &image);
	imshow(WINDOW_NAME_ORIGINAL, image);
	waitKey(0);
	return EXIT_SUCCESS;
}
