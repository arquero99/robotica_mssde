import rclpy
from rcl_interfaces.msg import ParameterDescriptor
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node


class MinimalParam(Node):
    def __init__(self):
        super().__init__('minimal_param_node')

        my_parameter_descriptor = ParameterDescriptor(description='This parameter is mine!')

        self.declare_parameter('my_parameter', 'world', my_parameter_descriptor)
        my_param = self.get_parameter('my_parameter').get_parameter_value().string_value
        self.get_logger().info('Hello %s!' % my_param)

        # Se llama cada vez que cambian parámetros del nodo (ros2 param set, load...)
        self.add_post_set_parameters_callback(self.on_param_change)

    def on_param_change(self, parameters):
        for param in parameters:
            if param.name == 'my_parameter':
                self.get_logger().info('Hello %s!' % param.value)


def main():
    try:
        with rclpy.init():
            node = MinimalParam()
            rclpy.spin(node)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass


if __name__ == '__main__':
    main()
