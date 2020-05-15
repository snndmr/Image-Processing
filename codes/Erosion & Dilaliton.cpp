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

void update(Mat image) {
	Mat instant;
	Mat element = getStructuringElement(MorphShapes(posOfElement), Size(2 * posOfKernel + 1, 2 * posOfKernel + 1), Point(posOfKernel, posOfKernel));

	switch(MorphTypes(posOfType)) {
		case MORPH_ERODE:
			erode(image, instant, element);
			break;
		case MORPH_DILATE:
			dilate(image, instant, element);
			break;
	}
	imshow(WINDOW_MAIN, instant);
}

void onChangeType(int pos, void* userdata) {
	posOfType = pos;
	update(*((Mat*) userdata));
}

void onChangeKernel(int pos, void* userdata) {
	posOfKernel = pos;
	update(*((Mat*) userdata));
}

void onChangeElement(int pos, void* userdata) {
	posOfElement = pos;
	update(*((Mat*) userdata));
}

int main(int argc, char** argv) {
	Mat image = imread(argv[1]);

	if(!image.data) {
		return EXIT_FAILURE;
	}

	namedWindow(WINDOW_MAIN, WINDOW_AUTOSIZE);

	createTrackbar(TRACKBAR_TYPE, WINDOW_MAIN, &posOfType, MAX_POS_TYPE, onChangeType, &image);
	createTrackbar(TRACKBAR_KERNEL, WINDOW_MAIN, &posOfKernel, MAX_POS_KERNEL, onChangeKernel, &image);
	createTrackbar(TRACKBAR_ELEMENT, WINDOW_MAIN, &posOfElement, MAX_POS_ELEMENT, onChangeElement, &image);

	imshow(WINDOW_MAIN, image);
	waitKey(0);

	return EXIT_SUCCESS;
}
