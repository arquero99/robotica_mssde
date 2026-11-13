cmake_minimum_required(VERSION 3.20)
project(my_package_cpp)

# Lyrical usa C++20 por defecto
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(my_node src/my_node.cpp)
target_link_libraries(my_node PUBLIC rclcpp::rclcpp)

install(TARGETS
  my_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
