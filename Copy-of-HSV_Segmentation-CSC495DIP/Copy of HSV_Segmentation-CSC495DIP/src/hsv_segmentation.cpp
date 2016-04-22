//CSC495/492
//pornchai@sit.kmutt.ac.th

#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc_c.h"
#include <stdio.h>

using namespace cv;

// Initial values
int _hueLower = 0;
int _hueUpper = 179;
int _saturationLower = 0;
int _saturationUpper = 255;
int _valueLower = 0;
int _valueUpper = 255;

IplImage* img = 0;
IplImage* img2 = 0;
IplImage* imgSeg = 0;

IplImage* DrawHistogram(CvHistogram *hist, float scaleX = 2, float scaleY = 2) {
	float histMax = 0;
	cvGetMinMaxHistValue(hist, 0, &histMax, 0, 0);
	IplImage* imgHist = cvCreateImage(cvSize(180 * scaleX, 64 * scaleY), 8, 3); // Hue has values from 0 to 179.
	cvZero(imgHist);

	for (int i = 0; i < 180 - 1; i++) {
		//float histValue = cvQueryHistValue_1D(hist, i); //not working, use the one below instead.
		float histValue = cvGetReal1D(hist->bins, i);
		float nextValue = cvGetReal1D(hist->bins, i + 1);

		CvPoint pt1 = cvPoint(i * scaleX, 64 * scaleY);
		CvPoint pt2 = cvPoint(i * scaleX + scaleX, 64 * scaleY);
		CvPoint pt3 = cvPoint(i * scaleX + scaleX,
				(64 - nextValue * 64 / histMax) * scaleY);
		CvPoint pt4 = cvPoint(i * scaleX,
				(64 - histValue * 64 / histMax) * scaleY);

		int numPts = 5;
		CvPoint pts[] = { pt1, pt2, pt3, pt4, pt1 };
		cvFillConvexPoly(imgHist, pts, numPts, CV_RGB(250, 10, 12));

	}
	return imgHist;
}

