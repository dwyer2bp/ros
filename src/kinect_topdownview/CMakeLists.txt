cmake_minimum_required(VERSION 2.8.3)
project(kinect_topdownview)

set(${PROJECT_NAME}_CATKIN_DEPS
  dynamic_reconfigure
  pcl_ros
  roscpp
  visualization_msgs
  laser_geometry
  image_transport
  cv_bridge
	nodelet
)

find_package(catkin REQUIRED COMPONENTS ${${PROJECT_NAME}_CATKIN_DEPS})

## Setup include directories
include_directories(${catkin_INCLUDE_DIRS})

catkin_package(
	INCLUDE_DIRS include
	LIBRARIES 
  CATKIN_DEPENDS ${${PROJECT_NAME}_CATKIN_DEPS}
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
)

add_library(KinectTopDownView src/KinectTopDownView.cpp)
target_link_libraries(KinectTopDownView ${catkin_LIBRARIES})
