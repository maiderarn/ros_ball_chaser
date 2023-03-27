#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

class DriveBot {
  public:
    DriveBot() {
      motor_command_publisher_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
      service_ = n_.advertiseService("/ball_chaser/command_robot", &DriveBot::handle_drive_request, this);
    }
		
    bool handle_drive_request(ball_chaser::DriveToTarget::Request& req,
        ball_chaser::DriveToTarget::Response& res) {
      geometry_msgs::Twist motor_command;
      motor_command.linear.x = req.linear_x;
      motor_command.angular.z = req.angular_z;
			
      motor_command_publisher_.publish(motor_command);
			
      return true;
    }

  private:
    ros::NodeHandle n_;
    ros::Publisher motor_command_publisher_;
    ros::ServiceServer service_;
};

int main(int argc, char** argv){
  ros::init(argc, argv, "drive_bot");
  DriveBot drive_bot;	
  ros::spin();	
  return 0;
}
