#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
  IplImage* img = 0;
  int height,width,step,channels;
  unsigned char *data;

  setbuf(stdout, NULL);
  // load an image
  img= cvLoadImage("9.jpg");
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

  printf("Processing a %d%d image with %d channels\n",height,width,channels);
  printf("step = %d\n", step);


  IplImage* imgRed = cvCreateImage(cvGetSize(img), 8, 1);
  IplImage* imgGreen = cvCreateImage(cvGetSize(img), 8, 1);
  IplImage* imgBlue = cvCreateImage(cvGetSize(img), 8, 1);
  IplImage* imgGrayscale = cvCreateImage(cvGetSize(img), 8, 1);
  cvSplit(img, imgBlue, imgGreen, imgRed, NULL);

  //change to grayscale
 // cvCvtColor(img, imgGrayscale, CV_RGB2GRAY);

  // create a window
  cvNamedWindow("Gray scale", CV_WINDOW_AUTOSIZE);
  cvNamedWindow( "Pseudo color" );

  // Create an image for the output
  IplImage* imgPseudoColor = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );

  //Pseudo coloring
  unsigned char *dataGrayscale;
  unsigned char *dataRed, *dataGreen, *dataBlue;
  dataRed = (uchar *)imgRed->imageData;
  dataGreen = (uchar *)imgGreen->imageData;
  dataBlue = (uchar *)imgBlue->imageData;
  dataGrayscale = (uchar *)imgGrayscale->imageData;



  int i,j;
 // uchar brightness;


		 //find max
		  int max = 0;
		  int min = 255; //min = brightness(white)




		  for(i=0;i<height;i++){
		  	  for(j=0;j<width;j++){
		  		  if(dataRed[i*width+j] > max){ max = dataRed[i*width+j]; }
		  		  if(dataGreen[i*width+j] > max){max = dataGreen[i*width+j];}
		  		  if(dataBlue[i*width+j] >max){max = dataBlue[i*width+j];}

		  	  }

		  }
		  printf("max_of_original = %d\n" ,max);

		  //find min
		  for(i=0;i<height;i++){
		  		for(j=0;j<width;j++){
		  		  	if(dataRed[i*width+j] < min){min = dataRed[i*width+j];}
		  		  	if(dataGreen[i*width+j] < min){min = dataGreen[i*width+j];}
		  		  	if(dataBlue[i*width+j] < min){min = dataBlue[i*width+j];}
		  		}
		  }
		  printf("min_of_original = %d\n" ,min);

		  //normalization RGB = (value - min) / (max - min)

		  for(i=0;i<height;i++){
		  			  for(j=0;j<width;j++){
		  				  dataRed[i*width+j] = 255* (dataRed[i*width+j]-min) / (max -min) ;
		  				  dataGreen[i*width+j] = 255*(dataGreen[i*width+j]-min ) / (max -min) ;
		  				  dataBlue[i*width+j] = 255*(dataBlue[i*width+j]-min )/ (max-min) ;
		  			  }
		  		  }

		  for(i=0;i<height;i++){
		  		  	  for(j=0;j<width;j++){
		  		  		  if(dataRed[i*width+j] > max){ max = dataRed[i*width+j]; }
		  		  		  if(dataGreen[i*width+j] > max){max = dataGreen[i*width+j];}
		  		  		  if(dataBlue[i*width+j] >max){max = dataBlue[i*width+j];}

		  		  	  }

		  		  }
		  printf("max_after_normalize = %d\n" ,max);

		  		  //find min
		  for(i=0;i<height;i++){
		  		for(j=0;j<width;j++){
		  		  	if(dataRed[i*width+j] < min){min = dataRed[i*width+j];}
		  		  	if(dataGreen[i*width+j] < min){min = dataGreen[i*width+j];}
		  		  	if(dataBlue[i*width+j] < min){min = dataBlue[i*width+j];}
		  		  }
		  }
		  printf("min_after_normalize = %d" ,min);


  // merge three planes back into one image
  cvMerge(imgBlue, imgGreen, imgRed, NULL, imgPseudoColor);


  // show the image
  cvShowImage("Gray scale", img );
  cvShowImage("Pseudo color", imgPseudoColor);

  // wait for a key
  cvWaitKey(0);

  // release the image
  cvReleaseImage(&imgGrayscale);
  cvReleaseImage(&imgPseudoColor);

  return 0;
}
