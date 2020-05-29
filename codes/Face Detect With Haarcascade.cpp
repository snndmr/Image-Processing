#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/objdetect.hpp"

using namespace cv;
using namespace std;

int main(int argc, const char **argv) {
	if(argc != 3) {
		cout << " You must specify camera or video and haarcascade source as arguments." << endl;
		return EXIT_FAILURE;
	}

	VideoCapture capture;
	if(!capture.open(0)) {
		cout << argv[1] << " failed to open." << endl;
		return EXIT_FAILURE;
	}

	CascadeClassifier cascade;
	if(!cascade.load(argv[2])) {
		cout << argv[2] << " failed to open." << endl;
		return EXIT_FAILURE;
	}

	vector<Rect> faces;
	Mat frame;
	while(true) {
		capture.read(frame);
		cascade.detectMultiScale(frame, faces, 1.1, 2, 0 | 2, Size(30, 30));

		for(int i = 0; i < faces.size(); i++) {
			imshow("Window", frame(faces[i]));
		}
		waitKey(1);
	}
}