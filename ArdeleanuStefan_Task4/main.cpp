#include <opencv2/highgui.hpp>
#include <iostream>
int main(int argc, char **argv)
{
    cv::Mat input_image;

    input_image = cv::imread("Lenna.png", cv::IMREAD_COLOR);

    if (!input_image.data)
    {
        std::cout << "Could not open file" << std::endl;
        return -1;
    }

    cv::Mat output_image = cv::Mat::zeros(input_image.size(), input_image.type());

    double alpha = 1.0; // contrast
    int beta = 0;       // brightness

    std::cout << "Enter the alpha value for contrast [1.0;3.0]: ";
    std::cin >> alpha;
    std::cout << "Enter the beta value for brightness [0;100]: ";
    std::cin >> beta;

    for( int y = 0; y < input_image.rows; y++ ) {
        for( int x = 0; x < input_image.cols; x++ ) {
            for( int c = 0; c < input_image.channels(); c++ ) {
                output_image.at<cv::Vec3b>(y,x)[c] =
                  cv::saturate_cast<uchar>( alpha*input_image.at<cv::Vec3b>(y,x)[c] + beta );
            }
        }
    }

    cv::namedWindow("Input Image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Output Image", cv::WINDOW_AUTOSIZE);
    
    cv::moveWindow("Input Image", 200,200);
    cv::moveWindow("Output Image", input_image.cols+400,200);

    cv::imshow("Input Image", input_image);
    cv::imshow("Output Image", output_image);

    cv::waitKey(0);

    return 0;
}