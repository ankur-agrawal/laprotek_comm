cmake_minimum_required(VERSION 2.8.3)
project(laprotek_comm)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)


find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  tf
)
find_package(cmake_modules REQUIRED)
find_package(Eigen REQUIRED)


catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES laprotek_comm
#  CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

 add_executable(${PROJECT_NAME}_node src/server.cpp)


## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
 )
