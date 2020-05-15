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

void update(Mat image) {
	Mat instant;
	Mat element = getStructuringElement(MorphShapes(posOfShape), Size(2 * posOfKernel + 1, 2 * posOfKernel + 1), Point(posOfKernel, posOfKernel));
	morphologyEx(image, instant, MorphTypes(posOfType), element);
	imshow(WINDOW_MAIN, instant);
}

void onChangeType(int pos, void* userdata) {
	posOfType = pos;
	update(*((Mat*) userdata));
}

void onChangeShape(int pos, void* userdata) {
	posOfShape = pos;
	update(*((Mat*) userdata));
}

void onChangeKernel(int pos, void* userdata) {
	posOfKernel = pos;
	update(*((Mat*) userdata));
}

int main(int argc, char** argv) {
	Mat image = imread(argv[1]);

	if(!image.data) {
		return EXIT_FAILURE;
	}

	namedWindow(WINDOW_MAIN, WINDOW_AUTOSIZE);

	createTrackbar(TRACKBAR_TYPE, WINDOW_MAIN, &posOfType, MAX_POS_TYPE, onChangeType, &image);
	createTrackbar(TRACKBAR_SHAPE, WINDOW_MAIN, &posOfShape, MAX_POS_SHAPE, onChangeShape, &image);
	createTrackbar(TRACKBAR_KERNEL, WINDOW_MAIN, &posOfKernel, MAX_POS_KERNEL, onChangeKernel, &image);

	imshow(WINDOW_MAIN, image);
	waitKey(0);
	return EXIT_SUCCESS;
}