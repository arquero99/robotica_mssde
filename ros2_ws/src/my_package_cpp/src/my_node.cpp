#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class MyNode : public rclcpp::Node
{
public:
  MyNode()
  : Node("my_node_cpp"), count_(0)
  {
    timer_ = this->create_wall_timer(
      1s, std::bind(&MyNode::timer_callback, this));
  }

private:
  void timer_callback()
  {
    RCLCPP_INFO(this->get_logger(), "Hola desde C++: %zu", count_++);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);                     // 1. Inicializar ROS 2
  rclcpp::spin(std::make_shared<MyNode>());     // 2. Crear el nodo y atender callbacks
  rclcpp::shutdown();                           // 3. Liberar recursos
  return 0;
}
