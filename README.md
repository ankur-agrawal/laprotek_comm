# Description

This package is used to establish communication using TCPIP for a surgical robot named Laprotek to receive the joint angles, poses and send input wrench to it. It provides an interface for ROS, where the messages are converted into ROS messages of sensor_msgs/JointStates, geometry_msgs/PoseStamped, geometry_msgs/WrenchStamped.

The following describes the purpose of all files within:

Server.h : Creates a TCPIP server to which the robot client can communicate with and data is transferred in form of strings.

RosBridge.h : Converts the received/sent data to ROS messages and has publishers/subscribers to publish/listen to different topics.

Server.cpp : Has the main function that puts together the two classes.

# Author

Ankur Agrawal : asagrawal@wpi.edu

# Install
* download & compile laprotek_comm

Dependencies: ROS Kinetic or Indigo, Eigen library

```sh
# cd to catkin ws src dir
cd /PATH/TO/CATKIN_WS/src
# clone repo
git clone https://github.com/ankur-agrawal/laprotek_comm.git
# build
cd ..
catkin_make
```
# How to use

```sh
#Source the folder
source devel/setup.bash

# To use it with ROS
rosrun laprotek_comm laprotek_comm_node ROS

# To use without ROS
rosrun laprotek_comm laprotek_comm_node

# To run a trial client for testing purposes
