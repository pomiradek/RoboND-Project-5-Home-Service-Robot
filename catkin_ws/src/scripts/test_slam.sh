#!/bin/sh
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch  world_file:=/home/robond/workspace/RoboND-Project-5-Home-Service-Robot/catkin_ws/src/world/house.world " &
sleep 10
xterm -e " roslaunch turtlebot_gazebo gmapping_demo.launch " &
sleep 10
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 10
xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch"

