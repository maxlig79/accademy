#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <thread>
#include <future>
#include <chrono>
#include <algorithm>
#include <execution>

class Timer
{
private:
    std::chrono::time_point<std::chrono::steady_clock> m_start;
    std::chrono::time_point<std::chrono::steady_clock> m_end;

public:
    void reset()
    {
        m_start = std::chrono::steady_clock::time_point();
        m_end = std::chrono::steady_clock::time_point();
    }

    void start()
    {
        m_start = std::chrono::steady_clock::now();
    }

    void stop()
    {
        m_end = std::chrono::steady_clock::now();
    }

    void print(const std::string &str)
    {
        int micro = std::chrono::duration_cast<std::chrono::microseconds>(m_end - m_start).count();
        std::cout << str << ": " << micro << std::endl;
    }
};
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

void addBrightness(cv::Mat &image, double contrast, int brightness, int start, int step)
{
    //Classic for-loops
    for (int i = start; i < image.rows; i += step)
    {
        for (int j = 0; j < image.cols; j++)
        {
            for (int c = 0; c < image.channels(); c++)
            {
                uchar &rgb = image.at<cv::Vec3b>(i, j)[c];
                rgb = cv::saturate_cast<uchar>(contrast * rgb + brightness);
            }
        }
    }

    //Linear traversal of matrix
    /* for (int k = start; k < image.rows * image.cols; k += step)
    {
        int i = k / image.cols;
        int j = k % image.cols;
        for (int c = 0; c < image.channels(); c++)
        {
            uchar &rgb = image.at<cv::Vec3b>(i, j)[c];
            rgb = cv::saturate_cast<uchar>(contrast * rgb + brightness);
        }
    } */

    //MatIterator
    /* cv::MatIterator_<cv::Vec3b> it, end;

    for (it = image.begin<cv::Vec3b>() + start, end = image.end<cv::Vec3b>(); it != end; it += step)
    {
        for(int c = 0;c < image.channels(); c++)
        {
            (*it)[c] = cv::saturate_cast<uchar>(contrast * ((*it)[c]) + brightness);
        }

    } */
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
    if (contrast < 0)
    {
        std::cout << "Contrast must be greater or equal than zero" << std::endl;
        return -1;
    }
    cv::Mat originalImage = cv::imread(filename);
    cv::Mat seqImage = originalImage.clone();
    cv::Mat image = originalImage.clone();

    Timer t;
    // Sequential
    t.start();
    addBrightness(seqImage, contrast, brightness, 0, 1);
    t.stop();
    t.print("Sequential time");
    t.reset();

    // Parallel (std::async)
    t.start();
    int threads = std::thread::hardware_concurrency();
    std::vector<std::shared_future<void>> tasks;
    for (int i = 0; i < threads; i++)
    {
        std::shared_future<void> task = std::async(std::launch::async, addBrightness, std::ref(image), contrast, brightness, i, threads);
        tasks.push_back(task);
    }

    for (auto &task : tasks)
    {
        task.get();
    }
    t.stop();
    t.print("Parallel time");
    t.reset();

    // Parallel (std::for_each)
    cv::Mat foreachImage = originalImage.clone();
    t.start();
    std::for_each(
        std::execution::par,
        foreachImage.begin<cv::Vec3b>(),
        foreachImage.end<cv::Vec3b>(),
        [&](cv::Vec3b &pixel)
        {
            for (int c = 0; c < foreachImage.channels(); c++)
            {
                pixel[c] = cv::saturate_cast<uchar>(contrast * pixel[c] + brightness);
            }
        });
    t.stop();
    t.print("for_each");

    // Show windows
    std::string windowOriginalImage = "Original Image";
    std::string windowProcessedImage = "Processed Image";
    std::string windowSeqImage = "Sequential Image";
    std::string windowParForEach = "Parallel std::forEach";

    cv::namedWindow(windowOriginalImage, cv::WINDOW_NORMAL);
    cv::namedWindow(windowProcessedImage, cv::WINDOW_NORMAL);
    cv::namedWindow(windowSeqImage, cv::WINDOW_NORMAL);
    cv::namedWindow(windowParForEach, cv::WINDOW_NORMAL);

    cv::imshow(windowOriginalImage, originalImage);
    cv::imshow(windowProcessedImage, image);
    cv::imshow(windowSeqImage, seqImage);
    cv::imshow(windowParForEach, foreachImage);

    cv::waitKey(0);
    std::cout << std::thread::hardware_concurrency() << std::endl;
    return 0;
}