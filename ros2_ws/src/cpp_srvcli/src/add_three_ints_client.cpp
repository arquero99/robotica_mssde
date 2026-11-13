#include <chrono>
#include <cinttypes>
#include <memory>

#include "tutorial_interfaces/srv/add_three_ints.hpp"                 // CHANGE
#include "rclcpp/rclcpp.hpp"

using AddThreeInts = tutorial_interfaces::srv::AddThreeInts;          // CHANGE

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("add_three_ints_client");     // CHANGE
  auto client = node->create_client<AddThreeInts>("add_three_ints");  // CHANGE
  while (!client->wait_for_service(std::chrono::seconds(1))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "client interrupted while waiting for service to appear.");
      return 1;
    }
    RCLCPP_INFO(node->get_logger(), "waiting for service to appear...");
  }
  auto request = std::make_shared<AddThreeInts::Request>();           // CHANGE
  request->a = 41;
  request->b = 1;
  request->c = 1;                                                     // CHANGE
  auto result_future = client->async_send_request(request);
  if (rclcpp::spin_until_future_complete(node, result_future) !=
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_ERROR(node->get_logger(), "service call failed :(");
    client->remove_pending_request(result_future);
    return 1;
  }
  auto result = result_future.get();
  RCLCPP_INFO(
    node->get_logger(), "result of %" PRId64 " + %" PRId64 " + %" PRId64 " = %" PRId64,  // CHANGE
    request->a, request->b, request->c, result->sum);                                    // CHANGE
  rclcpp::shutdown();
  return 0;
}
