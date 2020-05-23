#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;

const char* WINDOW_MAIN_NAME = "Main Window";

Mat findFace(Mat* frame, Mat* head) {
	Mat instant = frame->clone();

	int result_cols = frame->cols - head->cols + 1;
	int result_rows = frame->rows - head->rows + 1;
	Mat result(result_rows, result_cols, CV_32FC1);

	matchTemplate(*frame, *head, result, TM_CCOEFF_NORMED);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	double minVal;
	double maxVal;
	Point minLoc;
	Point maxLoc;
	Point matchLoc;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	rectangle(instant, maxLoc, Point(maxLoc.x + head->cols, maxLoc.y + head->rows), Scalar(0, 255, 255), 3, LINE_AA);
	return instant;
}

int main(int argc, char** argv) {
	Mat face = imread(argv[1]);
	VideoCapture capture(argv[2]);

	if(face.empty() || !capture.isOpened()) {
		return EXIT_FAILURE;
	}

	Mat frame;
	VideoWriter video("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'),
					  capture.get(CAP_PROP_FPS), Size(capture.get(CAP_PROP_FRAME_WIDTH), capture.get(CAP_PROP_FRAME_HEIGHT)));

	printf("\n\n Video processing started. \n\n");

	clock_t beg = clock();
	double counter = 0.0;
	while(true) {
		capture >> frame;

		if(frame.empty())
			break;

		video.write(findFace(&frame, &face));
		printf("\r %3.2lf%% of the video was processed. ( Elapsed Time : %.2lf sec. )",
			   ++counter / capture.get(CAP_PROP_FRAME_COUNT) * 100, ((double) clock() - beg) / CLOCKS_PER_SEC);
	}

	printf("\n\n Video processing finished. \n\n");

	video.release();
	capture.release();
	return EXIT_SUCCESS;
}