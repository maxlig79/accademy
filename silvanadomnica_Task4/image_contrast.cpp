#include <opencv2/highgui.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/opencv.hpp>
#include "Timer.h"
#include <algorithm>
#include <execution>

cv::Mat addBrightnessContrast(const cv::Mat &image, double contrast, double brightness)
{
    cv::Mat newImage = image.clone();
    std::for_each(std::execution::par,
                   newImage.begin<cv::Vec3b>(),
                   newImage.end<cv::Vec3b>(),
                   [newImage,contrast,brightness](cv::Vec3b &rgb)
                   {
                       for (int c = 0; c < newImage.channels(); c++)
                       {
                           rgb[c] = cv::saturate_cast<uchar>(contrast * rgb[c] + brightness);
                       }
                   });
    return newImage;
}
int main(int argc, char **argv)
{
    cv::Mat image;

    image = cv::imread("Lenna.png", cv::IMREAD_COLOR);

    if (!image.data)
    {
        std::cout << "Could not open file" << std::endl;
    }

    double contrast = 1.0;
    int brightness = 0;
    std::cout << "Enter the contrast value [1.0-3.0]: ";
    std::cin >> contrast;
    std::cout << "Enter the brightness value [0-100]: ";
    std::cin >> brightness;

    cv::Mat simpleImage = cv::Mat::zeros(image.size(), image.type());
    Timer timer1;
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            for (int c = 0; c < image.channels(); c++)
            {
                simpleImage.at<cv::Vec3b>(i, j)[c] = cv::saturate_cast<uchar>(contrast * image.at<cv::Vec3b>(i, j)[c] + brightness);
            }
        }
    }
    timer1.ShowResult("Simple: ");

    Timer timer2;
    cv::Mat foreachImage = addBrightnessContrast(image, contrast, brightness);
    timer2.ShowResult("For each: ");

    cv::namedWindow("Lenna image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Simple image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Foreach image", cv::WINDOW_AUTOSIZE);

    cv::imshow("Lenna image", image);
    cv::imshow("Simple image", simpleImage);
    cv::imshow("Foreach image", foreachImage);

    cv::moveWindow("Lenna image", 100, 200);
    cv::moveWindow("Simple image", 600, 200);
    cv::moveWindow("Foreach image", 1100, 200);

    cv::waitKey(0);
}