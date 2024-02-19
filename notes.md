```json
{
  "configurations": [
    {
      "name": "Linux",
      "includePath": [
        "${workspaceFolder}/**",
        "~/ros2_ws/install/more_interfaces/include",
        "/opt/ros/foxy/include"
      ],
      "defines": [],
      "compilerPath": "/usr/bin/gcc",
      "cStandard": "c17",
      "cppStandard": "gnu++14",
      "intelliSenseMode": "linux-gcc-x64"
    }
  ],
  "version": 4
}
```

```sh
ros2 pkg create my_cpp_pkg --build-type ament_cmake --dependencies rclcpp
colcon build --packages-select my_cpp_pkg

. install/setup.bash

ros2 topic echo ${topic_name}


# Modify the name
ros2 run my_cpp_pkg robot_news_station --ros-args -r_node:=my_station

# Remap hte topic name
ros2 run my_cpp_pkg robot_news_station --ros-args -r __node:=my_station -r robot_news:=my_news
ros2 run my_cpp_pkg smartphone --ros-args -r robot_news:=my_news
```
