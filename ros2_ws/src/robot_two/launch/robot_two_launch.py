#!/usr/bin/env python3

import os

import launch
import launch_ros.actions

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

def generate_launch_description():

    return launch.LaunchDescription([
        launch_ros.actions.Node(
            package='robot_two', executable='gripper_node', name='gripper_node'
        ),
        launch_ros.actions.Node(
            package='robot_two', executable='stepper_node', name='stepper_node'
        ),
    ])
