#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

const char* WINDOW_MAIN = "Erosion & Dilaliton Demo";
const char* TRACKBAR_TYPE = "Type";
const char* TRACKBAR_KERNEL = "Kernel";
const char* TRACKBAR_ELEMENT = "Element";

const int MAX_POS_TYPE = 1;
const int MAX_POS_KERNEL = 50;
const int MAX_POS_ELEMENT = 2;

int posOfType = 0;
int posOfKernel = 0;
int posOfElement = 0;

void onChange(int, void* userdata) {
	Mat instant;
	Mat element = getStructuringElement(MorphShapes(posOfElement), Size(2 * posOfKernel + 1, 2 * posOfKernel + 1), Point(posOfKernel, posOfKernel));

	switch(MorphTypes(posOfType)) {
		case MORPH_ERODE:
			erode(*((Mat*) userdata), instant, element);
			break;
		case MORPH_DILATE:
			dilate(*((Mat*) userdata), instant, element);
			break;
	}
	imshow(WINDOW_MAIN, instant);
}

int main(int argc, char** argv) {
	Mat source = imread(argv[1]);

	if(source.empty()) {
		return EXIT_FAILURE;
	}

	namedWindow(WINDOW_MAIN, WINDOW_AUTOSIZE);
	createTrackbar(TRACKBAR_TYPE, WINDOW_MAIN, &posOfType, MAX_POS_TYPE, onChange, &source);
	createTrackbar(TRACKBAR_KERNEL, WINDOW_MAIN, &posOfKernel, MAX_POS_KERNEL, onChange, &source);
	createTrackbar(TRACKBAR_ELEMENT, WINDOW_MAIN, &posOfElement, MAX_POS_ELEMENT, onChange, &source);
	imshow(WINDOW_MAIN, source);
	waitKey(0);
	return EXIT_SUCCESS;
}