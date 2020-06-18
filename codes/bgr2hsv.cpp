#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

const double HUE_TOLARENCE = 10.0;
const double SAT_TOLARENCE = 30.0;
const double VAL_TOLARENCE = 30.0;

struct Bound {
	Scalar lower;
	Scalar middle;
	Scalar upper;
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
	boundary.lower = Scalar(boundary.middle[0] - HUE_TOLARENCE, boundary.middle[1] - SAT_TOLARENCE, boundary.middle[2] - VAL_TOLARENCE);
	boundary.upper = Scalar(boundary.middle[0] + HUE_TOLARENCE, boundary.middle[1] + SAT_TOLARENCE, boundary.middle[2] + VAL_TOLARENCE);
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
		imshow("Original", instant);
	}

	if(event == EVENT_LBUTTONUP) {
		Bound bound = findBounds((*(Mat *) userdata)(Rect(init, Point(x, y))));
		imshow("Find Color", findColor(*(Mat *) userdata, bound.lower, bound.upper));
	}
}
int main(int argc, const char *argv[]) {
	Mat image = imread(argv[1]);
	Bound bound = findBounds(image);

	namedWindow("Original", WINDOW_AUTOSIZE);
	setMouseCallback("Original", onMouse, &image);
	imshow("Original", image);
	waitKey(0);
	return EXIT_SUCCESS;
}
