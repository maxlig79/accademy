#include "utils.hpp"

int main( int argc, char** argv )
{
    cv::Mat photoLuna;
    photoLuna = cv::imread( Photo,cv::IMREAD_COLOR );

    if(!photoLuna.data)
    {
        std::cout << "Could not open file" << std::endl;
        return -1;
    }
    
    cv::resize( photoLuna, photoLuna, cv::Size(), ScaleFactor, ScaleFactor );
    
    cv::Mat copyPhotoLuna = timer( photoLuna );

    display( photoLuna, copyPhotoLuna );

    return 0;
}
