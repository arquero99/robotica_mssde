from setuptools import find_packages, setup

package_name = 'custom_action_py'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Equipo docente',
    maintainer_email='docente@example.com',
    description='Servidor y cliente de la action Fibonacci en Python (solucion del ejercicio)',
    license='Apache-2.0',
    extras_require={
        'test': ['pytest'],
    },
    entry_points={
        'console_scripts': [
            'fibonacci_action_server = custom_action_py.fibonacci_action_server:main',
            'fibonacci_action_client = custom_action_py.fibonacci_action_client:main',
        ],
    },
)
