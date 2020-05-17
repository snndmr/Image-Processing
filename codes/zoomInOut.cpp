#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

const char* WINDOW_NAME = "Pyramids Demo";

void onMouse(int event, int x, int y, int flags, void* userdata) {
	Mat instant;
	Mat image = *((Mat*) userdata);

	if(event == EVENT_MOUSEWHEEL) {
		if(getMouseWheelDelta(flags) > 0)
			pyrUp(*((Mat*) userdata), instant, Size(image.cols * 2, image.rows * 2));
		else
			pyrDown(*((Mat*) userdata), instant, Size(image.cols / 2, image.rows / 2));
	}
	imshow(WINDOW_NAME, instant);
}

int main(int argc, char** argv) {

	Mat image = imread(argv[1]);
	if(!image.data) {
		return EXIT_FAILURE;
	}

	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	setMouseCallback(WINDOW_NAME, onMouse, &image);
	imshow(WINDOW_NAME, image);

	waitKey(0);
	return EXIT_SUCCESS;
}