#include <iostream>
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(int args, char **argv) {
	Mat image = imread(*(argv + 1), IMREAD_COLOR);
	// Mat image = imread(*(argv + 1), IMREAD_GRAYSCALE);

	if(image.empty()) {
		std::cout << "Image not found!";
		return EXIT_FAILURE;
	}

	Mat gray;
	cvtColor(image, gray, COLOR_RGB2GRAY);

	// To assign header of image.
	// Mat ref(image);

	// Region of Interest (ROI)
	// Mat ref(image, Rect(0, 0, 1000, 1000));
	// Mat ref = image(Range::all(), Range(1, 1000));

	// To copy image data
	// Mat ref;
	// image.copyTo(ref);
	Mat ref = gray.clone();

	namedWindow("window", WINDOW_NORMAL);
	imshow("window", ref);
	waitKey(0);

	// RGB      : Most common as our eyes use something similar
	// BGR      : OpenCV display system
	// HSV, HLS : Hue, saturation and value/luminance components,more natural way for us to describe colors
	// YCrCb    : Used by the popular JPEG image format

	return EXIT_SUCCESS;
}