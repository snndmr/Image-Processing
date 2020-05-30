#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
	Mat image = imread(argv[1]);

	if(image.empty()) {
		cout << "Image could not be opened!";
		return EXIT_FAILURE;
	}

	Mat hsvImage = image.clone();
	cvtColor(image, hsvImage, COLOR_BGR2HSV);

	Scalar lowerLimit = Scalar(60, 100, 100);
	Scalar upperLimit = Scalar(180, 255, 255);

	Mat mask, output(Scalar(0, 0, 0));
	inRange(hsvImage, lowerLimit, upperLimit, mask);

	bitwise_and(image, image, output, mask = mask);

	imshow("Output", output);
	imshow("Original", image);
	waitKey(0);
	return EXIT_SUCCESS;
}