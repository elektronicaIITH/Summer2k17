#!/bin/sh
# This is a powerful script which in the wrong hands can hack into any system
# on this world. If you are using this, you hold the fate of this world in your
# hands.
# HANDLE with CARE!
# LOL
if [ `id -u` -ne 0 ]
	then echo "Run the command as root."
	exit
fi
echo "[**]Running update..";sleep 2
sudo apt-get update
echo "Update done.."
echo "[**]Installing NumPy..";sleep 2
sudo apt-get install python-numpy
echo "[**]Installing matplotlib..";sleep 2
sudo apt-get install python-matplotlib
echo "[**]Installing pip";sleep 2
sudo apt-get install python-setuptools python-dev build-essential
sudo easy_install pip
sudo pip install --upgrade virtualenv
echo "[**] Installing audio modules required..";sleep 2
sudo pip install pydub
sudo pip install audiolazy
sudo apt-get install portaudio19-dev
sudo pip install pyaudio
echo "[**]Installing OpenCV";sleep 2
echo "This may take a lot of time..";sleep 1; echo ";)"
# I didn't write the below script. I took from the internet.
# Build tools:
sudo apt-get install -y build-essential cmake
# GUI (if you want to use GTK instead of Qt, replace 'qt5-default' with 'libgtkglext1-dev' and remove '-DWITH_QT=ON' option in CMake):
sudo apt-get install -y qt5-default libvtk6-dev
# Media I/O:
sudo apt-get install -y zlib1g-dev libjpeg-dev libwebp-dev libpng-dev libtiff5-dev libjasper-dev libopenexr-dev libgdal-dev
# Video I/O:
sudo apt-get install -y libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev yasm libopencore-amrnb-dev libopencore-amrwb-dev libv4l-dev libxine2-dev
# Parallelism and linear algebra libraries:
sudo apt-get install -y libtbb-dev libeigen3-dev
# Java:
sudo apt-get install -y ant default-jdk
# Documentation:
sudo apt-get install -y doxygen
# INSTALL THE LIBRARY (YOU CAN CHANGE '3.1.0' FOR THE LAST STABLE VERSION)
sudo apt-get install -y unzip wget
wget https://github.com/Itseez/opencv/archive/3.1.0.zip
unzip 3.1.0.zip
rm 3.1.0.zip
mv opencv-3.1.0 OpenCV
cd OpenCV
mkdir build
cd build
cmake -DWITH_QT=ON -DWITH_OPENGL=ON -DFORCE_VTK=ON -DWITH_TBB=ON -DWITH_GDAL=ON -DWITH_XINE=ON -DBUILD_EXAMPLES=ON ..
make -j4
sudo make install
sudo ldconfig
echo "[**] If you're reading this, you've successfully completed installing everything."
sleep 2
echo "[**] ENJOY!!"
