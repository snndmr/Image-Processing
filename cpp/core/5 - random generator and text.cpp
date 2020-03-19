#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#define WIDTH 1920
#define HEIGHT 1080

#define DELAY 10
#define NUMBER 100

using namespace cv;
using namespace std;

Scalar randomColor(RNG rng) {
	return Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
}

bool drawRandomLine(Mat image, char *window_name, RNG rng) {
	Point pointOne, pointTwo;

	for(int i = 0; i < NUMBER; i++) {
		pointOne.x = rng.uniform(0, WIDTH);
		pointOne.y = rng.uniform(0, HEIGHT);
		pointTwo.x = rng.uniform(0, WIDTH);
		pointTwo.y = rng.uniform(0, HEIGHT);

		line(image, pointOne, pointTwo, randomColor(rng), rng.uniform(1, 10), LINE_AA);
		imshow(window_name, image);

		if(waitKey(DELAY) >= 0) {
			return false;
		}
	}
	return true;
}

bool drawRandomRectangle(Mat image, char *window_name, RNG rng) {
	Point pointOne, pointTwo;

	for(int i = 0; i < NUMBER; i++) {
		pointOne.x = rng.uniform(0, WIDTH);
		pointOne.y = rng.uniform(0, HEIGHT);
		pointTwo.x = rng.uniform(0, WIDTH);
		pointTwo.y = rng.uniform(0, HEIGHT);

		rectangle(image, pointOne, pointTwo, randomColor(rng), rng.uniform(-1, 10), LINE_AA);
		imshow(window_name, image);

		if(waitKey(DELAY) >= 0) {
			return false;
		}
	}
	return true;
}

bool drawRandomEllipse(Mat image, char *window_name, RNG rng) {
	int degree(0);
	Point center, point;

	for(int i = 0; i < NUMBER; i++) {
		degree = rng.uniform(0, 360);
		center.x = rng.uniform(0, WIDTH);
		center.y = rng.uniform(0, HEIGHT);
		point.x = rng.uniform(0, WIDTH) / 16;
		point.y = rng.uniform(0, HEIGHT) / 16;

		ellipse(image, center, point, degree, 0, degree, randomColor(rng), rng.uniform(-1, 10), LINE_AA);
		imshow(window_name, image);

		if(waitKey(DELAY) >= 0) {
			return false;
		}
	}
	return true;
}

bool drawRandomText(Mat image, char *window_name, RNG rng) {
	Point point;

	for(int i = 0; i < NUMBER; i++) {
		point.x = rng.uniform(0, WIDTH);
		point.y = rng.uniform(0, HEIGHT);

		putText(image, "Selam ben Sinan!", point, rng.uniform(0, 8), rng.uniform(0, 100) * 0.05 + 0.1, randomColor(rng), rng.uniform(1, 10), LINE_AA);
		imshow(window_name, image);

		if(waitKey(DELAY) >= 0) {
			return false;
		}
	}
	return true;
}

bool drawEndText(Mat image, char *window_name, RNG rng) {
	Size textSize = getTextSize("Selam ben Sinan!", FONT_HERSHEY_COMPLEX, 3, 5, 0);

	Point point;
	point.x = (WIDTH - textSize.width) / 2;
	point.y = (HEIGHT - textSize.height) / 2;

	Mat imageTwo;

	for(int i = 0; i < 255; i+=3) {
		imageTwo = image - Scalar::all(i);
		putText(imageTwo, "Selam ben Sinan!", point, FONT_HERSHEY_COMPLEX, 3, Scalar(i, i, 255), 5, LINE_AA);
		imshow(window_name, imageTwo);

		if(waitKey(DELAY) >= 0) {
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
	// Random Number Generator object (RNG)
	RNG rng(0xFFFFFFFF);

	char window_name[] = "window";

	Mat image = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);

	drawRandomLine(image, window_name, rng);
	drawRandomRectangle(image, window_name, rng);
	drawRandomEllipse(image, window_name, rng);
	drawRandomText(image, window_name, rng);
	drawEndText(image, window_name, rng);

	namedWindow(window_name, WINDOW_FULLSCREEN);
	waitKey(0);
	return EXIT_SUCCESS;
}