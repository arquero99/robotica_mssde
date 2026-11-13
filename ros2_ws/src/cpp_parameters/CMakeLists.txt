cmake_minimum_required(VERSION 3.20)
project(cpp_parameters)

# Default to C++20
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(minimal_param_node src/cpp_parameters_node.cpp)
target_link_libraries(minimal_param_node rclcpp::rclcpp)

install(TARGETS
    minimal_param_node
  DESTINATION lib/${PROJECT_NAME}
)

# Instalar los launch files en share/cpp_parameters/launch
install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
