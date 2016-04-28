//CSC495
//aom ball pan
//note most 24 bit -->15 12 9 6 3
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>


// Initial values
//int _bitMin = 3;
//int _bitMax = 24;

//void updateBit(int arg, void*) {
	//int
//}

int main(int argc, char *argv[])
{
  IplImage* img = 0;
  int height,width,step,channels;
  unsigned char *data, *data_r, *data_g, *data_b, *data_rgb_weighted, *data_rgb_avg, *data_24bits,*data_sepia,
  *data_binary,*data_8bits, *data_15bits,*data_12bits,*data_9bits,*data_6bits,*data_3bits;




  int i,j,k;

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

  //cvNamedWindow( "Copy" );
  //cvNamedWindow( "Gray scale (weighted)" );
  //cvNamedWindow( "Gray scale (average)" );
  //cvNamedWindow( "Use red color channel" );
  //cvNamedWindow( "Use green color channel" );
  //cvNamedWindow( "Use blue color channel" );
  //cvNamedWindow( "8 bit gray scale (one channel)" ); //a
  //cvNamedWindow( "24 bit gray scale (three channel)" ); //b
  cvNamedWindow( "Binary" ); //c
  cvNamedWindow( "Sepia" ); //d



  // Create an image for the output
  IplImage* copy = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 ); //three channels.
  cvCopy(img, copy);

  IplImage* out_r = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* out_g = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* out_b = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* out_rgb_avg = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* out_rgb_weighted = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );

//-------------------------------
  IplImage* out_3bits =  cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* out_6bits =  cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* out_9bits =  cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* out_12bits = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* out_15bits = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
//--------------------------------------

  IplImage* out_8bits = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 1 ); //one channel.
  IplImage* out_24bits = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 ); //three channel.
  IplImage* out_binary = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 1 );
  IplImage* out_sepia = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );


  data_rgb_avg = (uchar *) out_rgb_avg->imageData;
  data_rgb_weighted = (uchar *) out_rgb_weighted->imageData;
  data_r = (uchar *) out_r->imageData;
  data_g = (uchar *) out_g->imageData;
  data_b = (uchar *) out_b->imageData;
  data_3bits = (uchar *) out_3bits->imageData;
  data_9bits = (uchar *) out_9bits->imageData;
  data_6bits = (uchar *) out_6bits->imageData;
  data_8bits = (uchar *) out_8bits->imageData;
  data_12bits = (uchar *) out_12bits->imageData;
  data_15bits = (uchar *) out_15bits->imageData;
  data_24bits = (uchar *) out_24bits->imageData;
  data_binary = (uchar *) out_binary->imageData;
  data_sepia = (uchar *) out_sepia->imageData;


  int intensity_val_avg = 0;
  uchar intensity_val_weighted = 0;


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


		  intensity_val_avg = 0;
		  for(k=0;k<channels;k++){
			  intensity_val_avg += data[i*step+j*channels+k];
		  }
		  //Intensity_val_avg is equal to (R+G+B)/3.0;
		  intensity_val_avg = (uchar) (intensity_val_avg /3.0);

		  // Weighted intensity (Y) of RGB.
		  // Y = 0.2126*R + 0.7152*G + 0.0722*B.
		  intensity_val_weighted = (uchar) (0.2126 * data[i*step+j*channels+2])+
		  				  (uchar) (0.7152 * data[i*step+j*channels+1]) +
		  				  (uchar) (0.0722 * data[i*step+j*channels+0]);


		  // Three channels.
		  for(k=0;k<channels;k++){
			  data_rgb_avg[i*step+j*channels+k]= (uchar) intensity_val_avg;
			  data_rgb_weighted[i*step+j*channels+k]= (uchar) intensity_val_weighted;
			  data_r[i*step+j*channels+k]= data[i*step+j*channels+2];
			  data_g[i*step+j*channels+k]= data[i*step+j*channels+1];
			  data_b[i*step+j*channels+k]= data[i*step+j*channels+0];

			  data_24bits[i*step+j*channels+k]= (uchar) intensity_val_weighted;
		  }


		  // One channel.
		  int step_3 = step/3;
		  data_8bits[i*step_3+j]= (uchar) intensity_val_weighted; //change color image to gray 8 bit



		  // binary = black white 128(1 bit)
		  int blackwhite = 0;
		  blackwhite = data[i*step+j*channels+2]*11 + data[i*step+j*channels+1]*16 + data[i*step+j*channels+0]*5;
		  blackwhite = (uchar) (blackwhite/32);

		  if(blackwhite>=128){blackwhite=255;}

		  data_binary[i*step_3+j] = (uchar) blackwhite;

		  //sepia

		  int r = .393 * data[i*step+j*channels+2] + .768 * data[i*step+j*channels+1] + .189 * data[i*step+j*channels+0];
		  		  int g = .349 * data[i*step+j*channels+2] + .686 * data[i*step+j*channels+1] + .168 * data[i*step+j*channels+0];
		  		  int b = .272 * data[i*step+j*channels+2] + .534 * data[i*step+j*channels+1] + .131 * data[i*step+j*channels+0];

		  		  if(r>=255){r=255;}	data_sepia[i*step+j*channels+2] = r;
		  		  if(g>=255){g=255;}	data_sepia[i*step+j*channels+1] = g;
		  		  if(b>=255){b=255;}	data_sepia[i*step+j*channels+0] = b;


	  }
  }

  //create window
  //createTrackbar("Value-L", "After", &_valueLower, 255,updateHueSaturationValue);

  // show the image

  //cvShowImage("Copy", copy);
  //cvShowImage("Gray scale (average)", out_rgb_avg);
  //cvShowImage("Gray scale (weighted)", out_rgb_weighted);

  cvShowImage("mainWin", img );
  cvShowImage("8 bit gray scale (one channel)", out_8bits);
  cvShowImage("3 bits",out_3bits);
  cvShowImage("6 bits)", out_6bits);
  cvShowImage("9 bits",out_9bits);
  cvShowImage("12 bits",out_12bits);
  cvShowImage("15 bits",out_15bits);
  cvShowImage("24 bit gray scale (three channel)", out_24bits);
  cvShowImage("Binary", out_binary);
  cvShowImage("Sepia", out_sepia);

  // wait for a key
  cvWaitKey(0);

  // release the image
  cvReleaseImage(&img);
  cvReleaseImage(&copy);
  cvReleaseImage(&out_rgb_avg);
  cvReleaseImage(&out_rgb_weighted);
  cvReleaseImage(&out_3bits);
  cvReleaseImage(&out_6bits);
  cvReleaseImage(&out_8bits);
  cvReleaseImage(&out_9bits);
  cvReleaseImage(&out_12bits);
  cvReleaseImage(&out_15bits);
  cvReleaseImage(&out_24bits);
  cvReleaseImage(&out_binary);
  cvReleaseImage(&out_sepia);

  return 0;
}
