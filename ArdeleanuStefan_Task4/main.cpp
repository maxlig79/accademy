#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <chrono>
#include <execution>

using namespace std::chrono;

cv::Mat ContrastBrightnessForeach(const cv::Mat &input_image, double alpha, int beta)
{
    cv::Mat output_image = input_image.clone();

    std::for_each(
        std::execution::par,
        output_image.begin<cv::Vec3b>(),
        output_image.end<cv::Vec3b>(),
        [&](cv::Vec3b &pixel)
        {
            for (int c = 0; c < output_image.channels(); c++)
            {
                pixel[c] = cv::saturate_cast<uchar>(alpha * pixel[c] + beta);
            }
        });
    return output_image;
}

cv::Mat ContrastBrightnessSimple(const cv::Mat &input_image, double alpha, int beta)
{
    cv::Mat output_image = cv::Mat::zeros(input_image.size(), input_image.type());

    for (int y = 0; y < input_image.rows; y++)
    {
        for (int x = 0; x < input_image.cols; x++)
        {
            for (int c = 0; c < input_image.channels(); c++)
            {
                output_image.at<cv::Vec3b>(y, x)[c] =
                    cv::saturate_cast<uchar>(alpha * input_image.at<cv::Vec3b>(y, x)[c] + beta);
            }
        }
    }
    return output_image;
}

int main(int argc, char **argv)
{
    cv::Mat input_image;

    input_image = cv::imread("Lenna.png", cv::IMREAD_COLOR);

    if (!input_image.data)
    {
        std::cout << "Could not open file" << std::endl;
        return -1;
    }

    double alpha = 1.0; // contrast
    int beta = 0;       // brightness

    std::cout << "Enter the alpha value for contrast [1.0;3.0]: ";
    std::cin >> alpha;
    std::cout << "Enter the beta value for brightness [0;100]: ";
    std::cin >> beta;

    auto start_simple = high_resolution_clock::now();
    cv::Mat output_image_simple = ContrastBrightnessSimple(input_image, alpha, beta);
    auto stop_simple = high_resolution_clock::now();
    std::cout << "Simple Computation: " << duration_cast<microseconds>(stop_simple - start_simple).count() << std::endl;

    auto start_foreach = high_resolution_clock::now();
    cv::Mat output_image_foreach = ContrastBrightnessForeach(input_image, alpha, beta);
    auto stop_foreach = high_resolution_clock::now();
    std::cout << "Foreach Computation: " << duration_cast<microseconds>(stop_foreach - start_foreach).count() << std::endl;

    cv::namedWindow("Input Image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Output Image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Foreach Output Image", cv::WINDOW_AUTOSIZE);

    cv::moveWindow("Input Image", 200, 200);
    cv::moveWindow("Output Image", input_image.cols + 20, 200);
    cv::moveWindow("Foreach Output Image", input_image.cols * 2 + 20, 200);

    cv::imshow("Input Image", input_image);
    cv::imshow("Output Image", output_image_simple);
    cv::imshow("Foreach Output Image", output_image_foreach);

    cv::waitKey(0);

    return 0;
}