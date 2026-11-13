cmake_minimum_required(VERSION 3.20)
project(cpp_pubsub)

# Default to C++20
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tutorial_interfaces REQUIRED)    # Bloque 10: tipos propios

# Bloque 8: publicador y suscriptor con std_msgs/String
add_executable(talker src/publisher_lambda_function.cpp)
target_link_libraries(talker PUBLIC rclcpp::rclcpp std_msgs::std_msgs)

add_executable(listener src/subscriber_lambda_function.cpp)
target_link_libraries(listener PUBLIC rclcpp::rclcpp std_msgs::std_msgs)

# Bloque 10: los mismos nodos con tutorial_interfaces/msg/Num
add_executable(talker_num src/publisher_num.cpp)
target_link_libraries(talker_num PUBLIC rclcpp::rclcpp tutorial_interfaces::tutorial_interfaces)

add_executable(listener_num src/subscriber_num.cpp)
target_link_libraries(listener_num PUBLIC rclcpp::rclcpp tutorial_interfaces::tutorial_interfaces)

install(TARGETS
  talker
  listener
  talker_num
  listener_num
  DESTINATION lib/${PROJECT_NAME})

ament_package()
