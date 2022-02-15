#include "utils.hpp"

cv::Mat brightnessContrastLambda( const cv::Mat &image, int brightness, double contrast )
{
    cv::Mat modifiedImage = image.clone();

    std::for_each(
        std::execution::par,
        modifiedImage.begin <cv::Vec3b> (),
        modifiedImage.end <cv::Vec3b> (), 
        [&] (cv::Vec3b &intensity) 
        {
            for( int k = 0; k < modifiedImage.channels(); k++ )
            {
                intensity[k]= cv::saturate_cast <uchar> ( contrast * intensity[k] + brightness );
            }
        });
        
    return modifiedImage;
}

cv::Mat brightnessContrast( const cv::Mat &image, int brightness, double contrast )
{
    cv::Mat modifiedImage = image.clone();

    for( int i = 0; i < modifiedImage.cols; i++ )
    {
        for( int j = 0; j < modifiedImage.rows; j++ )
        {
            cv::Vec3b &intensity = modifiedImage.at <cv::Vec3b> (j,i) ;
            for( int k = 0; k < modifiedImage.channels(); k++ )
            {
                intensity.val[k] = cv::saturate_cast <uchar> ( contrast * intensity.val[k] + brightness );
            }
        }
    }
    return modifiedImage;
}

cv::Mat timer (const cv::Mat &image )
{
    using namespace std::chrono;

    auto start = high_resolution_clock::now();
    cv::Mat modifiedImage = brightnessContrastLambda( image, Brightness, Contrast );
    auto stop = high_resolution_clock::now();
    std::cout << "\nThe function call with lambda took " << 
                duration_cast <microseconds> ( stop - start ).count() << 
                " microseconds to execute" << std::endl;

    start = high_resolution_clock::now();
    modifiedImage = brightnessContrast( image, Brightness, Contrast );
    stop = high_resolution_clock::now();
    std::cout << "\nThe original function call took " << 
                duration_cast <microseconds> ( stop - start ).count() << 
                " microseconds to execute" << std::endl;

    return modifiedImage;
}

void display( const cv::Mat &image,const cv::Mat &modifiedImage )
{

    cv::imshow( WindowName1, image );
    cv::moveWindow( WindowName1, 200,0 );

    cv::imshow( WindowName2, modifiedImage );
    cv::moveWindow( WindowName2, 1000,0 );
    
    cv::waitKey();

    cv::destroyAllWindows;
}
