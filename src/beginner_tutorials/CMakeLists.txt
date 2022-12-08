# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(beginner_tutorials)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg   pcl_conversions pcl_ros roscpp sensor_msgs)

## Declare ROS messages and services
add_message_files(FILES Num.msg)
#add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs )

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(trans src/trans.cpp)
target_link_libraries(trans ${catkin_LIBRARIES})
add_dependencies(trans beginner_tutorials_generate_messages_cpp)

catkin_install_python(PROGRAMS src/ekf_radar.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# %EndTag(FULLTEXT)%

