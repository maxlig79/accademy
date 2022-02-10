#include <opencv2/highgui.hpp>
#include <iostream>
int main( int argc, char** argv )
{
    cv::Mat image;
    image = cv::imread("Ana.png",cv::IMREAD_COLOR);
    if(! image.data)
        {
            std::cout<<"Could not open file" << std::endl;
            return -1;
        }
    cv::namedWindow("Ana image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Ana image", image);
    cv::waitKey(0);
    return 0;
}