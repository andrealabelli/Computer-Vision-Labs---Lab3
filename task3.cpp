#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define NEIGHBORHOOD_Y 9
#define NEIGHBORHOOD_X 9

typedef Vec<uchar, 3> Vec3b;

void onMouse(int event, int x, int y, int f, void *userdata);

int main(int argc, char** argv)
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

        //Preventing segfaults for looking over the image boundaries
        if(y + NEIGHBORHOOD_Y > img_out.rows || 
        x + NEIGHBORHOOD_X > img_out.cols) return;

        //Mean on the neighborhood
        Rect rect (x, y, NEIGHBORHOOD_X, NEIGHBORHOOD_Y);
        Scalar mea = mean(img_out(rect));

        cout << "\nMean: \n" << "B = " << mea[0] << "\nG = " << mea[1] << "\nR = " << mea[2] << endl;

    }

}