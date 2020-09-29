cmake_minimum_required(VERSION 2.8.3)
project(visual_servo)

find_package(catkin REQUIRED
  roscpp
  high_level_planner
  std_srvs
  aruco_ros
)


catkin_package(
  CATKIN_DEPENDS roscpp high_level_planner aruco_ros std_srvs
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
add_executable(servo src/pose_subscriber_action_caller_class.cpp)
target_link_libraries(servo ${catkin_LIBRARIES})
install(TARGETS servo DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

