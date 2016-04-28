//CSC495
//aom ball pan
//note most 24 bit -->15 12 9 6 3
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>

using namespace cv;

int _scrollbar = 0;
IplImage* img = 0;
IplImage* outputImg = 0;

void update(int arg, void*){
	int height,width,step,channels,i,j,k;

	IplImage* imgBit = cvCreateImage(cvGetSize(img), 8, 3);
	cvCopy(img,imgBit);

	unsigned char *data ;

	// get the image data
	height    = img->height;
	width     = img->width;
	step      = img->widthStep;
	channels  = imgBit->nChannels;
	data      = (uchar *)imgBit->imageData;

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){

			if(_scrollbar == 0){

			}
			//3bit
			if(_scrollbar == 1){
				for(k=0;k<channels;k++){
					if(data[i*step+j*channels+k]>127){
						data[i*step+j*channels+k] = 255;}
					else{data[i*step+j*channels+k]= 0;}
				}
			}

			//6bit
			if(_scrollbar == 2){
				for(k=0;k<channels;k++){
					if(data[i*step+j*channels+k] >= 0 && data[i*step+j*channels+k] < 64 ){
						data[i*step+j*channels+k] = 64;}
					else if(data[i*step+j*channels+k]>= 64 && data[i*step+j*channels+k] < 128){
						data[i*step+j*channels+k] = 128;}
					else if(data[i*step+j*channels+k]>= 128 && data[i*step+j*channels+k] < 192 ){
						data[i*step+j*channels+k] = 192;}
					else{data[i*step+j*channels+k]= 255;}
				}
			}

			//9bit
			if(_scrollbar == 3){
				for(k=0;k<channels;k++){
					if(data[i*step+j*channels+k]>= 0&& data[i*step+j*channels+k] < 32 ){
						data[i*step+j*channels+k] = 32;}
					else if(data[i*step+j*channels+k]>= 32&& data[i*step+j*channels+k] < 64 ){
						data[i*step+j*channels+k] = 64;}
					else if(data[i*step+j*channels+k]>=64  && data[i*step+j*channels+k] < 96 ){
						data[i*step+j*channels+k] = 96;}
					else if(data[i*step+j*channels+k]>= 96&& data[i*step+j*channels+k] < 128 ){
						data[i*step+j*channels+k] = 128;}
					else if(data[i*step+j*channels+k]>= 128&& data[i*step+j*channels+k] < 160 ){
						data[i*step+j*channels+k] = 160;}
					else if(data[i*step+j*channels+k]>= 160&& data[i*step+j*channels+k] < 192 ){
						data[i*step+j*channels+k] = 192;}
					else if(data[i*step+j*channels+k]>= 192&& data[i*step+j*channels+k] < 224 ){
						data[i*step+j*channels+k] = 224;}
					else{data[i*step+j*channels+k]= 255;}
				}
			}

			//12bit
			if(_scrollbar == 4){
				for(k=0;k<channels;k++){
					if(data[i*step+j*channels+k]>= 0&& data[i*step+j*channels+k] < 16 ){
						data[i*step+j*channels+k] = 16;}
					else if(data[i*step+j*channels+k]>= 16 && data[i*step+j*channels+k] < 32 ){
						data[i*step+j*channels+k] = 32;}
					else if(data[i*step+j*channels+k]>= 32 && data[i*step+j*channels+k] < 64 ){
						data[i*step+j*channels+k] = 64;}
					else if(data[i*step+j*channels+k]>= 64 && data[i*step+j*channels+k] < 80 ){
						data[i*step+j*channels+k] = 80;}
					else if(data[i*step+j*channels+k]>= 80 && data[i*step+j*channels+k] < 96 ){
						data[i*step+j*channels+k] = 96;}
					else if(data[i*step+j*channels+k]>= 96 && data[i*step+j*channels+k] < 112 ){
						data[i*step+j*channels+k] = 112;}
					else if(data[i*step+j*channels+k]>= 112 && data[i*step+j*channels+k] < 128 ){
						data[i*step+j*channels+k] = 128;}
					else if(data[i*step+j*channels+k]>= 128 && data[i*step+j*channels+k] < 144 ){
						data[i*step+j*channels+k] = 144;}
					else if(data[i*step+j*channels+k]>= 144 && data[i*step+j*channels+k] < 160 ){
						data[i*step+j*channels+k] = 160;}
					else if(data[i*step+j*channels+k]>= 160 && data[i*step+j*channels+k] < 176 ){
						data[i*step+j*channels+k] = 176;}
					else if(data[i*step+j*channels+k]>= 176 && data[i*step+j*channels+k] < 192 ){
						data[i*step+j*channels+k] = 192;}
					else if(data[i*step+j*channels+k]>= 192 && data[i*step+j*channels+k] < 208 ){
						data[i*step+j*channels+k] = 208;}
					else if(data[i*step+j*channels+k]>= 208 && data[i*step+j*channels+k] < 224 ){
						data[i*step+j*channels+k] = 224;}
					else if(data[i*step+j*channels+k]>= 224 && data[i*step+j*channels+k] < 240 ){
						data[i*step+j*channels+k] = 240;}
					else{data[i*step+j*channels+k]= 255;}
				}
			}

			//15 bit == 32 case
			if(_scrollbar == 5){
				for(k=0;k<channels;k++){
					if(data[i*step+j*channels+k]>= 0 && data[i*step+j*channels+k] < 8 ){
						data[i*step+j*channels+k] = 8;}
					else if(data[i*step+j*channels+k]>= 8 && data[i*step+j*channels+k] <16 ){
						data[i*step+j*channels+k] = 16;}
					else if(data[i*step+j*channels+k]>= 16 && data[i*step+j*channels+k] < 24 ){
						data[i*step+j*channels+k] = 24;}
					else if(data[i*step+j*channels+k]>= 24 && data[i*step+j*channels+k] < 32 ){
						data[i*step+j*channels+k] = 32;}
					else if(data[i*step+j*channels+k]>= 32 && data[i*step+j*channels+k] < 40 ){
						data[i*step+j*channels+k] = 40;}
					else if(data[i*step+j*channels+k]>= 40 && data[i*step+j*channels+k] < 48 ){
						data[i*step+j*channels+k] = 48;}
					else if(data[i*step+j*channels+k]>= 48 && data[i*step+j*channels+k] < 56 ){
						data[i*step+j*channels+k] = 56;}
					else if(data[i*step+j*channels+k]>= 56 && data[i*step+j*channels+k] < 64 ){
						data[i*step+j*channels+k] = 64;}
					else if(data[i*step+j*channels+k]>= 64 && data[i*step+j*channels+k] < 72 ){
						data[i*step+j*channels+k] = 72;}
					else if(data[i*step+j*channels+k]>= 72 && data[i*step+j*channels+k] < 80 ){
						data[i*step+j*channels+k] = 80;}
					else if(data[i*step+j*channels+k]>= 80 && data[i*step+j*channels+k] < 88 ){
						data[i*step+j*channels+k] = 88;}
					else if(data[i*step+j*channels+k]>= 88 && data[i*step+j*channels+k] < 96 ){
						data[i*step+j*channels+k] = 96;}
					else if(data[i*step+j*channels+k]>= 96 && data[i*step+j*channels+k] < 104 ){
						data[i*step+j*channels+k] = 104;}
					else if(data[i*step+j*channels+k]>= 104 && data[i*step+j*channels+k] < 112 ){
						data[i*step+j*channels+k] = 112;}
					else if(data[i*step+j*channels+k]>= 112 && data[i*step+j*channels+k] < 120 ){
						data[i*step+j*channels+k] = 120;}
					else if(data[i*step+j*channels+k]>= 120 && data[i*step+j*channels+k] < 128 ){
						data[i*step+j*channels+k] = 128;}
					else if(data[i*step+j*channels+k]>= 128 && data[i*step+j*channels+k] < 136 ){
						data[i*step+j*channels+k] = 136;}
					else if(data[i*step+j*channels+k]>= 136 && data[i*step+j*channels+k] < 144 ){
						data[i*step+j*channels+k] = 144;}
					else if(data[i*step+j*channels+k]>= 144 && data[i*step+j*channels+k] < 152 ){
						data[i*step+j*channels+k] = 152;}
					else if(data[i*step+j*channels+k]>= 152 && data[i*step+j*channels+k] <160 ){
						data[i*step+j*channels+k] = 160;}
					else if(data[i*step+j*channels+k]>= 160 && data[i*step+j*channels+k] < 168 ){
						data[i*step+j*channels+k] = 168;}
					else if(data[i*step+j*channels+k]>= 168 && data[i*step+j*channels+k] < 176 ){
						data[i*step+j*channels+k] = 176;}
					else if(data[i*step+j*channels+k]>= 176 && data[i*step+j*channels+k] < 184 ){
						data[i*step+j*channels+k] = 184;}
					else if(data[i*step+j*channels+k]>= 184 && data[i*step+j*channels+k] < 192 ){
						data[i*step+j*channels+k] =192;}
					else if(data[i*step+j*channels+k]>= 192 && data[i*step+j*channels+k] < 200 ){
						data[i*step+j*channels+k] = 200;}
					else if(data[i*step+j*channels+k]>= 200 && data[i*step+j*channels+k] < 208 ){
						data[i*step+j*channels+k] = 208;}
					else if(data[i*step+j*channels+k]>= 208 && data[i*step+j*channels+k] < 216 ){
						data[i*step+j*channels+k] = 216;}
					else if(data[i*step+j*channels+k]>= 216 && data[i*step+j*channels+k] < 224 ){
						data[i*step+j*channels+k] = 224;}
					else if(data[i*step+j*channels+k]>= 224 && data[i*step+j*channels+k] < 232 ){
						data[i*step+j*channels+k] = 232;}
					else if(data[i*step+j*channels+k]>= 232 && data[i*step+j*channels+k] < 240 ){
						data[i*step+j*channels+k] = 240;}
					else if(data[i*step+j*channels+k]>= 240  && data[i*step+j*channels+k] < 248 ){
						data[i*step+j*channels+k] = 248;}
					else{data[i*step+j*channels+k]= 255;}
				}
			}
		}
	}

	outputImg = imgBit;

	cvShowImage("Output", outputImg);
}

int main(int argc, char *argv[])
{
	int height,width,step,channels;
	unsigned char *data;

	setbuf(stdout, NULL);
	// load an image
	img= cvLoadImage("harry.jpg");
	if(!img){
		printf("Could not load image file: %s\n",argv[1]);
		exit(0);
	}

	outputImg = cvCreateImage(cvGetSize(img), 8, 3);
	cvCopy(img,outputImg);

	// get the image data
	height    = img->height;
	width     = img->width;
	step      = img->widthStep;
	channels  = img->nChannels;
	data      = (uchar *)img->imageData;


	printf("Processing a %dx%d image with %d channels\n",height,width,channels);
	printf("step = %d\n", step);


	// create a window --- show window
	cvNamedWindow("Input", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Output", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Control", CV_WINDOW_AUTOSIZE);

	createTrackbar("Bit", "Control", &_scrollbar, 5, update);
	update(0,0);

	cvShowImage("Input", img );

	// wait for a key
	cvWaitKey(0);

	// release the image
	cvReleaseImage(&img);

	return 0;
}
