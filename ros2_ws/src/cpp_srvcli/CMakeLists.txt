cmake_minimum_required(VERSION 3.20)
project(cpp_srvcli)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(tutorial_interfaces REQUIRED)    # Bloque 10: tipos propios

# Bloque 9: servicio y cliente con example_interfaces/srv/AddTwoInts
add_executable(server src/add_two_ints_server.cpp)
target_link_libraries(server PUBLIC rclcpp::rclcpp example_interfaces::example_interfaces)

add_executable(client src/add_two_ints_client.cpp)
target_link_libraries(client PUBLIC rclcpp::rclcpp example_interfaces::example_interfaces)

# Bloque 10: los mismos nodos con tutorial_interfaces/srv/AddThreeInts
add_executable(server_three src/add_three_ints_server.cpp)
target_link_libraries(server_three PUBLIC rclcpp::rclcpp tutorial_interfaces::tutorial_interfaces)

add_executable(client_three src/add_three_ints_client.cpp)
target_link_libraries(client_three PUBLIC rclcpp::rclcpp tutorial_interfaces::tutorial_interfaces)

install(TARGETS
  server
  client
  server_three
  client_three
  DESTINATION lib/${PROJECT_NAME})

ament_package()
