#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
	Mat res;
	Mat image = imread(argv[1], IMREAD_COLOR);

	// Mat kernSharpen = (Mat_<char>(3, 3) <<
	// 				   0, -1, 0,
	//				   -1, 5, -1,
	//				   0, -1, 0);

	// Mat kernEdge = (Mat_<char>(3, 3) <<
	//			-1, -1, -1,
	//			-1, 8, -1,
	//			-1, -1, -1);

	// filter2D(image, res, image.depth(), kernEdge);

	// g(x) = αf(x) + β
	image.convertTo(res, -1, 5, 50);

	namedWindow("frameOne", WINDOW_NORMAL);
	namedWindow("frameTwo", WINDOW_NORMAL);

	imshow("frameOne", image);
	imshow("frameTwo", res);

	waitKey(0);

	return EXIT_SUCCESS;
}