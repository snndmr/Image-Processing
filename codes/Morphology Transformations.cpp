#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

const char* WINDOW_MAIN = "Morphology Transformations";
const char* TRACKBAR_TYPE = "Type";
const char* TRACKBAR_SHAPE = "Shape";
const char* TRACKBAR_KERNEL = "Kernel";

const int MAX_POS_TYPE = 6;
const int MAX_POS_SHAPE = 2;
const int MAX_POS_KERNEL = 30;

int posOfType = 0;
int posOfShape = 0;
int posOfKernel = 0;

void onChange(int, void* userdata) {
	Mat instant;
	Mat element = getStructuringElement(MorphShapes(posOfShape), Size(2 * posOfKernel + 1, 2 * posOfKernel + 1), Point(posOfKernel, posOfKernel));
	morphologyEx(*((Mat*) userdata), instant, MorphTypes(posOfType), element);
	imshow(WINDOW_MAIN, instant);
}

int main(int argc, char** argv) {
	Mat image = imread(argv[1]);

	if(image.empty()) {
		return EXIT_FAILURE;
	}

	namedWindow(WINDOW_MAIN, WINDOW_AUTOSIZE);
	createTrackbar(TRACKBAR_TYPE, WINDOW_MAIN, &posOfType, MAX_POS_TYPE, onChange, &image);
	createTrackbar(TRACKBAR_SHAPE, WINDOW_MAIN, &posOfShape, MAX_POS_SHAPE, onChange, &image);
	createTrackbar(TRACKBAR_KERNEL, WINDOW_MAIN, &posOfKernel, MAX_POS_KERNEL, onChange, &image);
	imshow(WINDOW_MAIN, image);
	waitKey(0);
	return EXIT_SUCCESS;
}