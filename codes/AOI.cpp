#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

const char* WINDOW_NAME_ORIGINAL = "Original";
const char* WINDOW_NAME_AOI = "AOI";

Scalar randomColor() {
	// return Scalar(rand() % 255, rand() % 255, rand() % 255);
	return Scalar(rand() % 100 + 50, rand() % 100 + 50, rand() % 100 + 50);
}

Mat connections(Mat image) {
	Mat labels, stats, centroids;
	int num_objects = connectedComponentsWithStats(image, labels, stats, centroids);

	if(num_objects < 2) {
		std::cout << "No objects detected." << std::endl;
		return labels;
	}

	Mat output = Mat::zeros(image.rows, image.cols, CV_8UC3);
	for(int i = 1; i < num_objects; i++) {
		Mat mask = labels == i;
		output.setTo(randomColor(), mask);
		if(stats.at<int>(i, CC_STAT_AREA) > 100) {
			putText(output, format("Area: %d", stats.at<int>(i, CC_STAT_AREA)),
					Point(centroids.at<double>(i, 0), centroids.at<double>(i, 1)),
					FONT_HERSHEY_DUPLEX, 0.4, Scalar(255, 255, 255), 1, LINE_AA);
		}
	}
	return output;
}

Mat removeLight(Mat image, Mat pattern) {
	Mat instant;
	Mat image32, pattern32;
	image.convertTo(image32, CV_32F);
	pattern.convertTo(pattern32, CV_32F);
	instant = 1 - (image32 / pattern32);
	instant.convertTo(instant, CV_8U, 255);
	return instant;
}

int main(int argc, const char** argv) {
	Mat image = imread(argv[1], IMREAD_GRAYSCALE);
	Mat pattern = imread(argv[2], IMREAD_GRAYSCALE);

	if(image.empty()) {
		std::cout << "Error loading image " << argv[1] << std::endl;
		return EXIT_FAILURE;
	}

	Mat noiseless;
	medianBlur(image, noiseless, 3);
	std::cout << "Noise reduced using median blur." << std::endl;

	if(pattern.empty()) {
		std::cout << "Error loading pattern image " << argv[2] << std::endl;
		blur(image, pattern, Size(image.cols / 3, image.cols / 3));
		std::cout << argv[2] << " was created using the blur() function." << std::endl;
	}

	Mat thresh;
	threshold(removeLight(noiseless, pattern), thresh, 30, 255, THRESH_BINARY);
	std::cout << "Image was made in black and white using threshold." << std::endl;

	Mat aoi = connections(thresh);

	namedWindow(WINDOW_NAME_ORIGINAL, WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME_AOI, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME_ORIGINAL, image);
	imshow(WINDOW_NAME_AOI, aoi);
	waitKey(0);

	return EXIT_SUCCESS;
}
