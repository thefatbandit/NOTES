#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat img(500,500,CV_8UC1,Scalar(0));

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          img.at<uchar>(x,y)=255;
     }
     
     /*else if  ( event == EVENT_RBUTTONDOWN )
     {
          cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if  ( event == EVENT_MBUTTONDOWN )
     {
          cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if ( event == EVENT_MOUSEMOVE )
     {
          cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

     }*/
}

int main(int argc, char** argv)
{
     // Read image from file 

     //if fail to read the image
     if ( img.empty() ) 
     { 
          cout << "Error loading the image" << endl;
          return -1; 
     }

     //Create a window
     namedWindow("My Window", 1);

     //set the callback function for any mouse event
     setMouseCallback("My Window", CallBackFunc, NULL);

     //show the image
     imshow("My Window", img);

     // Wait until user press some key
     waitKey(0);

     return 0;

}