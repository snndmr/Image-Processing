#include <vector>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define KERNEL_SIZE 31

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
	Mat image = imread(argv[1], IMREAD_COLOR);

	if(image.empty()) {
		cout << argv[1] << " - Image could not find!";
		return EXIT_FAILURE;
	}

	Mat blurImage;
	Mat gaussianImage;
	Mat medianImage;
	Mat bilateralImage;

	vector<string> windows_names = { "Normal Blur", "Gaussian", "Median", "Bilateral", "Original" };

	for(int i = 0; i < windows_names.size(); i++) {
		namedWindow(windows_names[i], WINDOW_NORMAL);
	}

	blur(image, blurImage, Size(KERNEL_SIZE, KERNEL_SIZE));
	GaussianBlur(image, gaussianImage, Size(KERNEL_SIZE, KERNEL_SIZE), 0, 0);
	medianBlur(image, medianImage, KERNEL_SIZE);
	bilateralFilter(image, bilateralImage, KERNEL_SIZE, KERNEL_SIZE * 2, KERNEL_SIZE / 2);

	imshow(windows_names[0], blurImage);
	imshow(windows_names[1], gaussianImage);
	imshow(windows_names[2], medianImage);
	imshow(windows_names[3], bilateralImage);
	imshow(windows_names[4], image);

	waitKey(0);
	return EXIT_SUCCESS;
}