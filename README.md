# RoboND-Project-5-Home-Service-Robot
Udacity RoboND Project 5 - Home Service Robot

## Install
Checkout this repo
```shell
sudo apt-get update && apt-get upgrade

cd catkin_ws
catkin_make
source devel/setup.bash
./src/script/*.sh
```

## SLAM Testing

test_slam.sh

Autonomously map the environment. After launching the script it will open Gazebo + Rviz + Teleop.
Launch test_slam.sh file, search for the xterminal running the keyboard_teleopnode, and start controlling your robot.
You have to navigate Turtlebot to map your environment, util you are satisfied with the map. Than you have to export the map using this comand in new terminal window:
```shell
rosrun map_server map_saver -f /map/house
```

## Localization and Navigation Testing

Running the script test_navigation.sh you will initially see the particles around your robot, which means that AMCL recognizes the initial robot pose. Now, manually point out to two different goals, one at a time, and direct your robot to reach them and orient itself with respect to them.

## Your Home Service Robot

```shell
home_service.sh
```

The are 2 new ROS nodes:
### add_markers

This C++ node subscribes to /odom topic to read robot's pose for evaluating pick up and drop off zone.
Initially show the marker at the pickup zone
Hide the marker once your robot reaches the pickup zone
Wait 5 seconds to simulate a pickup
Show the marker at the drop off zone once your robot reaches it

For displaying Markers in Rviz, it is required to add Marker to Rviz configuration. For display custom Markers I am using ROS Marker (see http://wiki.ros.org/rviz/Tutorials/Markers%3A%20Basic%20Shapes)

### pick_objects

This C++ node is responsible for navigating the robot to the pickup zone.
Waiting 5sec to simulate loading. 
Than navigate to drop off zone.

For moving robot I am using MoveBaseClient (see http://wiki.ros.org/navigation/Tutorials/SendingSimpleGoals)
