#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#define WIDTH 1280
#define HEIGHT 720

using namespace cv;
using namespace std;

void drawEllipse(Mat atom_image, int degree) {
	ellipse(atom_image,
			Point(WIDTH / 2, HEIGHT / 2),
			Size(WIDTH / 8, HEIGHT / 16),
			degree,
			0,
			360,
			Scalar(0, 255, 255),
			2,
			LINE_AA);
}

int main(int argc, char *argv[]) {

	char atom_window[] = "Drawing 1: Atom";

	Mat atom_image = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);

	drawEllipse(atom_image, 0);
	drawEllipse(atom_image, 45);
	drawEllipse(atom_image, 90);
	drawEllipse(atom_image, -45);

	circle(atom_image,
		   Point(WIDTH / 2, HEIGHT / 2),
		   HEIGHT / 64,
		   Scalar(255, 0, 255),
		   FILLED,
		   LINE_AA);

	rectangle(atom_image,
			  Point(WIDTH / 4, HEIGHT / 4),
			  Point(WIDTH / 4 * 3, HEIGHT / 4 * 3),
			  Scalar(255, 255, 0),
			  2,
			  LINE_AA);

	namedWindow(atom_window, WINDOW_FULLSCREEN);
	imshow(atom_window, atom_image);
	waitKey(0);
	return EXIT_SUCCESS;
}