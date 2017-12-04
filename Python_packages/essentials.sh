#!/bin/sh
# The scroll of the dragon warrior.
# You're the secret ingredient. No one cares about the code below.

if [ `id -u` -ne 0 ]
	then echo "Run the command as root."
	exit
fi

echo "[**]Running update..";sleep 2
sudo apt-get update
echo "Update done.."

echo "[**]Installing pip..";sleep 2
sudo apt-get install python-setuptools python-dev build-essential
sudo apt-get install python-pip

echo "[**]Installing NumPy..";sleep 2
sudo pip install numpy

echo "[**]Installing SciPy..";sleep 2
sudo pip install scipy

echo "[**]Installing Scikit-Learn..";sleep 2
sudo pip install scikit-learn

echo "[**]Installing matplotlib..";sleep 2
sudo pip install matplotlib

sudo pip install --upgrade virtualenv
echo "[**] Installing audio modules required..";sleep 2
sudo pip install pydub
sudo pip install audiolazy
sudo apt-get install portaudio19-dev
sudo pip install pyaudio

# echo "[**] Installing CUDA";sleep 2
# sudo apt-get install linux-headers-$(uname -r)

# echo "Enter your version of Ubuntu. Do not include '.', ie, 16.04 == 1604";sleep 2
# read version
# if [$version -eq 16.04] || [$version -eq 17.04]
# then
# 	# Download and unpack CUDA toolkit
#         sudo wget https://developer.nvidia.com/compute/cuda/9.0/Prod/local_installers/cuda-repo-ubuntu$(version)-9-0-local_9.0.176-1_amd64-deb
# 	sudo dpkg -i cuda-repo-ubuntu$(version)-9-0-local_9.0.176-1_amd64.deb
# 	# Add to package manager and install CUDA
# 	sudo apt-key add /var/cuda-9-0-local/7fa2af80.pub
# 	sudo apt-get update
# 	sudo apt-get install cuda
# 	# Set up environment variables
# 	export PATH=/usr/local/cuda-9.0/bin${PATH:+:${PATH}}
# 	export LD_LIBRARY_PATH=/usr/local/cuda-9.0/lib64\
#                          ${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
# 	# Install and compile CUDA Samples
# 	cuda-install-samples-9.0.sh ~
# 	cd ~/NVIDIA_CUDA-9.0_Samples
# 	make
# else
# 	echo "This script installs CUDA only for Ubuntu 16.04 and 17.04. The alternative is to install from aptitude but this is not recommended."
# fi

echo "[**]Installing OpenCV";sleep 2
echo "This may (will) take a while..";sleep 1
# Third hand OpenCV install script. Must work.
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

echo "[**]Installing Theano";sleep 2
# Install dependencies
sudo pip install nose
sudo apt-get install libopenblas-dev git
# Install theano	
sudo pip install Theano
# Work around a glibc bug
echo -e "\n[nvcc]\nflags=-D_FORCE_INLINES\n" >> ~/.theanorc

echo "[**]Installing Tensorflow";sleep 2
echo "Do you wish to install tensorflow for GPU? [Y/n]"
# read choice

# if [-z $choice] || [$choice == 'y'] || [$choice == 'Y']
# then
# 	sudo pip install tensorflow-gpu
# elif [$choice == 'n'] || [$choice == 'N']
sudo pip install tensorflow
# fi

echo "[**] Installing Keras";sleep 2
# Install dependencies
sudo pip install h5py graphviz pydot
# Install Keras
sudo pip install keras

echo "[**] Congratulations, you've made it! Use this power wisely. May the Force be with you."

