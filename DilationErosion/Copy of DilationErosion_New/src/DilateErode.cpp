//	CSC495

//erosion add more black

#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc_c.h"
#include <stdio.h>

using namespace cv;


// 3x3 Structuring element

int B[3][3]= {
	{0, 1, 0},
	{1, 1, 1},
	{0, 1, 0}};

int _dilation_no,_erosion_no = 0; // Initially, perform no dilation.
IplImage* img = 0;
IplImage* imgBW = 0;
IplImage* imgOutDilation = 0;
IplImage* imgOutErotion = 0;
IplImage* imgOutBoundary = 0;


void doDilation(int iter_no, IplImage* imgBW, IplImage* imgOutDilation) {

	//just hit only 1 point
	int height, width, step;

	// get the image data
	height = imgBW->height;
	width = imgBW->width;
	step = imgBW->widthStep;

	// Split the 3-channel black&white image into 3 planes.
	IplImage* BChannel = cvCreateImage(cvGetSize(img), 8, 1); // One channel.
	IplImage* GChannel = cvCreateImage(cvGetSize(img), 8, 1); // One channel.
	IplImage* RChannel = cvCreateImage(cvGetSize(img), 8, 1); // One channel.

	cvSplit(imgBW, BChannel, GChannel, RChannel, NULL);

	// Use one of the channel, say, B or G or R because the input image is a binary image.
	unsigned char *data;
	data = (uchar *) BChannel->imageData;

	unsigned char *dataOut;
	dataOut = (uchar *) imgOutDilation->imageData;
	cvSetZero(imgOutDilation); // Clear the output.

	// One channel.
	int step_3 = step / 3;
	int i, j;
	int r, c;
	int sum = 0;

	for(int cnt = iter_no; cnt > 0; cnt-- ) {
		for (i = 1; i < height-1; i++) {
			for (j = 1; j < width-1; j++) {
				sum = 0;
				for (r = 0; r < 3; r++){
					for (c = 0; c < 3; c++){
						sum += data[(i+r-1) * step_3 + (j+c-1)] * B[r][c];
					}
				}
				// There are some hits.
				if (sum != 0){
					dataOut[i * step_3 + j] = 255; //white
				}
				else {
					dataOut[i * step_3 + j] = 0;//black
				}
			}
		}
		cvSetZero(BChannel);
		cvCopy(imgOutDilation, BChannel);
	}

	cvShowImage("Output Dilation", imgOutDilation); // Needed here.

	// release the images
	cvReleaseImage(&BChannel);
	cvReleaseImage(&GChannel);
	cvReleaseImage(&RChannel);

	return;
}

void doErosion(int iter_no, IplImage* imgBW, IplImage* imgOutErotion) {
	//hit every point or fit
	int height, width, step;

	// get the image data
	height = imgBW->height;
	width = imgBW->width;
	step = imgBW->widthStep;

	// Split the 3-channel black&white image into 3 planes.
	IplImage* BChannel = cvCreateImage(cvGetSize(img), 8, 1); // One channel.
	IplImage* GChannel = cvCreateImage(cvGetSize(img), 8, 1); // One channel.
	IplImage* RChannel = cvCreateImage(cvGetSize(img), 8, 1); // One channel.

	cvSplit(imgBW, BChannel, GChannel, RChannel, NULL);

	// Use one of the channel, say, B because the input image is a binary image.
	unsigned char *data1;
	data1 = (uchar *) BChannel->imageData;
	unsigned char *dataOut1;
	dataOut1 = (uchar *) imgOutErotion->imageData;
	cvSetZero(imgOutErotion); // Clear the output.

	// One channel.
	int step_3 = step / 3;
	int i, j;
	int r, c;
	int sum= 0; //point of hit

	for(int cnt = iter_no; cnt > 0; cnt-- ) {
		for (i = 1; i < height-1; i++) {
			for (j = 1; j < width-1; j++) {
				int count = 0;
				sum = 0;
				for (r = 0; r < 3; r++){
					for (c = 0; c < 3; c++){
						sum += data1[(i+r-1) * step_3 + (j+c-1)] * B[r][c];
						if(data1[(i+r-1) * step_3 + (j+c-1)] * B[r][c] != 0){
							count++; // count point of hit
						}
					}
				}
				// There are some hits.
				if (count == 5){ // change every time when you change structure element
					dataOut1[i * step_3 + j] = 255;
				}
				else {
					dataOut1[i * step_3 + j] = 0;
				}
			}
		}
		cvSetZero(BChannel);
		cvCopy(imgOutErotion, BChannel);
	}

	cvShowImage("Output Erosion", imgOutErotion); // Needed here.

	// release the images
	cvReleaseImage(&BChannel);
	cvReleaseImage(&GChannel);
	cvReleaseImage(&RChannel);

	return;
}

