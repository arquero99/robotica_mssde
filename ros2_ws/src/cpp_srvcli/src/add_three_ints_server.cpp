#include <cinttypes>
#include <memory>

#include "tutorial_interfaces/srv/add_three_ints.hpp"                 // CHANGE
#include "rclcpp/rclcpp.hpp"

using AddThreeInts = tutorial_interfaces::srv::AddThreeInts;          // CHANGE
rclcpp::Node::SharedPtr g_node = nullptr;

void handle_service(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<AddThreeInts::Request> request,               // CHANGE
  const std::shared_ptr<AddThreeInts::Response> response)             // CHANGE
{
  (void)request_header;
  RCLCPP_INFO(
    g_node->get_logger(),
    "request: %" PRId64 " + %" PRId64 " + %" PRId64,                  // CHANGE
    request->a, request->b, request->c);                              // CHANGE
  response->sum = request->a + request->b + request->c;               // CHANGE
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  g_node = rclcpp::Node::make_shared("add_three_ints_server");        // CHANGE
  auto server = g_node->create_service<AddThreeInts>(                 // CHANGE
    "add_three_ints", handle_service);                                // CHANGE
  rclcpp::spin(g_node);
  rclcpp::shutdown();
  g_node = nullptr;
  return 0;
}
