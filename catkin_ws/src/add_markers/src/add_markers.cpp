#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

const float pickup_x = -1.0;
const float pickup_y = 2.0;

const float target_x = 2.0;
const float target_y = -2.5;

bool is_going_to_target = false;
bool pickup_zone_reached = false;

float dest_x;
float dest_y;

visualization_msgs::Marker marker;
ros::Publisher marker_pub;

void odom_callback(const nav_msgs::Odometry::ConstPtr &msg)
{
  float pose_x = msg -> pose.pose.position.x;
  float pose_y = msg -> pose.pose.position.y;

  if (is_going_to_target) {
	dest_x = target_x;
        dest_y = target_y;	
  } else {
        dest_x = pickup_x;
        dest_y = pickup_y;
  }

  float target_dist = sqrt(pow(pose_x-dest_x, 2) + pow(pose_y-dest_y, 2));

  ROS_INFO("Dest x: %f", dest_x);
  ROS_INFO("Dest y: %f", dest_y);
  ROS_INFO("Pose x: %f", pose_x);
  ROS_INFO("Pose y: %f", pose_y);
  ROS_INFO("Target dsitance: %f", target_dist);

  if (target_dist < 1.0) {
        // Pick up zone reached
	if (!is_going_to_target) {
		    pickup_zone_reached = true;
		    ROS_INFO("Robot reached pick up zone");
		    marker.action = visualization_msgs::Marker::DELETE;
		    marker_pub.publish(marker);
		    ros::Duration(5).sleep();
                    ROS_INFO("Robot is going to target zone");
		    is_going_to_target = true;
                    marker.action = visualization_msgs::Marker::ADD;
                    marker.pose.position.x = target_x;
		    marker.pose.position.y = target_y;
                    marker.pose.position.z = 0;
		    marker.pose.orientation.x = 0.0;
		    marker.pose.orientation.y = 0.0;
		    marker.pose.orientation.z = 0.0;
		    marker.pose.orientation.w = 1.0;
                    marker_pub.publish(marker);
        } else {
             ROS_INFO("Robot reached target zone");
	     marker.action = visualization_msgs::Marker::DELETE;
	     marker_pub.publish(marker);	
        }
  }
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  //ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("/odom", 1, &odom_callback);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();

// Set the namespace and id for this marker.  This serves to create a unique ID
// Any marker sent with the same namespace and id will overwrite the old one
marker.ns = "add_markers";
marker.id = 0;

// Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
marker.type = shape;

// Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
marker.action = visualization_msgs::Marker::ADD;

// Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
marker.pose.position.x = pickup_x;
marker.pose.position.y = pickup_y;
marker.pose.position.z = 0;
marker.pose.orientation.x = 0.0;
marker.pose.orientation.y = 0.0;
marker.pose.orientation.z = 0.0;
marker.pose.orientation.w = 1.0;

// Set the scale of the marker -- 1x1x1 here means 1m on a side
marker.scale.x = 0.2;
marker.scale.y = 0.2;
marker.scale.z = 0.2;

// Set the color -- be sure to set alpha to something non-zero!
marker.color.r = 0.0f;
marker.color.g = 0.0f;
marker.color.b = 1.0f;
marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

// Publish the marker
while (marker_pub.getNumSubscribers() < 1)
{
	if (!ros::ok())
	{
		return 0;
	}
	ROS_WARN_ONCE("Please create a subscriber to the marker");
	sleep(1);
}

marker_pub.publish(marker);

   while (ros::ok() )
  {

    ros::spinOnce();
  }

}
