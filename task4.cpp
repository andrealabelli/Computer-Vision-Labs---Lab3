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
    Mat input_img = imread("C:/Users/andre/OneDrive/Desktop/Lab_3/robocup.jpg");

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
        Mat mask = Mat::zeros(img_out.size(), CV_8UC1);

        //Preventing segfaults for looking over the image boundaries
        if(y + NEIGHBORHOOD_Y> img_out.rows || 
        x + NEIGHBORHOOD_X > img_out.cols) return;

        //Mean on the neighborhood
        Rect rect (x, y, NEIGHBORHOOD_X, NEIGHBORHOOD_Y);
        Scalar mea = mean(img_out(rect));

        cout << "\nMean: \n" << "B = " << mea[0] << "\nG = " << mea[1] << "\nR = " << mea[2] << endl;

        int treshold;
        cout << "\n\nInsert a value for the treshold: " << endl;
        cin >> treshold;

        Scalar referencecol(mea[0], mea[1], mea[2]);

        for(int i = 0; i < img_out.rows; i++)
        {
            for(int j = 0; j < img_out.cols; j++)
            {
                Scalar current_pixel = img_out.at<Vec3b>(i, j);

                double dist_fromB = abs(current_pixel[0] - referencecol[0]);
                double dist_fromG = abs(current_pixel[1] - referencecol[1]);
                double dist_fromR = abs(current_pixel[2] - referencecol[2]);

                if(dist_fromB <= treshold && dist_fromG <= treshold && dist_fromR <= treshold)
                {
                    mask.at<uchar>(i, j) = 255;
                }else{
                    mask.at<uchar>(i, j) = 0;
                }

            }
        }

        imshow("Mask", mask);
    }
}