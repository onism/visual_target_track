#include <highgui.h>
#include <cxcore.h>
#include <cv.h>
#include <iostream>

#include "adaboostDetect.h"
using namespace std;
/** Constant string for window title */
const char* WINDOW_TITLE = "Particle Filter";
/** Path to video file */
const char* VIDEO_PATH = "/home/sse/Downloads/Particle-Filter/data/fussgaengerzone.mp4";
/** Path to xml cascade with trained classificator */
const char* CASCADE_XML_PATH = "/home/sse/Downloads/Particle-Filter/data/cascades.xml";

int initDetection(adaboostDetect* detect)
{
	detect->cascade = cvLoadHaarClassifierCascade(CASCADE_XML_PATH, cvSize(20, 20));
	if (!detect->cascade)
	{
		return 0;
	}

	detect->flags = CV_HAAR_DO_CANNY_PRUNING;
	detect->maxR = 23;
	detect->minNeighbours = 3;
    detect->minSize = cvSize(10, 10);
    detect->maxSize = cvSize(40, 40);
    detect->scaleFactor = 1.1;
    return 1;

}

 


int main(int argc,char ** argv) {
    IplImage* frame;
    int frameNo = 0;
    int nheads = 0;
    int n;
    CvRect* region; // list of region aroud each detected head
    adaboostDetect* detect = new adaboostDetect;
    CvCapture* capture = cvCaptureFromAVI(VIDEO_PATH);

    assert(capture);
    assert(initDetection(detect));
    cvNamedWindow(WINDOW_TITLE,CV_WINDOW_AUTOSIZE);
    while(1)
    {
    	frame = cvQueryFrame(capture);
    	assert(frame);
    	if (frameNo == 0)
    	{
    	    nheads = detect->detectObject(frame,&region);
    	    cout<<"find objects number :"<<nheads<<endl;
    	    for (int i = 0; i < nheads; ++i)
    	    {
    	    	/* code */

    	    	CvRect region_s =  region[i];
    	    	int width = region_s.width;
                int height = region_s.height;
                int x =  region_s.x ;
                int y =  region_s.y;
                cout<<i<<" widht "<<width<<" height "<<height<<endl;
                CvScalar color;
                color = CV_RGB(0, 255, 0);
                cvRectangle(frame, cvPoint(x, y), cvPoint(width+x, height+y), color);
                CvFont font;
                cvInitFont(&font, CV_FONT_HERSHEY_PLAIN|CV_FONT_ITALIC, 1, 1, 0, 1);
                char buffer [4];
                sprintf (buffer, "%d",i);
                cvPutText(frame,buffer, cvPoint( x+5, y+5 ), &font,	cvScalar(255,255,255));
 
    	    }
    	    cvShowImage("result", frame);
    	     cvWaitKey();
    	    char ch = getchar();
    	  
    	}
    	 
    	nheads = detect->detectAndDraw(frame,&region);
    	   frameNo++;
        
        if ((cvWaitKey(10) & 255) == 27) {
            break;
        }

    	 
    }

    free(detect);
    
    cvReleaseCapture(&capture);
    cvDestroyWindow(WINDOW_TITLE);
    return 0;
}
