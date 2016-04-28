//CSC495
//aom ball pan
//note most 24 bit -->15 12 9 6 3
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>


int main(int argc, char *argv[])
{
  IplImage* img = 0;
  int height,width,step,channels,i,j,k;
  unsigned char *data,*data_15bits,*data_12bits,*data_9bits,*data_6bits,*data_3bits;

  setbuf(stdout, NULL);
  // load an image
  img= cvLoadImage("Truecolor.png");
  if(!img){
    printf("Could not load image file: %s\n",argv[1]);
    exit(0);
  }

  // get the image data
  height    = img->height;
  width     = img->width;
  step      = img->widthStep;
  channels  = img->nChannels;
  data      = (uchar *)img->imageData;


  printf("Processing a %dx%d image with %d channels\n",height,width,channels);
  printf("step = %d\n", step);


  // create a window --- show window
  cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE);
  cvMoveWindow("mainWin", 10, 10); //positioned at (x,y).


  // Create an image for the output

  IplImage* out_3bits =  cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* out_6bits =  cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* out_9bits =  cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* out_12bits = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* out_15bits = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );

  data_3bits = (uchar *) out_3bits->imageData;
  data_9bits = (uchar *) out_9bits->imageData;
  data_6bits = (uchar *) out_6bits->imageData;
  data_12bits = (uchar *) out_12bits->imageData;
  data_15bits = (uchar *) out_15bits->imageData;

  for(i=0;i<height;i++){
	  for(j=0;j<width;j++){

		  //3bit
		  for(k=0;k<channels;k++){
			  if(data[i*step+j*channels+k]>127){
				  data_3bits[i*step+j*channels+k] = 255;}
			  else{data_3bits[i*step+j*channels+k]= 0;}
		  }
		  //6bit
		  for(k=0;k<channels;k++){
			  if(data[i*step+j*channels+k] >= 0 && data[i*step+j*channels+k] < 64 ){
				  data_6bits[i*step+j*channels+k] = 64;}
			  else if(data[i*step+j*channels+k]>= 64 && data[i*step+j*channels+k] < 128){
		 		  data_6bits[i*step+j*channels+k] = 128;}
			  else if(data[i*step+j*channels+k]>= 128 && data[i*step+j*channels+k] < 192 ){
		 		  data_6bits[i*step+j*channels+k] = 192;}
			  else{data_6bits[i*step+j*channels+k]= 255;}
		  }

		  //9bit
		  for(k=0;k<channels;k++){
			  if(data[i*step+j*channels+k]>= 0&& data[i*step+j*channels+k] < 32 ){
 		 		  data_9bits[i*step+j*channels+k] = 32;}
			  else if(data[i*step+j*channels+k]>= 32&& data[i*step+j*channels+k] < 64 ){
				  data_9bits[i*step+j*channels+k] = 64;}
			  else if(data[i*step+j*channels+k]>=64  && data[i*step+j*channels+k] < 96 ){
 		 		  data_9bits[i*step+j*channels+k] = 96;}
			  else if(data[i*step+j*channels+k]>= 96&& data[i*step+j*channels+k] < 128 ){
 		 		  data_9bits[i*step+j*channels+k] = 128;}
			  else if(data[i*step+j*channels+k]>= 128&& data[i*step+j*channels+k] < 160 ){
				  data_9bits[i*step+j*channels+k] = 160;}
			  else if(data[i*step+j*channels+k]>= 160&& data[i*step+j*channels+k] < 192 ){
				  data_9bits[i*step+j*channels+k] = 192;}
			  else if(data[i*step+j*channels+k]>= 192&& data[i*step+j*channels+k] < 224 ){
				  data_9bits[i*step+j*channels+k] = 224;}
			  else{data_9bits[i*step+j*channels+k]= 255;}
		  }

		 	//12bit
		 	for(k=0;k<channels;k++){
		 		if(data[i*step+j*channels+k]>= 0&& data[i*step+j*channels+k] < 16 ){
		 		 	data_12bits[i*step+j*channels+k] = 16;}
		 		else if(data[i*step+j*channels+k]>= 16 && data[i*step+j*channels+k] < 32 ){
		 			data_12bits[i*step+j*channels+k] = 32;}
		 		else if(data[i*step+j*channels+k]>= 32 && data[i*step+j*channels+k] < 64 ){
		 			data_12bits[i*step+j*channels+k] = 64;}
		 		else if(data[i*step+j*channels+k]>= 64 && data[i*step+j*channels+k] < 80 ){
		 		 	data_12bits[i*step+j*channels+k] = 80;}
		 		else if(data[i*step+j*channels+k]>= 80 && data[i*step+j*channels+k] < 96 ){
		 		 	data_12bits[i*step+j*channels+k] = 96;}
		 		else if(data[i*step+j*channels+k]>= 96 && data[i*step+j*channels+k] < 112 ){
		 		 	data_12bits[i*step+j*channels+k] = 112;}
		 		else if(data[i*step+j*channels+k]>= 112 && data[i*step+j*channels+k] < 128 ){
		 		 	data_12bits[i*step+j*channels+k] = 128;}
		 		else if(data[i*step+j*channels+k]>= 128 && data[i*step+j*channels+k] < 144 ){
		 		 	data_12bits[i*step+j*channels+k] = 144;}
		 		else if(data[i*step+j*channels+k]>= 144 && data[i*step+j*channels+k] < 160 ){
		 		 	data_12bits[i*step+j*channels+k] = 160;}
		 		else if(data[i*step+j*channels+k]>= 160 && data[i*step+j*channels+k] < 176 ){
		 		 	data_12bits[i*step+j*channels+k] = 176;}
		 		else if(data[i*step+j*channels+k]>= 176 && data[i*step+j*channels+k] < 192 ){
		 		 	data_12bits[i*step+j*channels+k] = 192;}
		 		else if(data[i*step+j*channels+k]>= 192 && data[i*step+j*channels+k] < 208 ){
		 		 	data_12bits[i*step+j*channels+k] = 208;}
		 		else if(data[i*step+j*channels+k]>= 208 && data[i*step+j*channels+k] < 224 ){
		 		 	data_12bits[i*step+j*channels+k] = 224;}
		 		else if(data[i*step+j*channels+k]>= 224 && data[i*step+j*channels+k] < 240 ){
		 		 	data_12bits[i*step+j*channels+k] = 240;}
		 		else{data_12bits[i*step+j*channels+k]= 255;}
		 	}

		 	//15 bit == 32 case
		 	for(k=0;k<channels;k++){
			 	 if(data[i*step+j*channels+k]>= 0 && data[i*step+j*channels+k] < 8 ){
						 data_15bits[i*step+j*channels+k] = 8;}
					else if(data[i*step+j*channels+k]>= 8 && data[i*step+j*channels+k] <16 ){
						 data_15bits[i*step+j*channels+k] = 16;}
					else if(data[i*step+j*channels+k]>= 16 && data[i*step+j*channels+k] < 24 ){
						 data_15bits[i*step+j*channels+k] = 24;}
					else if(data[i*step+j*channels+k]>= 24 && data[i*step+j*channels+k] < 32 ){
						 data_15bits[i*step+j*channels+k] = 32;}
					else if(data[i*step+j*channels+k]>= 32 && data[i*step+j*channels+k] < 40 ){
						data_15bits[i*step+j*channels+k] = 40;}
					else if(data[i*step+j*channels+k]>= 40 && data[i*step+j*channels+k] < 48 ){
						data_15bits[i*step+j*channels+k] = 48;}
					else if(data[i*step+j*channels+k]>= 48 && data[i*step+j*channels+k] < 56 ){
						data_15bits[i*step+j*channels+k] = 56;}
					else if(data[i*step+j*channels+k]>= 56 && data[i*step+j*channels+k] < 64 ){
						data_15bits[i*step+j*channels+k] = 64;}
					else if(data[i*step+j*channels+k]>= 64 && data[i*step+j*channels+k] < 72 ){
						data_15bits[i*step+j*channels+k] = 72;}
					else if(data[i*step+j*channels+k]>= 72 && data[i*step+j*channels+k] < 80 ){
						data_15bits[i*step+j*channels+k] = 80;}
					else if(data[i*step+j*channels+k]>= 80 && data[i*step+j*channels+k] < 88 ){
						data_15bits[i*step+j*channels+k] = 88;}
					else if(data[i*step+j*channels+k]>= 88 && data[i*step+j*channels+k] < 96 ){
						data_15bits[i*step+j*channels+k] = 96;}
					else if(data[i*step+j*channels+k]>= 96 && data[i*step+j*channels+k] < 104 ){
						 data_15bits[i*step+j*channels+k] = 104;}
					else if(data[i*step+j*channels+k]>= 104 && data[i*step+j*channels+k] < 112 ){
						 data_15bits[i*step+j*channels+k] = 112;}
					else if(data[i*step+j*channels+k]>= 112 && data[i*step+j*channels+k] < 120 ){
						 data_15bits[i*step+j*channels+k] = 120;}
					else if(data[i*step+j*channels+k]>= 120 && data[i*step+j*channels+k] < 128 ){
						 data_15bits[i*step+j*channels+k] = 128;}
					else if(data[i*step+j*channels+k]>= 128 && data[i*step+j*channels+k] < 136 ){
						 data_15bits[i*step+j*channels+k] = 136;}
					else if(data[i*step+j*channels+k]>= 136 && data[i*step+j*channels+k] < 144 ){
						 data_15bits[i*step+j*channels+k] = 144;}
					else if(data[i*step+j*channels+k]>= 144 && data[i*step+j*channels+k] < 152 ){
						 data_15bits[i*step+j*channels+k] = 152;}
					else if(data[i*step+j*channels+k]>= 152 && data[i*step+j*channels+k] <160 ){
						 data_15bits[i*step+j*channels+k] = 160;}
					else if(data[i*step+j*channels+k]>= 160 && data[i*step+j*channels+k] < 168 ){
						 data_15bits[i*step+j*channels+k] = 168;}
					else if(data[i*step+j*channels+k]>= 168 && data[i*step+j*channels+k] < 176 ){
						data_15bits[i*step+j*channels+k] = 176;}
					else if(data[i*step+j*channels+k]>= 176 && data[i*step+j*channels+k] < 184 ){
						data_15bits[i*step+j*channels+k] = 184;}
					else if(data[i*step+j*channels+k]>= 184 && data[i*step+j*channels+k] < 192 ){
						data_15bits[i*step+j*channels+k] =192;}
					else if(data[i*step+j*channels+k]>= 192 && data[i*step+j*channels+k] < 200 ){
						data_15bits[i*step+j*channels+k] = 200;}
					else if(data[i*step+j*channels+k]>= 200 && data[i*step+j*channels+k] < 208 ){
						data_15bits[i*step+j*channels+k] = 208;}
					else if(data[i*step+j*channels+k]>= 208 && data[i*step+j*channels+k] < 216 ){
						data_15bits[i*step+j*channels+k] = 216;}
					else if(data[i*step+j*channels+k]>= 216 && data[i*step+j*channels+k] < 224 ){
						data_15bits[i*step+j*channels+k] = 224;}
					else if(data[i*step+j*channels+k]>= 224 && data[i*step+j*channels+k] < 232 ){
						data_15bits[i*step+j*channels+k] = 232;}
					else if(data[i*step+j*channels+k]>= 232 && data[i*step+j*channels+k] < 240 ){
						data_15bits[i*step+j*channels+k] = 240;}
					else if(data[i*step+j*channels+k]>= 240  && data[i*step+j*channels+k] < 248 ){
						data_15bits[i*step+j*channels+k] = 248;}
					else{data_15bits[i*step+j*channels+k]= 255;}
				 }
	  	 }
  }

  // show the image

  cvShowImage("mainWin", img );
  cvShowImage("3 bits",  out_3bits);
  cvShowImage("6 bits)", out_6bits);
  cvShowImage("9 bits",  out_9bits);
  cvShowImage("12 bits", out_12bits);
  cvShowImage("15 bits", out_15bits);

  // wait for a key
  cvWaitKey(0);

  // release the image
  cvReleaseImage(&img);
  cvReleaseImage(&out_3bits);
  cvReleaseImage(&out_6bits);
  cvReleaseImage(&out_9bits);
  cvReleaseImage(&out_12bits);
  cvReleaseImage(&out_15bits);

  return 0;
}
