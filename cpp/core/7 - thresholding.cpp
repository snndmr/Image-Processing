#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

Mat image;
Mat cloneImage;

int type = 0;
int value = 0;

const int max_type = 4;
const int max_value = 255;
const int max_binary_value = 255;

const char *window_name = "window";
const char *trackbar_type = "Type ";
const char *trackbar_value = "Value ";

void Threshold(int, void *) {
	// 0: Binary | 1: Binary Inverted | 2: Threshold Truncated | 3: Threshold to Zero | 4: Threshold to Zero Inverted
	threshold(image, cloneImage, value, max_binary_value, type);
	imshow(window_name, cloneImage);
}

int main(int argc, char *argv[]) {
	image = imread(argv[1], IMREAD_GRAYSCALE);

	if(image.empty()) {
		std::cout << "Image could not find!" << std::endl;
		return EXIT_FAILURE;
	}

	namedWindow(window_name, WINDOW_AUTOSIZE);
	createTrackbar(trackbar_type, window_name, &type, max_type, Threshold);
	createTrackbar(trackbar_value, window_name, &value, max_value, Threshold);

	imshow(window_name, image);
	waitKey(0);

	return EXIT_SUCCESS;
}