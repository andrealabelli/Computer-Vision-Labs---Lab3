#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

typedef Vec<uchar, 3> Vec3b;
void onMouse(int event, int x, int y, int f, void *userdata);


//Task 2

int main(int argc, char** argv )
{
    Mat input_img = imread("../../robocup.jpg");

    if (!input_img.data)
    {
        printf(" No image found in the path! \n");
        return -1;
    }

    namedWindow("Img", WINDOW_KEEPRATIO);
    imshow("Img", input_img);
    
    setMouseCallback("Img", onMouse, (void*)&input_img);

    waitKey(0);

    return 0;
}


void onMouse(int event, int x, int y, int f, void *userdata)
{
    //If the left button is pressed
    if(event == EVENT_LBUTTONDOWN)
    {
        //Retrieving the image from the main
        Mat img = *(Mat*) userdata;
        Mat img_out = img.clone();

        cout << "\n\nB = " << static_cast<int>(img_out.at<Vec3b>(y, x)[0]);
        cout << "\nG = " << static_cast<int>(img_out.at<Vec3b>(y, x)[1]);
        cout << "\nR = " << static_cast<int>(img_out.at<Vec3b>(y, x)[2]);

    }

}
