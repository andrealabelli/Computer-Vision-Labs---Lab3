#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//Task 1

int main(int argc, char** argv )
{
    //Task 1
    Mat img = imread("C:/Users/andre/OneDrive/Desktop/Lab_3/robocup.jpg");
    if (!img.data)
    {
        printf(" No image found in the path! \n");
        return -1;
    }

    namedWindow("Img", WINDOW_KEEPRATIO);
    imshow("Img", img);
    
    waitKey(0);

    return 0;

}