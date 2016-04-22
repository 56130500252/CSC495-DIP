
//CSC495/492: DIP
//pornchai@sit.kmutt.ac.th


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
  img= cvLoadImage("45.jpg");
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


  IplImage* imgRed = cvCreateImage(cvGetSize(img), 8, 1);
  IplImage* imgGreen = cvCreateImage(cvGetSize(img), 8, 1);
  IplImage* imgBlue = cvCreateImage(cvGetSize(img), 8, 1);
  IplImage* imgGrayscale = cvCreateImage(cvGetSize(img), 8, 1);

  //change to grayscale
  cvCvtColor(img, imgGrayscale, CV_RGB2GRAY);

  // create a window
  //cvNamedWindow("Gray scale", CV_WINDOW_AUTOSIZE);
  //cvNamedWindow( "Pseudo color" );

  // Create an image for the output
  IplImage* imgPseudoColorBlue = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* imgPseudoColorGreen = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* imgPseudoColorRed = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );
  IplImage* imgPseudoColorTry = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3 );


  //Pseudo coloring
  unsigned char *dataGrayscale;
  unsigned char *dataRed, *dataGreen, *dataBlue;
  dataRed = (uchar *)imgRed->imageData;
  dataGreen = (uchar *)imgGreen->imageData;
  dataBlue = (uchar *)imgBlue->imageData;
  dataGrayscale = (uchar *)imgGrayscale->imageData;



  int i,j;
  uchar val;
  for(i=0;i<height;i++){
	  for(j=0;j<width;j++){
		  val = dataGrayscale[i*width+j];
		  if(val<=128){
		  			  dataRed[i*width+j] = 0;
		  			  dataGreen[i*width+j] = val*2;
		  			  dataBlue[i*width+j] = 255-(val*2);
		  		  }
		  		if(val>128){
		  			  			  dataRed[i*width+j] = val*2;
		  			  			  dataGreen[i*width+j] = 255-(val*2);
		  			  			  dataBlue[i*width+j] = 0;
		  		  }
	  }
  }
  // merge three planes back into one image
    cvMerge(imgBlue, imgGreen, imgRed, NULL, imgPseudoColorBlue);

  for(i=0;i<height;i++){
  	  for(j=0;j<width;j++){
  		  val = dataGrayscale[i*width+j];

	//GREEN


				  dataRed[i*width+j] = val;
				  dataGreen[i*width+j]= 255;
				  dataBlue[i*width+j]= val;
  	  }
  }
  cvMerge(imgBlue, imgGreen, imgRed, NULL, imgPseudoColorGreen);

  for(i=0;i<height;i++){
    	  for(j=0;j<width;j++){
    		  val = dataGrayscale[i*width+j];



  				  dataRed[i*width+j] = 255;
  				  dataGreen[i*width+j]= val;
  				  dataBlue[i*width+j]= val;
    	  }
    }
    cvMerge(imgBlue, imgGreen, imgRed, NULL, imgPseudoColorRed);

  for(i=0;i<height;i++){
  	  for(j=0;j<width;j++){
  		  val = dataGrayscale[i*width+j];
  		  //blue


  			  dataRed[i*width+j] = 255;
  			  dataGreen[i*width+j]= val;
  			  dataBlue[i*width+j]= val;

        		  if(val >= 0 & val <= 21){
        		  				dataRed[i*width+j] = 255 ;
        		  				dataGreen[i*width+j] = 0;
        		  				dataBlue[i*width+j] = 0;
        		  			}
        		  			else if(val >= 22 & val <= 43){
        		  				dataRed[i*width+j] = 255;
        		  				dataGreen[i*width+j] = 127;
        		  				dataBlue[i*width+j] = 0;
        		  										}

        		  			else if(val >= 44 & val <= 65){
        		  				dataRed[i*width+j] = 255;
        		  				dataGreen[i*width+j] = 255;
        		  				dataBlue[i*width+j] = 0;
        		  							}

        		  			else if(val > 66 & val < 87){
        		  					dataRed[i*width+j] = 127;
        		  					dataGreen[i*width+j] = 255;     // Green
        		  					dataBlue[i*width+j] = 0;
        		  				}

        		  			else if(val >= 88 & val <= 109){
        		  					dataRed[i*width+j] = 0;
        		  					dataGreen[i*width+j] = 255;     //Yellow
        		  					dataBlue[i*width+j] = 0;
        		  				}

        		  			else if(val >= 110 & val <= 131){
        		  							dataRed[i*width+j] = 0;
        		  							dataGreen[i*width+j] = 255;
        		  							dataBlue[i*width+j] = 127;
        		  						}

        		  			else if(val >= 132 & val <= 153){
        		  										dataRed[i*width+j] = 0;
        		  										dataGreen[i*width+j] = 255;
        		  										dataBlue[i*width+j] = 255;
        		  									}


        		  			else if(val >= 154 & val <= 175){
        		  										dataRed[i*width+j] = 0;
        		  										dataGreen[i*width+j] = 127;
        		  										dataBlue[i*width+j] = 255;
        		  									}

        		  			else if(val >= 176 & val <= 197){
        		  										dataRed[i*width+j] = 0;
        		  										dataGreen[i*width+j] = 0;
        		  										dataBlue[i*width+j] = 255;
        		  									}
        		  			else if(val >= 198 & val <= 219){
        		  										dataRed[i*width+j] = 127;
        		  										dataGreen[i*width+j] = 0;
        		  										dataBlue[i*width+j] = 255;
        		  									}
        		  			else if(val >= 220 & val <= 241){
        		  										dataRed[i*width+j] = 255;
        		  										dataGreen[i*width+j] = 0;
        		  										dataBlue[i*width+j] = 127;
        		  									}
        		  			else{
        		  										dataRed[i*width+j] = 255;
        		  										dataGreen[i*width+j] = 0;
        		  										dataBlue[i*width+j] = 127;
        		  									}
        		  			}
      }



          // merge three planes back into one image
            cvMerge(imgBlue, imgGreen, imgRed, NULL, imgPseudoColorTry);

/*



*/







  // show the image
  cvShowImage("Gray scale", imgGrayscale );
  cvShowImage("Pseudo color Blue", imgPseudoColorBlue);
  cvShowImage("Pseudo color Green", imgPseudoColorGreen);
  cvShowImage("Pseudo color Red", imgPseudoColorRed);
  cvShowImage("Pseudo color Try", imgPseudoColorTry);


  // wait for a key
  cvWaitKey(0);

  // release the image
  cvReleaseImage(&imgGrayscale);
  cvReleaseImage(&imgPseudoColorBlue);
  cvReleaseImage(&imgPseudoColorGreen);
  cvReleaseImage(&imgPseudoColorRed);
  cvReleaseImage(&imgPseudoColorTry);
  return 0;
}


