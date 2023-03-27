#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

class ProcessImage {
  public:
    ProcessImage() {
      client_ = n_.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
      sub1_ = n_.subscribe("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, this);
    }
	
    void drive_robot(float lin_x, float ang_z) {
      ball_chaser::DriveToTarget srv;
      srv.request.linear_x = lin_x;
      srv.request.angular_z = ang_z;
			
      if(!client_.call(srv))
        ROS_ERROR("Failed to call service command_robot");
    }
		
    void process_image_callback(const sensor_msgs::Image img) {
      int white_pixel = 255;
      int left_breakpoint = img.step / 3;
      int mid_breakpoint = img.step * 2 / 3;
			
      bool white_ball_visible = false;
			
      for (int i = 0; i < img.height * img.step; i += 3) {
        if (img.data[i] == white_pixel &&
            img.data[i+1] == white_pixel &&
            img.data[i+2] == white_pixel) {
          white_ball_visible = true;
          int col = i % img.step;
					
          if (col <= left_breakpoint)
            drive_robot(0.25, 0.5);
          else if (col <= mid_breakpoint)
            drive_robot(0.25, 0);
          else
            drive_robot(0.25, -0.5);
          break;
        }
      }
			
      if (!white_ball_visible)
        drive_robot(0.1, 0.7);
    }
	
  private:
    ros::NodeHandle n_;
    ros::ServiceClient client_;
    ros::Subscriber sub1_;
};

int main(int argc, char** argv){
  ros::init(argc, argv, "process_image");
  ProcessImage process_image;
  ros::spin();
  return 0;
}


