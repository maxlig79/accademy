#include <opencv2/highgui.hpp>
#include <opencv2/core/types.hpp>
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <execution>
#include <algorithm>
#include "new.hpp"

using namespace cv;

cv::Mat BrightnessContrast(const cv::Mat &image, double contrast, double brightness)
{
    cv::Mat new_Image = image.clone();
    std::for_each(
        new_Image.begin<cv::Vec3b>(),
        new_Image.end<cv::Vec3b>(),
        [new_Image, contrast, brightness](cv::Vec3b &img)
        {
            for (int k = 0; k < new_Image.channels(); k++)
            {
                img[k] = cv::saturate_cast<uchar>(contrast * img[k] + brightness);
            }
        });
    return new_Image;
}

int main(int argc, char **argv)
{
    cv::Mat image;
    image = cv::imread("Ana.png", cv::IMREAD_COLOR);
    if (!image.data)
    {
        std::cout << "Could not open file" << std::endl;
        return -1;
    }
    cv::Mat new_image = cv::Mat::zeros(image.size(), image.type());
    double contrast = 1.0;
    int brightness = 0;
    std::cout << "Enter the contrast value [1.0-5.0]: ";
    std::cin >> contrast;
    std::cout << "Enter the brightness value [0-100]: ";
    std::cin >> brightness;
    Timer t1;
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            for (int c = 0; c < image.channels(); c++)
            {
                new_image.at<cv::Vec3b>(i, j)[c] = cv::saturate_cast<uchar>(contrast * image.at<cv::Vec3b>(i, j)[c] + brightness);
            }
        }
    }
    t1.calculateTime("New image:");
    Timer t2;
    cv::Mat foreach_image = BrightnessContrast(image, contrast, brightness);

    t2.calculateTime("Foreach: ");

    cv::namedWindow("Ana image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("New image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Foreach image", cv::WINDOW_AUTOSIZE);

    cv::imshow("Ana image", image);
    cv::imshow("New image", new_image);
    cv::imshow("Foreach image", foreach_image);

    cv::moveWindow("Ana image", 200, 200);
    cv::moveWindow("New image", 500, 200);
    cv::moveWindow("Foreach image", 800, 200);

    cv::waitKey(0);
    return 0;
}