#!/bin/sh
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/robond/workspace/RoboND-Project-5-Home-Service-Robot/catkin_ws/src/world/house.world " &
sleep 10
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/robond/workspace/RoboND-Project-5-Home-Service-Robot/catkin_ws/src/map/house.yaml " &
sleep 10
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 10
xterm -e " rosrun pick_objects pick_objects "

