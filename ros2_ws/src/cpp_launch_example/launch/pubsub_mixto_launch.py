from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    # Valor del argumento: se puede cambiar al lanzar con topic:=otro_nombre
    topic = LaunchConfiguration('topic')

    return LaunchDescription([
        DeclareLaunchArgument(
            'topic',
            default_value='chatter',
            description='Topic que comparten el talker y el listener'),
        Node(
            package='cpp_pubsub',            # nodo escrito en C++
            executable='talker',
            name='talker_cpp',
            remappings=[('topic', topic)]),
        Node(
            package='py_pubsub',             # nodo escrito en Python
            executable='listener',
            name='listener_py',
            remappings=[('topic', topic)]),
    ])
