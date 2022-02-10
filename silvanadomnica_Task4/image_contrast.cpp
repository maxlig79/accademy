#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/core/types.hpp>

int main(int argc, char **argv)
{
    cv::Mat image;
    image = cv::imread("Lenna.png", 1);

    if (!image.data)
    {
        std::cout << "Could not open file" << std::endl;
        return -1;
    }
    cv::Mat new_image = cv::Mat::zeros(image.size(), image.type());
    double contrast = 1.0;
    int brightness = 0; // brightness
    std::cout << "Enter the contrast value [1.0-3.0]: ";
    std::cin >> contrast;
    std::cout << "Enter the brightness value [0-100]: ";
    std::cin >> brightness;
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            for (int c = 0; c < image.channels(); c++)
            {
             new_image.at<cv::Vec3b>(i, j)[c] = cv::saturate_cast<uchar>(contrast * image.at<cv::Vec3b>(i, j)[c] + brightness);
             std::cout<<image.channels()<<std::endl;
            }
        }
    }

    cv::namedWindow("Lenna image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Lenna image", image);
    cv::imshow("New Image", new_image);
    cv::waitKey(0);
    return 0;
}