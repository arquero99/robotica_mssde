# Ejercicio: servidor y cliente de la action Fibonacci en Python

En clase hemos visto el servidor y el cliente de la action `Fibonacci` en **C++** (`custom_action_cpp`). En este ejercicio vas a escribir los mismos nodos en **Python**, con `rclpy.action`, y a comprobar que son intercambiables con los de C++.

- **Tiempo estimado**: 30–45 minutos.
- **Referencia oficial**: [Writing an action server and client (Python)](https://docs.ros.org/en/lyrical/ROS-Framework/interfaces/actions/Working-with-actions/Writing-an-Action-Server-Client/Py.html)
- **Solución**: `ros2_ws/src/custom_action_py/`. Consúltala solo al terminar.

## Requisitos previos

- El paquete `custom_action_interfaces` compilado (bloque 11). Compruébalo con:

  ```bash
  ros2 interface show custom_action_interfaces/action/Fibonacci
  ```

  ```text
  # Goal
  int32 order
  ---
  # Result
  int32[] sequence
  ---
  # Feedback
  int32[] sequence
  ```

- El servidor y el cliente C++ (`custom_action_cpp`) funcionando, para las pruebas cruzadas.

## Paso 1: crear el paquete

```bash
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_python --license Apache-2.0 custom_action_py \
  --dependencies rclpy custom_action_interfaces
```

Crearás dos ficheros dentro de `custom_action_py/custom_action_py/`:

- `fibonacci_action_server.py`
- `fibonacci_action_client.py`

## Paso 2: el servidor

Completa los `TODO` del siguiente esqueleto:

```python
import time

import rclpy
from rclpy.action import ActionServer
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node

from custom_action_interfaces.action import Fibonacci


class FibonacciActionServer(Node):

    def __init__(self):
        super().__init__('fibonacci_action_server')
        # TODO 1: crear un ActionServer de tipo Fibonacci, con nombre 'fibonacci',
        #         que llame a self.execute_callback para cada goal.

    def execute_callback(self, goal_handle):
        self.get_logger().info('Executing goal...')

        # TODO 2: crear un Fibonacci.Feedback() cuya 'sequence' empiece en [0, 1].

        # TODO 3: para i desde 1 hasta goal_handle.request.order - 1:
        #           - añadir sequence[i] + sequence[i-1] a la secuencia
        #           - publicar el feedback con goal_handle.publish_feedback(...)
        #           - esperar 1 segundo (time.sleep(1))

        # TODO 4: marcar el goal como completado con goal_handle.succeed()
        #         (si no lo haces, el goal se considera abortado).

        # TODO 5: crear un Fibonacci.Result(), copiar la secuencia y devolverlo.


def main(args=None):
    try:
        with rclpy.init(args=args):
            fibonacci_action_server = FibonacciActionServer()
            rclpy.spin(fibonacci_action_server)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass


if __name__ == '__main__':
    main()
```

## Paso 3: registrar los ejecutables

En `setup.py`:

```python
entry_points={
    'console_scripts': [
        'fibonacci_action_server = custom_action_py.fibonacci_action_server:main',
        'fibonacci_action_client = custom_action_py.fibonacci_action_client:main',
    ],
},
```

Comprueba también que `package.xml` incluye `rclpy` y `custom_action_interfaces` como dependencias.

## Paso 4: probar el servidor desde la CLI

```bash
cd ~/ros2_ws
colcon build --packages-select custom_action_py
source install/setup.bash
ros2 run custom_action_py fibonacci_action_server
```

En otra terminal:

```bash
ros2 action list -t
ros2 action send_goal --feedback fibonacci custom_action_interfaces/action/Fibonacci "{order: 5}"
```

Resultado esperado: la secuencia `[0, 1, 1, 2, 3, 5]`, el feedback de cada paso y `Goal finished with status: SUCCEEDED`.

## Paso 5: el cliente

Completa los `TODO`:

```python
import rclpy
from rclpy.action import ActionClient
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node

from custom_action_interfaces.action import Fibonacci


class FibonacciActionClient(Node):

    def __init__(self):
        super().__init__('fibonacci_action_client')
        # TODO 1: crear un ActionClient de tipo Fibonacci para la action 'fibonacci'.

    def send_goal(self, order):
        # TODO 2: crear un Fibonacci.Goal() y rellenar 'order'.
        # TODO 3: esperar al servidor (wait_for_server).
        # TODO 4: enviar el goal con send_goal_async(goal, feedback_callback=self.feedback_callback)
        #         y registrar self.goal_response_callback con add_done_callback en el future.
        pass

    def goal_response_callback(self, future):
        goal_handle = future.result()
        # TODO 5: si el goal no fue aceptado (goal_handle.accepted), registrarlo y salir.
        # TODO 6: pedir el resultado con goal_handle.get_result_async()
        #         y registrar self.get_result_callback en ese future.

    def get_result_callback(self, future):
        result = future.result().result
        self.get_logger().info('Result: {0}'.format(result.sequence))
        rclpy.shutdown()

    def feedback_callback(self, feedback_msg):
        # TODO 7: mostrar feedback_msg.feedback.sequence con el logger.
        pass


def main(args=None):
    try:
        with rclpy.init(args=args):
            action_client = FibonacciActionClient()
            action_client.send_goal(10)
            rclpy.spin(action_client)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass


if __name__ == '__main__':
    main()
```

## Paso 6: pruebas cruzadas C++ ↔ Python

| Servidor | Cliente | Comando del servidor | Comando del cliente |
|---|---|---|---|
| Python | Python | `ros2 run custom_action_py fibonacci_action_server` | `ros2 run custom_action_py fibonacci_action_client` |
| Python | C++ | `ros2 run custom_action_py fibonacci_action_server` | `ros2 run custom_action_cpp fibonacci_action_client` |
| C++ | Python | `ros2 run custom_action_cpp fibonacci_action_server` | `ros2 run custom_action_py fibonacci_action_client` |

Las tres combinaciones deben terminar con la secuencia de orden 10: `[0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55]`.

## Criterios de comprobación

- [ ] `ros2 action list -t` muestra `/fibonacci [custom_action_interfaces/action/Fibonacci]` con tu servidor en marcha.
- [ ] `ros2 action send_goal --feedback ...` muestra el feedback paso a paso y termina en `SUCCEEDED`.
- [ ] Tu cliente muestra el feedback y el resultado, y después termina.
- [ ] Las tres combinaciones de la tabla funcionan.

## Ampliación (opcional): cancelación

El servidor C++ comprueba `is_canceling()` y termina con `canceled()`. Para hacer lo mismo en Python:

1. Pasa un `cancel_callback` al `ActionServer` que devuelva `CancelResponse.ACCEPT` (`from rclpy.action import CancelResponse`).
2. En el bucle de `execute_callback`, comprueba `goal_handle.is_cancel_requested`. Si es cierto, llama a `goal_handle.canceled()` y devuelve el resultado parcial.
3. Pista: mientras `execute_callback` está en `time.sleep()`, un executor de un solo hilo no puede atender la petición de cancelación. Investiga `MultiThreadedExecutor` y la guía [Using callback groups](https://docs.ros.org/en/lyrical/ROS-Framework/nodes/Working-with-nodes/Using-callback-groups.html).
4. Pruébalo enviando un goal largo (`order: 20`) y pulsando `Ctrl+C` en el `ros2 action send_goal`. La CLI pide la cancelación del goal.
