#include <iostream>
#include <map>
#include <limits>
#include "opencv2/core.hpp"
#include "opencv2/calib3d.hpp"


#include "opencv2/viz.hpp"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"

#define MIDDLE_COL (frame.cols / 2)
#define MIDDLE_ROW (frame.rows / 2)

using namespace std;
using namespace cv;

int main(int argc, char** argv )
{     
    //-----------------------------------------------------------------------------------------------------------------------
    if( argc != 2){
       cerr << "Not Enouth Parameter. ./ProgramName [video path]" << endl;
       return -1;
    }
    
    char* myPath= argv[1];
    
    cout << "Path: " << myPath << endl;
    
//    Mat imageL = imread( myPath, IMREAD_UNCHANGED );
//    
//    if(!imageL.data | !imageR.data){
//        cout << "Cannot read an image file " << endl;
//        return -1;
//    }
    //-----------------------------------------------------------------------------------------------------------------------

    VideoCapture vid(myPath);
    
    if(!vid.isOpened()){  // check if we succeeded
        cout << "Video konnte nicht geöffnet werden" << endl;
        return -1;
    }
    
    CascadeClassifier ccfilter("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml");
    
    double cframes = vid.get(CAP_PROP_FRAME_COUNT);
    //cout << "Frames: " << cframes << endl << "Vid Length: " << ((0.04166)*cframes) << endl;

    double size = 61.5/cframes;
    double delta;
    Point P1, P2;
    vector<Rect> a;
    
    
    for(;;){
        Mat frame;
        vid >> frame;
        
        //2a
        a.clear();
        ccfilter.detectMultiScale(frame, a, 1.7, 3, 0);
        
        for(auto rect : a){
            rectangle(frame, rect, Scalar(0,0,255), 1, LINE_8, 0);
        }
        
        //2a end
        
		/*
		//Show length of video
        delta = size*vid.get(CAP_PROP_POS_FRAMES);
        P1 = Point(MIDDLE_COL - (61.5 - delta), MIDDLE_ROW-(61.5 - delta));
        P2 = Point(MIDDLE_COL + (61.5 - delta), MIDDLE_ROW+(61.5 - delta));
        rectangle(frame, P1, P2, Scalar(0,255,0), 1, LINE_8, 0);
		*/
        
        imshow("Matrix",frame);
        //if(waitKey(41.66) >= 0)
        if(waitKey(1) >= 0)
            break;
        else if(vid.get(CAP_PROP_POS_FRAMES) == cframes)
			break;
    }
    return 0;
}
