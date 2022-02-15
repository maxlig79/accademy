#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <algorithm>
#include <execution>

const std::string WindowName1 = "Baby Luna";
const std::string WindowName2 = "Special Luna";
const std::string Photo = "Luna.jpg";
const double ScaleFactor = 0.4;
int Brightness = 20; // values in [0,100]
double Contrast = 1.2; //values in [0.0, 3.0]

cv::Mat brightnessContrast( const cv::Mat &image, int Brightness, double Contrast );
cv::Mat brightnessContrastLambda( const cv::Mat &image, int Brightness, double Contrast );
cv::Mat timer( const cv::Mat &image);
void display( const cv::Mat &image,const cv::Mat &modifiedImage );