void updateHueSaturationValue(int arg, void*) {
	int hueLower = _hueLower;
	int hueUpper = _hueUpper;
	int saturationLower = _saturationLower;
	int saturationUpper = _saturationUpper;
	int valueLower = _valueLower;
	int valueUpper = _valueUpper;

	/*
	 int saturationLower = _saturationLower;
	 int saturationUpper = _saturationUpper;
	 int valueLower = _valueLower;
	 int valueUpper = _valueUpper;
	 */

	int i, j;

	// Split the image into 3 planes, namely, B, G, and R.
	IplImage* Bchannel = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* Gchannel = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* Rchannel = cvCreateImage(cvGetSize(img), 8, 1);
	cvSplit(img, Bchannel, Gchannel, Rchannel, NULL);

	unsigned char *dataB;
	dataB = (uchar *) Bchannel->imageData;
	unsigned char *dataG;
	dataG = (uchar *) Gchannel->imageData;
	unsigned char *dataR;
	dataR = (uchar *) Rchannel->imageData;

	// Transform RGB to HSV
	IplImage* img_hsv = cvCreateImage(cvGetSize(img), 8, 3);
	cvCvtColor(img, img_hsv, CV_BGR2HSV);

	// Split the HSV into 3 planes, namely, H, S, and V.
	IplImage* Hchannel = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* Schannel = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* Vchannel = cvCreateImage(cvGetSize(img), 8, 1);
	cvSplit(img_hsv, Hchannel, Schannel, Vchannel, NULL);

	// Note that the Hue value in OpenCV is in the range from 0 to 179. A total of 180.
	// However, Saturation and Value are from 0 to 255.
	unsigned char *dataH;
	dataH = (uchar *) Hchannel->imageData;
	unsigned char *dataS;
	dataS = (uchar *) Schannel->imageData;
	unsigned char *dataV;
	dataV = (uchar *) Vchannel->imageData;

	int step = Hchannel->widthStep; // Same for the other channels.
	int valH, valS, valV;

	for (i = 0; i < Hchannel->height; i++) {
		for (j = 0; j < Hchannel->width; j++) {

			// Hue
			valH = dataH[i * step + j];
			if ((valH < hueLower) || (hueUpper < valH)) {
				dataB[i * step + j] = 0; // Set to black.
				dataG[i * step + j] = 0;
				dataR[i * step + j] = 0;
			}

			// Saturation
			valS = dataS[i * step + j];
			if ((valS < saturationLower) || (saturationUpper < valS)) {
				dataB[i * step + j] = 0; // Set to black.
				dataG[i * step + j] = 0;
				dataR[i * step + j] = 0;
			}

			// Value
			valV = dataV[i * step + j];
			if ((valV < valueLower) || (valueUpper < valV)) {
				dataB[i * step + j] = 0; // Set to black.
				dataG[i * step + j] = 0;
				dataR[i * step + j] = 0;
			}
		}
	}

	IplImage* imgSeg = cvCreateImage(cvGetSize(img), 8, 3);
	cvMerge(Bchannel, Gchannel, Rchannel, NULL, imgSeg);

	// Hue histogram
	cvCvtColor(imgSeg, img_hsv, CV_BGR2HSV); // reused img_hsv.
	cvSplit(img_hsv, Hchannel, Schannel, Vchannel, NULL); // reused Hchannel and others.
	int numBins = 180;
	float range[] = { 0, 179 };
	float *ranges[] = { range };
	CvHistogram *hist = cvCreateHist(1, &numBins, CV_HIST_ARRAY, ranges, 1);
	cvClearHist(hist);
	cvCalcHist(&Hchannel, hist, 0, 0);
	IplImage* imgHistHue = DrawHistogram(hist);
	cvClearHist(hist);
	cvShowImage("Hue Histogram", imgHistHue);

	// Saturation histogram
	int numBins2 = 256;
	float range2[] = { 0, 255 };
	float *ranges2[] = { range2 };
	CvHistogram *hist2 = cvCreateHist(1, &numBins2, CV_HIST_ARRAY, ranges2, 1);
	cvClearHist(hist2);
	cvCalcHist(&Schannel, hist2, 0, 0);
	IplImage* imgHistSat = DrawHistogram(hist2);
	cvClearHist(hist2);
	cvShowImage("Saturation Histogram", imgHistSat);

	CvHistogram *hist3 = cvCreateHist(1, &numBins2, CV_HIST_ARRAY, ranges2, 1);
	cvClearHist(hist3);
	cvCalcHist(&Vchannel, hist3, 0, 0);
	IplImage* imgHistVal = DrawHistogram(hist3);
	cvClearHist(hist3);
	cvShowImage("Value Histogram", imgHistVal);

	// Image releases
	cvReleaseImage(&img_hsv);
	cvReleaseImage(&Hchannel);
	cvReleaseImage(&Schannel);
	cvReleaseImage(&Vchannel);

	cvReleaseImage(&Bchannel);
	cvReleaseImage(&Gchannel);
	cvReleaseImage(&Rchannel);

	cvShowImage("After", imgSeg); // Show the segmentation.

}

