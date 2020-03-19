#include <iostream>
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int args, char **argv) {
	// CV_8UC3 CV_[The number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]
	// Constructor 
	// Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
	// cout << "M = " << endl << " " << M << endl;

	// M.create(4, 4, CV_8UC(2));
	// cout << "M = " << endl << " " << M << endl;

	// Mat E = Mat::eye(4, 4, CV_64F);
	// cout << "E = " << endl << " " << E << endl << endl;

	// Mat O = Mat::ones(2, 2, CV_32F);
	// cout << "O = " << endl << " " << O << endl << endl;

	// Mat Z = Mat::zeros(3, 3, CV_8UC1);
	// cout << "Z = " << endl << " " << Z << endl << endl;

	// To fill random values.
	// Mat R = Mat(3, 2, CV_8UC3);
	// randu(R, Scalar::all(0), Scalar::all(255));
	// cout << "R (default) = " << endl << R << endl << endl;

	// To create point
	Point2f P(5, 1);
	cout << "Point (2D) = " << P << endl << endl;

	Point3f P3f(2, 6, 7);
	cout << "Point (3D) = " << P3f << endl << endl;

	return EXIT_SUCCESS;
}