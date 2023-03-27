
# ros-ball-chaser
Este proyecto presenta un robot que persigue bolas de color blanco en un ambiente de oficina creado con Gazebo. Este robot utiliza un sensor de cámara para detectar la bola y conducir en esa dirección.

Está compuesto por dos paquetes ROS: "ball_chaser" y "robot".


### Build Package

Primero, ejecute los siguientes comandos para construir los paquetes.
```
$ cd <path_to_catkin_ws>
$ catkin_make
```

### Start Project

En una nueva ventana de terminal, por favor ejecute:
```
$ cd <path_to_catkin_ws>
$ source devel/setup.bash
$ roslaunch robot world.launch
```

En una segunda ventana de terminal, por favor ejecute:
```
$ cd <path_to_catkin_ws>
$ source devel/setup.bash
$ roslaunch ball_chaser ball_chaser.launch
```

Debería estar viendo el robot siguiendo la bola blanca en Gazebo.

## RViz Setup

También puede visualizar la escena usando RViz. Para hacer esto, espere a que RViz aparezca ejecutando los comandos anteriores. Luego, en el lado izquierdo de RViz en "Displays", realice lo siguiente:

1. Seleccione "odom" para "Fixed Frame".
2. Haga clic en el botón "Add".
   1. Añada "Robot Model" para mostrar el robot en RViz.
   2. Añada "Camera" y elija "/camera/rgb/image_raw" para "Image Topic".
   3. Añada "Laser Scan" y seleccione "/scan" para "Topic".

Ahora debería poder visualizar completamente la escena en RViz.


