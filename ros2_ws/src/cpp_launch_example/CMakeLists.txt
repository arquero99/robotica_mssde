cmake_minimum_required(VERSION 3.20)
project(cpp_launch_example)

find_package(ament_cmake REQUIRED)

# Install launch files.
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
