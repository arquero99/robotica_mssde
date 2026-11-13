#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class MyNode : public rclcpp::Node
{
public:
  MyNode()
  : Node("my_node_cpp"), count_(0)
  {
    auto timer_callback =
      [this]() -> void {
        RCLCPP_INFO(this->get_logger(), "Hola desde C++: %zu", this->count_++);
      };
    timer_ = this->create_wall_timer(1s, timer_callback);
  }

private:
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
