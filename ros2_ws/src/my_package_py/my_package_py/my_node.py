import rclpy
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node


class MyNode(Node):

    def __init__(self):
        super().__init__('my_node_py')
        self.count = 0
        self.timer = self.create_timer(1.0, self.timer_callback)

    def timer_callback(self):
        self.get_logger().info('Hola desde Python: %d' % self.count)
        self.count += 1


def main(args=None):
    try:
        with rclpy.init(args=args):         # 1. Inicializar ROS 2
            node = MyNode()                 # 2. Crear el nodo
            rclpy.spin(node)                # 3. Atender callbacks
    except (KeyboardInterrupt, ExternalShutdownException):
        pass                                # Ctrl+C: salida limpia


if __name__ == '__main__':
    main()
