#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

const char *pathOfTuerca = "data/nut/tuerca_%04d.pgm";
const char *pathOfArandela = "data/ring/arandela_%04d.pgm";
const char *pathOfTornillo = "data/screw/tornillo_%04d.pgm";

Mat removeLight(Mat image, Mat pattern) {
	Mat output, frame32, pattern32;

	// The division method requires a 32-bit float of images.
	image.convertTo(frame32, CV_32F);
	pattern.convertTo(pattern32, CV_32F);

	// Formula: output = 255 * 1 - (frame/pattern)
	output = 1 - (frame32 / pattern32);
	output.convertTo(output, CV_8U, 255);
	return output;
}

Mat preprocess(Mat image, Mat pattern) {
	if(image.channels() == 3) cvtColor(image, image, COLOR_RGB2GRAY);
	medianBlur(image, image, 3);
	image = removeLight(image, pattern);
	threshold(image, image, 30, 255, THRESH_BINARY);
	return image;
}

vector<vector<float>> ExtractFeatures(Mat pre, vector<int> *left = NULL, vector<int> *top = NULL) {
	vector<vector<float>> output;
	vector<vector<Point>> contours;
	Mat input = pre.clone();

	vector<Vec4i> hierarchy;

	findContours(pre, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	if(contours.empty()) {
		return output;
	}

	for(int i = 0; i < contours.size(); i++) {
		Mat mask = Mat::zeros(pre.rows, pre.cols, CV_8UC1);
		drawContours(mask, contours, i, Scalar(1), FILLED, LINE_8, hierarchy, 1);

		float area = sum(mask)[0];
		if(area > 500) {
			RotatedRect rect = minAreaRect(contours[i]);
			float width = rect.size.width;
			float height = rect.size.height;
			float aspectRatio = (width < height) ? height / width : width / height;

			vector<float> row;
			row.push_back(area);
			row.push_back(aspectRatio);

			output.push_back(row);

			if(left != NULL) {
				left->push_back((int) rect.center.x);
			}
			if(top != NULL) {
				top->push_back((int) rect.center.y);
			}
		}
	}
	return output;
}

bool readFolderAndExtractFeatures(String folder, Mat pattern, int label, int numberOfTest,
								  vector<float> &trainingData, vector<int> &responsesData,
								  vector<float> &testData, vector<float> &testResponsesData) {
	VideoCapture images;

	if(images.open(folder) == false) {
		cout << "Can not open the folder images" << endl;
		return false;
	}

	Mat frame;

	for(int imageIndex = 0; images.read(frame); imageIndex += 1) {
		Mat pre = preprocess(frame, pattern);
		vector<vector<float>> features = ExtractFeatures(pre);
		for(int i = 0; i < features.size(); i++) {
			if(imageIndex >= numberOfTest) {
				trainingData.push_back(features[i][0]);
				trainingData.push_back(features[i][1]);
				responsesData.push_back(label);
			} else {
				testData.push_back(features[i][0]);
				testData.push_back(features[i][1]);
				testResponsesData.push_back(label);
			}
		}
	}
	return true;
}

void trainAndTest(Mat pattern) {
	vector< float > trainingData;
	vector< int > responsesData;
	vector< float > testData;
	vector< float > testResponsesData;

	int numberOfTest = 20;

	readFolderAndExtractFeatures(pathOfTuerca, pattern, 0, numberOfTest, trainingData, responsesData, testData, testResponsesData);
	readFolderAndExtractFeatures(pathOfArandela, pattern, 1, numberOfTest, trainingData, responsesData, testData, testResponsesData);
	readFolderAndExtractFeatures(pathOfTornillo, pattern, 2, numberOfTest, trainingData, responsesData, testData, testResponsesData);

	cout << "Num of train samples: " << responsesData.size() << endl;
	cout << "Num of test samples: " << testResponsesData.size() << endl;
}

int main(int argc, const char **argv) {
	if(argc != 3) {
		return EXIT_FAILURE;
	}

	Mat image = imread(argv[1], IMREAD_GRAYSCALE);
	Mat pattern = imread(argv[2], IMREAD_GRAYSCALE);

	if(image.empty()) {
		cout << "Error loading image " << argv[1] << endl;
		return EXIT_FAILURE;
	}

	if(pattern.empty()) {
		cout << "Error loading image " << argv[2] << endl;
		return EXIT_FAILURE;
	}
	medianBlur(pattern, pattern, 3);

	trainAndTest(pattern);
	waitKey(0);
	return EXIT_SUCCESS;
}