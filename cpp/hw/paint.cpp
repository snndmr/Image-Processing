#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

const int WIDTH = 1000;
const int HEIGHT = 800;
const int MAX_CIRCLE_SIZE = 300;

const char * WINDOW_NAME = "Paint v1.0";
const char * TRACKBAR_NAME = "Size";

Mat background;
int circleSize = 50;

static void on_trackbar(int value, void *) {
	circleSize = value;
}

void onMouse(int event, int x, int y, int flag, void *) {
	if(event == EVENT_RBUTTONDOWN) {
		background = Mat(HEIGHT, WIDTH, CV_8UC3, Scalar(0, 0, 0));
		imshow(WINDOW_NAME, background);
	}

	if(flag == EVENT_LBUTTONDOWN) {
		circle(background, Point(x, y), circleSize, Scalar(255, 255, 255), -1, LINE_AA);
		imshow(WINDOW_NAME, background);
	}
}

int main(int argc, char * argv[]) {
	background = Mat(HEIGHT, WIDTH, CV_8UC3, Scalar(0, 0, 0));

	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	setMouseCallback(WINDOW_NAME, onMouse);
	createTrackbar(TRACKBAR_NAME, WINDOW_NAME, &circleSize, MAX_CIRCLE_SIZE, on_trackbar);
	imshow(WINDOW_NAME, background);
	waitKey(0);
}