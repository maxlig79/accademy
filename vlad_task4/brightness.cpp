#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

void help()
{
    std::string h =
        "This program increases the brightness of a given image\n"
        "Usage:\n"
        "[--help | -h  Prints this message]\n"
        "[--brightness | -b The amount of brightness added to the image (can't be a negative number)]\n"
        "[filename The image file]\n"
        "Example:\n"
        "./brightness ./opencv2.jfif --brightness=20";

    std::cout << h << std::endl;
}

int main(int argc, char **argv)
{
    cv::CommandLineParser parser(argc, argv,
                                 "{help h ||}"
                                 "{@filename | ./opencv2.jfif | Image file to process}"
                                 "{brightness b | 50 | Brightness that will be added to the image }"
                                 "{contrast c | 1 | Contrast, greater or equal than zero}"

    );

    std::string filename = parser.get<std::string>("@filename");
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    int brightness = parser.get<int>("brightness");
    double contrast = parser.get<double>("contrast");
    if(contrast < 0)
    {
        std::cout << "Contrast must be greater or equal than zero" << std::endl;
        return -1;
    }
    cv::Mat originalImage = cv::imread(filename);
    cv::Mat image = originalImage.clone();
    
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            cv::Vec3b &rgbPixel = image.at<cv::Vec3b>(i, j);
            rgbPixel[0] = cv::saturate_cast<uchar>(contrast * rgbPixel[0] + brightness);
            rgbPixel[1] = cv::saturate_cast<uchar>(contrast * rgbPixel[1] + brightness);
            rgbPixel[2] = cv::saturate_cast<uchar>(contrast * rgbPixel[2] + brightness);
        }
    }
    std::string windowOriginalImage = "Original Image";
    std::string windowProcessedImage = "Processed Image";

    cv::namedWindow(windowOriginalImage, cv::WINDOW_NORMAL);
    cv::namedWindow(windowProcessedImage, cv::WINDOW_NORMAL);
    
    cv::imshow(windowOriginalImage, originalImage);
    cv::imshow(windowProcessedImage, image);

    cv::waitKey(0);
    return 0;
}