int main(int argc, char *argv[]) {
	int height, width, step, channels, height2, width2, step2, channels2;
	unsigned char *data, *data2;

	setbuf(stdout, NULL);


	//image
	img = cvLoadImage("blue.jpg");
	if (!img) {
		printf("Could not load image file: %s\n", argv[1]);
		exit(0);
	}
	//bg image
	img2 = cvLoadImage("bgmic.jpg");
	if (!img2) {
		printf("Could not load image 2 file: %s\n", argv[1]);
		exit(0);
	}

	// get the image data
	height = img->height;
	width = img->width;
	step = img->widthStep;
	channels = img->nChannels;
	data = (uchar *) img->imageData;

	// get the image data
	height2 = img2->height;
	width2 = img2->width;
	step2 = img2->widthStep;
	channels2 = img2->nChannels;
	data2 = (uchar *) img2->imageData;

	printf("Processing a %dx%d image with %d channels\n", height, width,
			channels);
	printf("step = %d\n", step);

	// create a window
	cvNamedWindow("Before", CV_WINDOW_AUTOSIZE); // Fixed size
	cvNamedWindow("Chorma Key", CV_WINDOW_AUTOSIZE); // Fixed size
	cvNamedWindow("After", CV_WINDOW_NORMAL); // Re-sizable
	cvNamedWindow("After2", CV_WINDOW_NORMAL); // Re-sizable
	cvNamedWindow("Hue Histogram"); // Default is fixed size.
	cvNamedWindow("Saturation Histogram"); // Default is fixed size.
	cvNamedWindow("Value Histogram"); // Default is fixed size.

	createTrackbar("Hue-L", "After", &_hueLower, 179, updateHueSaturationValue);
	createTrackbar("Hue-U", "After", &_hueUpper, 179, updateHueSaturationValue);

	createTrackbar("Saturation-L", "After", &_saturationLower, 255,
			updateHueSaturationValue);
	createTrackbar("Saturation-U", "After", &_saturationUpper, 255,
			updateHueSaturationValue);

	createTrackbar("Value-L", "After", &_valueLower, 255,
			updateHueSaturationValue);
	createTrackbar("Value-U", "After", &_valueUpper, 255,
			updateHueSaturationValue);

	updateHueSaturationValue(0, 0);

	IplImage* Bchannel = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* Gchannel = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* Rchannel = cvCreateImage(cvGetSize(img), 8, 1);
	cvSplit(img, Bchannel, Gchannel, Rchannel, NULL);

	unsigned char *dataB;
	dataB = (uchar *) Bchannel->imageData;
	unsigned char *dataG;
	dataG = (uchar *) Gchannel->imageData;
	unsigned char *dataR;
	dataR = (uchar *) Rchannel->imageData;

	IplImage* Bchannel2 = cvCreateImage(cvGetSize(img2), 8, 1);
	IplImage* Gchannel2 = cvCreateImage(cvGetSize(img2), 8, 1);
	IplImage* Rchannel2 = cvCreateImage(cvGetSize(img2), 8, 1);
	cvSplit(img2, Bchannel2, Gchannel2, Rchannel2, NULL);

	unsigned char *dataB2;
	dataB2 = (uchar *) Bchannel2->imageData;
	unsigned char *dataG2;
	dataG2 = (uchar *) Gchannel2->imageData;
	unsigned char *dataR2;
	dataR2 = (uchar *) Rchannel2->imageData;

	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			float val = (dataR[i * width + j] + dataG[i * width + j]) / 2.0
					- dataB[i * width + j];

			if (val < 0) {
				dataR[i * width + j] = 0;
				dataG[i * width + j] = 0;
				dataB[i * width + j] = 0;

			} else {
				int i2 = i + 220; //x
				int j2 = j + 350; //y
				dataR2[i2 * width2 + j2] = dataR[i * width + j];
				dataG2[i2 * width2 + j2] = dataG[i * width + j];
				dataB2[i2 * width2 + j2] = dataB[i * width + j];

			}

		}
	}

	IplImage* imgChroma = cvCreateImage(cvGetSize(img), 8, 3);
	cvMerge(Bchannel, Gchannel, Rchannel, NULL, imgChroma);

	IplImage* imgResult = cvCreateImage(cvGetSize(img2), 8, 3);
	cvMerge(Bchannel2, Gchannel2, Rchannel2, NULL, imgResult);

// show the image
	cvShowImage("Before", img);
	cvShowImage("Chorma Key", imgChroma);
	cvShowImage("After2", imgResult);

// wait for a key
	cvWaitKey(0);

// release the images
	cvReleaseImage(&img);
	cvReleaseImage(&imgSeg);
	cvReleaseImage(&Bchannel);
	cvReleaseImage(&Gchannel);
	cvReleaseImage(&Rchannel);
	cvReleaseImage(&Bchannel2);
	cvReleaseImage(&Gchannel2);
	cvReleaseImage(&Rchannel2);

	return 0;
}
