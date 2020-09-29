#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Pose.h"
#include <actionlib/client/simple_action_client.h>
#include <high_level_planner/MoveGroupAction.h>
#include "std_msgs/Float64.h"
#include <iostream>

using namespace std;

actionlib::SimpleActionClient<high_level_planner::MoveGroupAction> ac("/my_gen3/move_group_action", true);
high_level_planner::MoveGroupGoal goal;


void chatterCallback(const geometry_msgs::PoseStamped msg)
{
  goal.path_constraint = false;
  goal.cartesian = true;
  goal.relative = false;
  goal.pose_reference_frame = "end_effector_link";
  

  double x_cal = msg.pose.position.x;
  double y_cal = msg.pose.position.y;
  double z_cal = msg.pose.position.z;
  double qx_cal = msg.pose.orientation.x;
  double qy_cal = msg.pose.orientation.y;
  double qz_cal = msg.pose.orientation.z;
  double qw_cal = msg.pose.orientation.w;
  ROS_INFO("Received Tag Pose");

  //set point values to goal message
  goal.cartesian_goal.position.x = x_cal;
  goal.cartesian_goal.position.y = y_cal;  
  goal.cartesian_goal.position.z = z_cal;
  //set quat values to goal message
  goal.cartesian_goal.orientation.x = qx_cal;
  goal.cartesian_goal.orientation.y = qy_cal;  
  goal.cartesian_goal.orientation.z = qz_cal;
  goal.cartesian_goal.orientation.w = qw_cal;
  ROS_INFO("Sending Tag Pose");
  ac.sendGoal(goal);
   
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "visual_servo");

  ros::NodeHandle n;

  ROS_INFO("Waiting for action server to start.");
  ac.waitForServer();
  ROS_INFO("Action server started, sending goal.");

  ros::Subscriber sub = n.subscribe("/aruco_single/position", 1, chatterCallback);

  ros::spin();

  return 0;
}
