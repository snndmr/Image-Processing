#include <iostream>
#include <opencv2/ml.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

const int MIN_AREA = 500;

const char *WINDOW_NAME_ORIGINAL = "Original";
const char *WINDOW_NAME_AFTER = "After SVM and AOI";
const char *pathOfTuerca = "data/nut/tuerca_%04d.pgm";
const char *pathOfArandela = "data/ring/arandela_%04d.pgm";
const char *pathOfTornillo = "data/screw/tornillo_%04d.pgm";

Scalar randomColor() {
	return Scalar(rand() % 255, rand() % 255, rand() % 255);
}

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

vector<vector<float>> ExtractFeatures(Mat pre, vector<int> *xOfCenter = NULL, vector<int> *yOfCenter = NULL) {
	vector<Vec4i> hierarchy;
	vector<vector<float>> output;
	vector<vector<Point>> contours;

	findContours(pre, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	if(contours.empty()) return output;

	for(int i = 0; i < contours.size(); i++) {
		Mat mask = Mat::zeros(pre.rows, pre.cols, CV_8UC1);
		drawContours(mask, contours, i, Scalar(1), FILLED, LINE_8, hierarchy, 1);

		float area = sum(mask)[0];
		if(area > MIN_AREA) {
			RotatedRect rect = minAreaRect(contours[i]);
			float width = rect.size.width;
			float height = rect.size.height;
			float aspectRatio = (width < height) ? height / width : width / height;

			vector<float> row;
			row.push_back(area);
			row.push_back(aspectRatio);
			output.push_back(row);

			if(xOfCenter != NULL) {
				xOfCenter->push_back((int) rect.center.x);
			}
			if(yOfCenter != NULL) {
				yOfCenter->push_back((int) rect.center.y);
			}
		}
	}
	return output;
}

bool readFolderAndExtractFeatures(const char *folder, Mat pattern, int label, int numberOfTest,
								  vector<float> &trainingData, vector<int> &responsesData,
								  vector<float> &testData, vector<float> &testResponsesData) {
	VideoCapture images;
	if(!images.open(folder)) {
		cout << "Can not open the folder images" << endl;
		return false;
	}

	cout << endl;
	Mat frame;
	for(int imageIndex = 0; images.read(frame); imageIndex += 1) {
		cout << format("\r %03d captured from %s", imageIndex, folder);
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

Ptr<SVM> trainAndTest(Mat pattern) {
	vector<float> trainingData;
	vector<int> responsesData;
	vector<float> testData;
	vector<float> testResponsesData;

	int numberOfTest = 20;

	readFolderAndExtractFeatures(pathOfTuerca, pattern, 0, numberOfTest,
								 trainingData, responsesData, testData, testResponsesData);
	readFolderAndExtractFeatures(pathOfArandela, pattern, 1, numberOfTest,
								 trainingData, responsesData, testData, testResponsesData);
	readFolderAndExtractFeatures(pathOfTornillo, pattern, 2, numberOfTest,
								 trainingData, responsesData, testData, testResponsesData);

	cout << endl << format(" Number of train samples: %4zd", responsesData.size());
	cout << endl << format(" Number of test samples : %4zd", testResponsesData.size());

	Mat trainingDataMat((int) trainingData.size() / 2, 2, CV_32FC1, &trainingData[0]);
	Mat responses((int) responsesData.size(), 1, CV_32SC1, &responsesData[0]);
	Mat testDataMat((int) testData.size() / 2, 2, CV_32FC1, &testData[0]);
	Mat testResponses((int) testResponsesData.size(), 1, CV_32FC1, &testResponsesData[0]);

	Ptr<TrainData> tdata = TrainData::create(trainingDataMat, ROW_SAMPLE, responses);
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setNu(0.05);
	svm->setKernel(SVM::CHI2);
	svm->setDegree(1.0);
	svm->setGamma(2.0);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
	svm->train(tdata);

	if(testResponsesData.size() > 0) {
		// Test the ML Model
		Mat testPredict;
		svm->predict(testDataMat, testPredict);
		// Error calculation
		Mat errorMat = testPredict != testResponses;
		cout << endl << format(" Error: %.5lf%%", 100.0f * countNonZero(errorMat) / testResponsesData.size());
	}
	return svm;
}

int main(int argc, const char **argv) {
	if(argc != 3) {
		cout << " You must enter image and pattern as arguments" << endl;
		return EXIT_FAILURE;
	}

	Mat image = imread(argv[1]);
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

	Ptr<SVM> svm = trainAndTest(pattern);

	Mat pre = preprocess(image, pattern);
	vector<int> xOfCenter, yOfCenter;
	vector<vector<float>> features = ExtractFeatures(pre, &xOfCenter, &yOfCenter);

	cout << endl << format(" Number of objects detected: %zd", features.size());
	imshow(WINDOW_NAME_ORIGINAL, image);
	for(int i = 0; i < features.size(); i++) {
		Mat trainingDataMat(1, 2, CV_32FC1, &features[i][0]);
		float result = svm->predict(trainingDataMat);

		if(result == 0) {
			putText(image, "Nut", Point2d(xOfCenter[i], yOfCenter[i]), FONT_HERSHEY_TRIPLEX, .5, randomColor());
		} else if(result == 1) {
			putText(image, "Ring", Point2d(xOfCenter[i], yOfCenter[i]), FONT_HERSHEY_TRIPLEX, .5, randomColor());
		} else if(result == 2) {
			putText(image, "Screw", Point2d(xOfCenter[i], yOfCenter[i]), FONT_HERSHEY_TRIPLEX, .5, randomColor());
		}
	}
	namedWindow(WINDOW_NAME_AFTER, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME_AFTER, image);
	waitKey(0);
	return EXIT_SUCCESS;
}