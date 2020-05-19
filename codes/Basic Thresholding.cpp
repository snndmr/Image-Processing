#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

const char* WINDOW_NAME = "WINDOW_MAIN";
const char* TRACKBAR_TYPE = "Type";
const char* TRACKBAR_VALUE = "Value";

const int MAX_POS_TYPE = 4;
const int MAX_POS_VALUE = 255;

int posOfType = 0;
int posOfValue = 0;

void onChange(int, void* userdata) {
	Mat instant;
	threshold(*(Mat*) userdata, instant, posOfValue, MAX_POS_VALUE, posOfType);
	imshow(WINDOW_NAME, instant);
}

int main(int argc, char** argv) {
	Mat source = imread(argv[1], IMREAD_GRAYSCALE);

	if(source.empty()) {
		return EXIT_FAILURE;
	}

	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar(TRACKBAR_TYPE, WINDOW_NAME, &posOfType, MAX_POS_TYPE, onChange, &source);
	createTrackbar(TRACKBAR_VALUE, WINDOW_NAME, &posOfValue, MAX_POS_VALUE, onChange, &source);
	onChange(0, &source);
	waitKey(0);

	return EXIT_SUCCESS;
}