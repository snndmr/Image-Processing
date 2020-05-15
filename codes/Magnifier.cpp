#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;
using namespace std;

Mat image;
Mat latest;

Point init;
bool clicked = false;

int calcRadius(Point p1, Point p2) {
	return (int) sqrt(pow(abs(p1.x - p2.x), 2) + pow(abs(p1.y - p2.y), 2)) / 2;
}

Point calcCenter(Point p1, Point p2) {
	return Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
}

void onMouse(int event, int x, int y, int, void *) {
	if(event == EVENT_RBUTTONDOWN) {
		image.copyTo(latest);
		imshow("image", latest);
	}

	if(event == EVENT_LBUTTONDOWN) {
		init.x = x;
		init.y = y;
		clicked = true;
	}

	if(event == EVENT_LBUTTONUP) {
		Mat instant(latest(Rect(init, Point(x, y))));
		instant.copyTo(latest);
		imshow("image", instant);
		clicked = false;
	}

	if(clicked) {
		Mat instant = latest.clone();
		rectangle(instant, init, Point(x, y), cv::Scalar(0, 0, 255), 2, LINE_AA);
		//circle(instant, calcCenter(init, Point(x, y)), calcRadius(init, Point(x, y)), cv::Scalar(255, 0, 0), 2, LINE_AA);
		imshow("image", instant);
	}
}

int main(int argc, char * argv[]) {
	if(argc < 2) {
		cout << "No image file is specified as an argument.";
		return EXIT_FAILURE;
	}

	image = imread(argv[1]);
	image.copyTo(latest);

	namedWindow("image", WINDOW_AUTOSIZE);
	setMouseCallback("image", onMouse);
	imshow("image", image);
	waitKey(0);

	return EXIT_SUCCESS;
}