#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

const char* WINDOW_NAME = "Edge Detection";
const char* TRACKBAR_TYPE = "Type";
const char* TRACKBAR_SIZE = "kSize";

const int MAX_POS_TYPE = 3;
const int MAX_POS_SIZE = 3;

const double LOWER_BOUND = 100.0;

int posOfType = 0;
int posOfSize = 0;

void sobel(Mat source) {
	Mat instant;
	Mat gradientX;
	Mat gradientY;
	Mat absoluteX;
	Mat absoluteY;

	Sobel(source, gradientX, CV_16S, 1, 0, 2 * posOfSize + 1);
	Sobel(source, gradientY, CV_16S, 0, 1, 2 * posOfSize + 1);

	convertScaleAbs(gradientX, absoluteX);
	convertScaleAbs(gradientY, absoluteY);

	addWeighted(absoluteX, 0.5, absoluteY, 0.5, 0, instant);
	imshow(WINDOW_NAME, instant);
}

void laplacian(Mat source) {
	Mat instant;
	Mat absolute;
	Laplacian(source, instant, CV_16S, 2 * posOfSize + 1);
	convertScaleAbs(instant, absolute);
	imshow(WINDOW_NAME, absolute);
}

void canny(Mat source) {
	Mat instant;
	Mat background(source.size(), source.type(), Scalar::all(0));
	Canny(source, instant, LOWER_BOUND, (posOfSize + 1) * LOWER_BOUND);
	source.copyTo(background, instant);
	imshow(WINDOW_NAME, instant);
}

void onChange(int, void* userdata) {
	switch(posOfType) {
		case 0:
			imshow(WINDOW_NAME, *(Mat*) userdata);
			break;
		case 1:
			sobel(*(Mat*) userdata);
			break;
		case 2:
			laplacian(*(Mat*) userdata);
			break;
		case 3:
			canny(*(Mat*) userdata);
			break;
		default:
			break;
	}
}

int main(int argc, char** argv) {
	Mat source = imread(argv[1], IMREAD_GRAYSCALE);

	if(source.empty()) {
		return EXIT_FAILURE;
	}

	// To reduce noise.
	GaussianBlur(source, source, Size(3, 3), 0, 0, BORDER_DEFAULT);

	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar(TRACKBAR_TYPE, WINDOW_NAME, &posOfType, MAX_POS_TYPE, onChange, &source);
	createTrackbar(TRACKBAR_SIZE, WINDOW_NAME, &posOfSize, MAX_POS_SIZE, onChange, &source);
	imshow(WINDOW_NAME, source);
	waitKey(0);

	return EXIT_SUCCESS;
}