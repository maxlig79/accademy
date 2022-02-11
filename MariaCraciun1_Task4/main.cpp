#include <opencv2/highgui.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
const std::string WindowName1 = "Baby Luna";
const std::string WindowName2 = "Special Luna";
const std::string Photo = "Luna.jpg";
const double ScaleFactor = 0.4;
int Brightness = 20; // values in [0,100]
double Contrast = 1.2; //values in [0.0, 3.0]

int main( int argc, char** argv )
{
    cv::Mat photoLuna;
    
    photoLuna = cv::imread(Photo,cv::IMREAD_COLOR);

    cv::resize(photoLuna, photoLuna, cv::Size(), ScaleFactor, ScaleFactor);

    if(! photoLuna.data)
        {
            std::cout<<"Could not open file" << std::endl;
            return -1;
        }
    
    cv::Mat copyPhotoLuna = photoLuna.clone();

    for(int i=0; i<copyPhotoLuna.cols; i++)
    {
        for(int j=0; j<copyPhotoLuna.rows; j++)
        {
            cv::Vec3b &intensity = copyPhotoLuna.at<cv::Vec3b> (j,i);
            for(int k=0; k< copyPhotoLuna.channels(); k++)
            {
                intensity.val[k]= cv::saturate_cast<uchar>(Contrast * intensity.val[k] + Brightness);
            }
        }
    }

    cv::imshow(WindowName1, photoLuna);
    cv::moveWindow(WindowName1, 200,0);

    cv::imshow(WindowName2, copyPhotoLuna);
    cv::moveWindow(WindowName2, 1000,0);
    
    cv::waitKey();

    cv::destroyAllWindows;

    return 0;
}