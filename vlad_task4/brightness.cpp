#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <thread>
#include <future>
#include <chrono>
#include <algorithm>
#include <execution>
#include <mutex>

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

    int get()
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(m_end - m_start).count();
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
        "./brightness ./opencv2.jfif --brightness=-10 --contrast=1.5";

    std::cout << h << std::endl;
}

void addBrightness(cv::Mat &inputImage, cv::Mat &outputImage, double contrast, int brightness, int start, int step)
{
    // Classic for-loops
    for (int i = start; i < inputImage.rows; i += step)
    {
        for (int j = 0; j < inputImage.cols; j++)
        {
            cv::Vec3b &out = outputImage.at<cv::Vec3b>(i, j);
            for (int c = 0; c < inputImage.channels(); c++)
            {
                uchar rgb = inputImage.at<cv::Vec3b>(i, j)[c];
                out[c] = cv::saturate_cast<uchar>(contrast * rgb + brightness);
            }
        }
    }
}

void useSequentialLoop(cv::Mat &src, cv::Mat &dest, double contrast, int brightness)
{
    addBrightness(src, dest, contrast, brightness, 0, 1);
}

void useThreadPool(cv::Mat &src, cv::Mat &dest, double contrast, int brightness)
{
    int threads = std::thread::hardware_concurrency();
    std::vector<std::shared_future<void>> tasks;
    for (int i = 0; i < threads; i++)
    {
        std::shared_future<void> task = std::async(
            std::launch::async,
            addBrightness,
            std::ref(src),
            std::ref(dest), contrast, brightness, i, threads);
        tasks.push_back(task);
    }

    for (auto &task : tasks)
    {
        task.get();
    }
}

void useStandardParallelForEach(cv::Mat &img, double contrast, int brightness)
{
    std::for_each(
        std::execution::par,
        img.begin<cv::Vec3b>(),
        img.end<cv::Vec3b>(),
        [&](cv::Vec3b &pixel)
        {
            for (int c = 0; c < img.channels(); c++)
            {
                pixel[c] = cv::saturate_cast<uchar>(contrast * pixel[c] + brightness);
            }
        });
}

void useStandardTransform(cv::Mat &src, cv::Mat &dest, double contrast, int brightness)
{
    std::transform(
        std::execution::par,
        src.begin<cv::Vec3b>(),
        src.end<cv::Vec3b>(),
        dest.begin<cv::Vec3b>(),
        [&](const cv::Vec3b &bgr)
        {
            cv::Vec3b res;
            for(int c = 0; c < src.channels(); c++)
            {
                res[c] = cv::saturate_cast<uchar>(contrast * bgr[c] + brightness);
            }
            return res;
        }
    );
}

int main(int argc, char **argv)
{
    cv::CommandLineParser parser(argc, argv,
                                 "{help h ||}"
                                 "{@filename | ./opencv2.jfif | Image file to process}"
                                 "{brightness b | 0 | Brightness that will be added to the image }"
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
    cv::Mat seqImage;
    cv::Mat asyncImage;
    cv::Mat foreachImage;
    cv::Mat transformImage;
    Timer t;

    int seqAverage = 0;
    int threadPoolAverage = 0;
    int forEachAverage = 0;
    int transformAverage = 0;

    for (int i = 0; i < 5; i++)
    {
        seqImage = cv::Mat::zeros(originalImage.rows, originalImage.cols, originalImage.type());
        t.start();
        useSequentialLoop(originalImage, seqImage, contrast, brightness);
        t.stop();
        seqAverage += t.get();
        t.reset();
        asyncImage = cv::Mat::zeros(originalImage.rows, originalImage.cols, originalImage.type());
        t.start();
        useThreadPool(originalImage, asyncImage, contrast, brightness);
        t.stop();
        threadPoolAverage += t.get();
        t.reset();
        foreachImage = originalImage.clone();
        t.start();
        useStandardParallelForEach(foreachImage, contrast, brightness);
        t.stop();
        forEachAverage += t.get();
        t.reset();
        transformImage = cv::Mat::zeros(originalImage.rows, originalImage.cols, originalImage.type());
        t.start();
        useStandardTransform(originalImage, transformImage, contrast, brightness);
        t.stop();
        transformAverage += t.get();
        t.reset();
    }

    std::cout << "Sequential average: " << seqAverage / 5 << std::endl
              << "Thread Pool average: " << threadPoolAverage / 5 << std::endl
              << "for_each average: " << forEachAverage / 5 << std::endl
              << "transform average: " << transformAverage / 5 << std::endl;

    // Show windows
    std::string windowOriginalImage = "Original Image";
    std::string windowProcessedImage = "Processed Image";
    std::string windowSeqImage = "Sequential Image";
    std::string windowParForEach = "Parallel std::forEach";
    std::string windowTransform = "Parallel std::transform";

    cv::namedWindow(windowOriginalImage, cv::WINDOW_NORMAL);
    cv::namedWindow(windowProcessedImage, cv::WINDOW_NORMAL);
    cv::namedWindow(windowSeqImage, cv::WINDOW_NORMAL);
    cv::namedWindow(windowParForEach, cv::WINDOW_NORMAL);
    cv::namedWindow(windowTransform, cv::WINDOW_NORMAL);

    cv::imshow(windowOriginalImage, originalImage);
    cv::imshow(windowSeqImage, seqImage);
    cv::imshow(windowProcessedImage, asyncImage);
    cv::imshow(windowParForEach, foreachImage);
    cv::imshow(windowTransform, transformImage);

    cv::waitKey(0);
    std::cout << std::thread::hardware_concurrency() << std::endl;
    return 0;
}