#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

const char * WINDOW_NAME = "MAIN_WINDOW";
const char * TRACKBAR_TYPE_NAME = "TYPE";
const char * TRACKBAR_SIZE_NAME = "SIZE";

const int MAX_TYPE = 3;
const int MAX_SIZE = 30;

int type = 0;
int size = 1;

Mat image;
Mat alter;

void smooth() {
	switch(type) {
	case 0:
		medianBlur(image, alter, size);
		break;
	case 1:
		GaussianBlur(image, alter, Size(size, size), 0, 0);
		break;
	case 2:
		blur(image, alter, Size(size, size), Point(-1, -1));
		break;
	case 3:
		bilateralFilter(image, alter, size, (double) size * 2, (double) size / 2);
		break;
	}
	imshow(WINDOW_NAME, alter);
}

void onChangeType(int pos, void * userdata) {
	type = pos;
	smooth();
}

void onChangeSize(int pos, void * userdata) {
	size = 2 * pos + 1;
	smooth();
}

int main(int argc, char * argv[]) {
	image = imread("istanbul.jpg");

	namedWindow(WINDOW_NAME, WINDOW_FREERATIO);
	createTrackbar(TRACKBAR_TYPE_NAME, WINDOW_NAME, &type, MAX_TYPE, onChangeType);
	createTrackbar(TRACKBAR_SIZE_NAME, WINDOW_NAME, &size, MAX_SIZE, onChangeSize);
	imshow(WINDOW_NAME, image);
	waitKey(0);
}