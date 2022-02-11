#!/bin/bash
cwd=$(pwd)

#Installs compile-time dependencies
sudo apt -y remove x264 libx264-dev

sudo apt -y install build-essential checkinstall cmake pkg-config yasm
sudo apt -y install git gfortran
sudo apt -y install libjpeg8-dev libjasper-dev libpng12-dev
 
sudo apt -y install libtiff5-dev
 
sudo apt -y install libtiff-dev
 
sudo apt -y install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev
sudo apt -y install libxine2-dev libv4l-dev
cd /usr/include/linux
sudo ln -s -f ../libv4l1-videodev.h videodev.h
cd $cwd
 
sudo apt -y install libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev
sudo apt -y install libgtk2.0-dev libtbb-dev qt5-default
sudo apt -y install libatlas-base-dev
sudo apt -y install libfaac-dev libmp3lame-dev libtheora-dev
sudo apt -y install libvorbis-dev libxvidcore-dev
sudo apt -y install libopencore-amrnb-dev libopencore-amrwb-dev
sudo apt -y install libavresample-dev
sudo apt -y install x264 v4l-utils

#Begins compilation and installation of OpenCV headers and libraries
cd $cwd
mkdir installation
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
cd opencv
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE \
      -DCMAKE_INSTALL_PREFIX=${cwd}/installation/OpenCV-master \
      -DINSTALL_C_EXAMPLES=ON \
      -DINSTALL_PYTHON_EXAMPLES=OFF \
      -DWITH_TBB=ON \
      -DWITH_V4L=ON \
      -DWITH_QT=ON \
      -DWITH_OPENGL=ON \
      -DOPENCV_EXTRA_MODULES_PATH=${cwd}/opencv_contrib/modules \
      -DBUILD_EXAMPLES=ON ..

make -j4
make install

OPENCV_LIBDIR=$cwd/installation/OpenCV-master/lib/
echo "$OPENCV_LIBDIR" > opencv.conf
sudo mv opencv.conf /etc/ld.so.conf.d/
sudo ldconfig
