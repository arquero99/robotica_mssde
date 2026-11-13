from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    # Valores de los argumentos: se cambian al lanzar con nombre:=valor
    topic = LaunchConfiguration('topic')
    saludo = LaunchConfiguration('saludo')

    return LaunchDescription([
        DeclareLaunchArgument('topic', default_value='chatter',
                              description='Topic del talker y el listener'),
        DeclareLaunchArgument('saludo', default_value='earth',
                              description='my_parameter del nodo C++'),
        # Nodos C++ y Python conectados por el mismo topic
        Node(package='cpp_pubsub', executable='talker', name='talker_cpp',
             remappings=[('topic', topic)]),
        Node(package='py_pubsub', executable='listener', name='listener_py',
             remappings=[('topic', topic)]),
        # Parámetros: tomado de un argumento (C++) o valor fijo (Python)
        Node(package='cpp_parameters', executable='minimal_param_node',
             name='param_cpp', parameters=[{'my_parameter': saludo}]),
        Node(package='python_parameters', executable='minimal_param_node',
             name='param_py', parameters=[{'my_parameter': 'mars'}]),
    ])
