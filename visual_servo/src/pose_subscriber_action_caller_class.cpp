#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Pose.h"
#include <actionlib/client/simple_action_client.h>
#include <high_level_planner/MoveGroupAction.h>
#include "std_msgs/Float64.h"
#include <iostream>

high_level_planner::MoveGroupGoal goal;

class VisualServoComm{
public:

  VisualServoComm(ros::NodeHandle *n): AC("/my_gen3/move_group_action", true){
    sub = n->subscribe("/aruco_single/pose", 1, &VisualServoComm::chatterCallback,this);
    //ROS_INFO("Waiting for action server to start.");
    //AC.waitForServer();
    //ROS_INFO("Action server started, sending goal.");
  }
  void chatterCallback(const geometry_msgs::PoseStamped msg);
private:
  actionlib::SimpleActionClient<high_level_planner::MoveGroupAction> AC;
  ros::Subscriber sub;

};

void VisualServoComm::chatterCallback(const geometry_msgs::PoseStamped msg){
    goal.path_constraint = false;
    goal.cartesian = true;
    goal.relative = false;
    goal.pose_reference_frame = "end_effector_link";
    

    double x_cal = msg.pose.position.x + 0.3;
    double y_cal = msg.pose.position.y + 0.05;
    double z_cal = msg.pose.position.z - 0.3;
    double qx_cal = msg.pose.orientation.x;
    double qy_cal = msg.pose.orientation.y;
    double qz_cal = msg.pose.orientation.z;
    double qw_cal = msg.pose.orientation.w;
    ROS_INFO("Received Tag Pose");

    //set point values to goal message
    goal.cartesian_goal.position.x = 0;
    std::cout << "Sending x direction: " << x_cal << std::endl;
    goal.cartesian_goal.position.y = 0;  
    goal.cartesian_goal.position.z = x_cal;
    //set quat values to goal message
    //goal.cartesian_goal.orientation.x = qx_cal;
   // goal.cartesian_goal.orientation.y = qy_cal;  
    //goal.cartesian_goal.orientation.z = qz_cal;
    //goal.cartesian_goal.orientation.w = qw_cal;
    //goal.cartesian_goal.orientation.x = 0.514;
   // goal.cartesian_goal.orientation.y = 0.495;  
    //goal.cartesian_goal.orientation.z = 0.492;
    //goal.cartesian_goal.orientation.w = 0.499;
    ROS_INFO("Sending Tag Pose");
    AC.sendGoal(goal);
  }




int main(int argc, char **argv)
{

  ros::init(argc, argv, "visual_servo");

  ros::NodeHandle n;
  VisualServoComm VSC(&n);


  ros::spin();

  return 0;
}
