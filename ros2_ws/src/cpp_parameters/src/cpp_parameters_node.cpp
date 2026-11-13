#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <rclcpp/rclcpp.hpp>

class MinimalParam : public rclcpp::Node
{
public:
  MinimalParam()
  : Node("minimal_param_node")
  {
    auto param_desc = rcl_interfaces::msg::ParameterDescriptor{};
    param_desc.description = "This parameter is mine!";

    this->declare_parameter("my_parameter", "world", param_desc);
    std::string my_param = this->get_parameter("my_parameter").as_string();
    RCLCPP_INFO(this->get_logger(), "Hello %s!", my_param.c_str());

    // Se llama cada vez que cambian parámetros del nodo (ros2 param set, load...)
    param_callback_handle_ = this->add_post_set_parameters_callback(
      std::bind(&MinimalParam::on_param_change, this, std::placeholders::_1));
  }

private:
  void on_param_change(const std::vector<rclcpp::Parameter> & parameters)
  {
    for (const auto & param : parameters) {
      if (param.get_name() == "my_parameter") {
        RCLCPP_INFO(this->get_logger(), "Hello %s!", param.as_string().c_str());
      }
    }
  }

  rclcpp::node_interfaces::PostSetParametersCallbackHandle::SharedPtr param_callback_handle_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalParam>());
  rclcpp::shutdown();
  return 0;
}
