# robotica_mssde

Repositorio para albergar tutoriales sobre ROS2. Master en sistemas empotrados y distribuidos. ETSISI UPM.

## Sesión «ROS 2 Lyrical Luth» (≈ 3 h)

Presentación en [Quarto](https://quarto.org) (revealjs) basada en los tutoriales oficiales de ROS 2 Lyrical (<https://docs.ros.org/en/lyrical/>). Cada concepto se explica desde la **CLI** (`ros2 …`), en **C++** (`rclcpp`) y en **Python** (`rclpy`).

| # | Bloque | Min |
|---|---|---|
| 1 | Qué es ROS 2 y qué puede hacer | 8 |
| 2 | Arquitectura | 13 |
| 3 | Elegir la versión según Ubuntu | 5 |
| 4 | Instalación (referencia) | 2 |
| 5 | Workspace y paquetes | 18 |
| 6 | Primer nodo | 15 |
| 7 | Interfaces: concepto y CLI | 10 |
| — | Descanso | 10 |
| 8 | Topics: publicador y suscriptor | 20 |
| 9 | Servicios: servidor y llamadas | 20 |
| 10 | Tipos propios: msg y srv | 15 |
| 11 | Actions: demo C++ + ejercicio Python | 20 |
| 12 | Parámetros | 10 |
| 13 | Launch files (Python) | 12 |
| — | Cierre | 2 |

## Estructura

```text
.
├── _quarto.yml                 # configuración de la presentación
├── index.qmd                   # portada, agenda e inclusión de los bloques
├── secciones/                  # un .qmd por bloque (01 … 13, 99-cierre)
├── estilos/custom.scss         # estilo de las diapositivas
├── _extensions/                # extensión include-code-files
├── ejercicios/
│   └── ejercicio-actions-python.md
└── ros2_ws/src/                # código de la sesión (paquetes ROS 2)
    ├── my_package_cpp/  my_package_py/              # bloque 6: primer nodo
    ├── cpp_pubsub/      py_pubsub/                  # bloques 8 y 10: topics
    ├── cpp_srvcli/      py_srvcli/                  # bloques 9 y 10: servicios
    ├── tutorial_interfaces/                         # bloque 10: Num, Sphere, AddThreeInts
    ├── custom_action_interfaces/                    # bloque 11: Fibonacci.action
    ├── custom_action_cpp/                           # bloque 11: demo en C++
    ├── custom_action_py/                            # bloque 11: solución del ejercicio
    ├── cpp_parameters/  python_parameters/          # bloque 12: parámetros
    └── cpp_launch_example/  py_launch_example/      # bloque 13: launch
```

Las diapositivas incluyen el código directamente de `ros2_ws/src/`, así que lo que se ve en clase coincide con lo que hay en el repositorio.

## Prerrequisitos para el alumnado

Antes de la sesión, con **Ubuntu 26.04**:

1. Instalar ROS 2 Lyrical siguiendo la [guía oficial](https://docs.ros.org/en/lyrical/Get-Started/Installation/Ubuntu-Install-Debs.html): `ros-lyrical-desktop` y `ros-dev-tools`.
2. Instalar `ros-lyrical-turtlesim`, `ros-lyrical-rqt` y `ros-lyrical-rqt-common-plugins`.
3. Comprobar que `ros2 run demo_nodes_cpp talker` y `ros2 run demo_nodes_py listener` se comunican.

## Compilar el workspace

```bash
cd ros2_ws
source /opt/ros/lyrical/setup.bash
rosdep install -i --from-path src --rosdistro lyrical -y
colcon build --symlink-install
source install/setup.bash
```

## Ver o generar la presentación

Requiere Quarto ≥ 1.4.

```bash
quarto preview            # servidor local con recarga automática
quarto render             # genera _site/index.html
```

En la presentación: `S` abre las notas del ponente, `F` pasa a pantalla completa y `Esc` muestra la vista general.
