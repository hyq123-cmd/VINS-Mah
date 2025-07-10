# VINS-Mah
## A monocular visual-inertial odometry for dynamic environments
VINS-Mah achieves better performance in dynamic environments than the baseline methods while not degrading in static scenarios. It is built on the well-known method [VINS-Fusion](https://github.com/HKUST-Aerial-Robotics/VINS-Fusion.git). However, our proposed method only supports one configuration, which is "one camera and one IMU". More configurations might be developed in the future.
## Running environments
We recommend referring the VINS-Fusion project, as there are no additional packages required to  run this algorithm. The only thing you might want to pay attention to is that we ran and tested this method on Ubuntu 20.04 and ROS Noetic.The required configuration environment is OpenCV 4.2.0 and Ceres Solver 1.14.0.

## Prerequisites
### 1.1 Ubuntu and ROS
Ubuntu 20.04.
ROS Noetic: [ROS Installation](edge)
### 1.2 Ceres Sovler
The 1.14.0 version is used in this project, we recommend installing it using following command:
'''sudo apt-get install libceres-dev'''
### 1.3 OpenCV
OpenCV 4.2.0
## License
This project is licensed under the GNU General Public License v3.0 (GPLv3), in accordance with the license of the original project it is based on.