void doBoundary(int iter_no, IplImage* imgBW, IplImage* imgOutBoundary) {
	int height, width, step;

	// get the image data
	height = imgBW->height;
	width = imgBW->width;
	step = imgBW->widthStep;

	// Split the 3-channel black&white image into 3 planes.
	IplImage* BChannel = cvCreateImage(cvGetSize(img), 8, 1); // One channel.
	IplImage* GChannel = cvCreateImage(cvGetSize(img), 8, 1); // One channel.
	IplImage* RChannel = cvCreateImage(cvGetSize(img), 8, 1); // One channel.

	cvSplit(imgBW, BChannel, GChannel, RChannel, NULL);

	// Use one of the channel, say, B because the input image is a binary image.
	unsigned char *data2;
	data2 = (uchar *) BChannel->imageData;
	unsigned char *dataOut2;
	dataOut2 = (uchar *) imgOutBoundary->imageData;
	cvSetZero(imgOutBoundary); // Clear the output.

	// One channel.
	int step_3 = step / 3;
	int i, j;
	int r, c;
	int sum = 0;

	for(int cnt = iter_no; cnt > 0; cnt-- ) {
		for (i = 1; i < height-1; i++) {
			for (j = 1; j < width-1; j++) {
				int count = 0;
				sum = 0;
				for (r = 0; r < 3; r++){
					for (c = 0; c < 3; c++){
						sum += data2[(i+r-1) * step_3 + (j+c-1)] * B[r][c];
						if(data2[(i+r-1) * step_3 + (j+c-1)] * B[r][c] != 0){
							count++;
						}
					}
				}
				// There are some hits.
				if (count == 5){
					dataOut2[i * step_3 + j] = 255;
				}
				else {
					dataOut2[i * step_3 + j] = 0;
				}
				dataOut2[i * step_3 + j] = data2[i * step_3 + j] - dataOut2[i * step_3 + j];

			}
		}
		cvSetZero(BChannel);
		cvCopy(imgOutBoundary, BChannel);
	}

	cvShowImage("Output Boundary", imgOutBoundary); // Needed here.

	// release the images
	cvReleaseImage(&BChannel);
	cvReleaseImage(&GChannel);
	cvReleaseImage(&RChannel);

	return;
}



void updateDilationInteration(int arg, void*)
{
	doDilation(_dilation_no, imgBW, imgOutDilation);
}

void updateErosionInteration(int arg, void*)
{
	doErosion(_erosion_no, imgBW, imgOutErotion);
}




int main(int argc, char *argv[]) {
	int height, width, step, channels;
	unsigned char *data;

	setbuf(stdout, NULL);

	// load an image
	img = cvLoadImage("10.jpg");
	if (!img) {
		printf("Could not load image file: %s\n", argv[1]);
		exit(0);
	}

	// get the image data
	height = img->height;
	width = img->width;
	step = img->widthStep;
	channels = img->nChannels;
	data = (uchar *) img->imageData;

	printf("Processing a %dx%d image with %d channels\n", height, width,
			channels);
	printf("step = %d\n", step);

	// Create a binary image.
	imgBW = cvCreateImage(cvGetSize(img), 8, 3); // Three channels.
	cvThreshold(img, imgBW, 0, 255, CV_THRESH_BINARY);


	// Create an output image (binary image).
	imgOutDilation = cvCreateImage(cvGetSize(img), 8, 1); // One channel.
	cvSetZero(imgOutDilation); // Clear the output (optional).
	imgOutErotion = cvCreateImage(cvGetSize(img), 8, 1); // One channel.
	cvSetZero(imgOutErotion); // Clear the output (optional).
	imgOutBoundary = cvCreateImage(cvGetSize(img), 8, 1); // One channel.
	cvSetZero(imgOutBoundary); // Clear the output (optional).

	// create a window
	cvNamedWindow("Original", CV_WINDOW_AUTOSIZE); // Fixed size
	cvNamedWindow("Binary", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Output Dilation", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Control", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Output Erosion", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Output Boundary", CV_WINDOW_AUTOSIZE);

	doBoundary(1,imgBW,  imgOutBoundary);

	// Morphological processing...
	createTrackbar("Dilation", "Control", &_dilation_no, 5, updateDilationInteration);
	//updateDilationInteration(0, 0);
	createTrackbar("Erosion", "Control", &_erosion_no, 5, updateErosionInteration);
	// show the image
	cvShowImage("Original", img);
	cvShowImage("Binary", imgBW);
	cvShowImage("Output Dilation", imgOutDilation);
	cvShowImage("Output Erosion", imgOutErotion);
	cvShowImage("Output Boundary", imgOutBoundary);

	// wait for a key
	cvWaitKey(0);

	// release the images
	cvReleaseImage(&img);
	cvReleaseImage(&imgBW);
	cvReleaseImage(&imgOutDilation);
	cvReleaseImage(&imgOutErotion);
	cvReleaseImage(&imgOutBoundary);

	return 0;
}
