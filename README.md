# ROBOT SIGUELINEAS

![Robot siguelineas](./images/siguelineas_1.jpg)

## Lista de componentes
A continuación se enumerarán los componentes para montar la versión básica. Los elementos añadidos para las siguientes versiones se enumerarán en cada una de estas.

* Chasis policarbonato
* Arduino Nano
* Protoboard 400 puntos o similar
* 2 x motores DC con ruedas
* Portapilas (4xAA)
* Interruptor
* Rueda loca
* Módulo L298N
* 3 x módulo infrarrojo TCRT5000
* Separadores varios
* Cables dupont

---
### Información de los motores
* Tensión de alimentación: 3-12V (Recomendada: 6-8V)
* Reductora con relación 1:48.
* Par máximo: 800 g·cm (3V)
* Velocidad sin carga: 170 rpm (3V)
* Corriente de carga: 70 mA (3V) - 250 mA máx.

>Se alimentarán con el portapilas mencionado anteriormente, es decir, 6V.

---
### Información del módulo L298N
<center><img src="./images/l298n.jpg" width="200"></center>

Permite controlar motores de entre 5 a 35V con una salida que puede suministrar hasta 2A.

Posee un jumper para controlar el regulador de tensión 7805 que incorpora.

**JUMPER PUESTO - Regulador activado**: Para motores de 5 a 12V. El conector +5V funciona como salida, suministrando hasta 500 mA.

**SIN JUMPER - Regulador desactivado**: Para motores que trabajen con alimentaciones de 12 a 35V. El terminal +5V deberá conectarse a una señal de 5V para alimentar la parte lógica del driver.

***¡ATENCIÓN! No alimentar el terminal +5V con el jumper puesto para evitar dañar el módulo.***

***
# Montaje

La alimentación del portapilas irá directamente al driver conectado el cable rojo al terminal +12V del driver, pasando previamente por el interruptor, y el cable negro al terminal GND.

Asegurarse de que el jumper está puesto, ya que la salida de 5V se utilizará para alimentar el Arduino.

**Conexión del driver con los motores:**

| DRIVER              | MOTOR IZQUIERDO        | MOTOR DERECHO          |
|--------|--------|--------|
| <center>OUT1</center> | <center>ROJO</center>  | <center>-</center>     |
| <center>OUT2</center> | <center>NEGRO</center> | <center>-</center>     |
| <center>OUT3</center> | <center>-</center>     | <center>ROJO</center>  |
| <center>OUT4</center> | <center>-</center>     | <center>NEGRO</center> |

**Conexión del driver con el Arduino:**

> *NOTA: Retirar los jumpers de los terminales ENA y ENB*

| DRIVER               | ARDUINO              |
|--------|--------|
| <center>GND</center> | <center>GND</center> |
| <center>+5V</center> | <center>5V</center>  |
| <center>ENA</center> | <center>D6</center>  |
| <center>IN1</center> | <center>D13</center> |
| <center>IN2</center> | <center>D12</center> |
| <center>IN3</center> | <center>D11</center> |
| <center>IN4</center> | <center>D10</center> |
| <center>ENB</center> | <center>D5</center>  |

**Conexión de los sensores infrarrojos con el Arduino:**

Se emplearán los terminales D0 de los sensores y los terminales VCC y GND de cada uno de ellos se conectarán a 5V y GND, respectivamente.

| MÓDULO INFRARROJO                 | ARDUINO             |
|--------|--------|
| <center>Sensor izquierda</center> | <center>D4</center> |
| <center>Sensor central</center>   | <center>D3</center> |
| <center>Sensor derecha</center>   | <center>D2</center> |

***
# Calibrar sensores infrarrojos

A través del sketch `01_CODIGOS_ARDUINO/prueba_infrarrojos.ino` se permite seleccionar uno de los tres sensores TCRT5000 conectados al Arduino para ajustar el potenciómetro que incorporan para una detección correcta de la línea de color negro. Al detectar la línea se enciende el LED del pin 13 de Arduino Nano.

Otro modo de calibraación sería alimentarlos y observar los LEDs que incluye el módulo; uno para indicar la alimentación y otro de detección. Cuando este úlitmo LED se apaga indica la detección del color negro.

Sabiendo esto se ajustará la sensibilidad de cada uno de los sensores.

***
# Comprobar sentido de giro de los motores

El control del sentido de cada uno de los motores se realizará mediante los pines IN1 e IN2 para el motor A (derecho) y los pines IN3 e IN4 para el motor B (izquierdo).

Las distintas configuraciones de los valores lógicos de estos pines se recogen en la siguiente tabla:

| IN1 / IN3 | IN2 / IN4 | FUNCIÓN |
|--------|--------|--------|
| <center>HIGH</center> | <center>LOW</center> | <center>Giro sentido A</center> |
| <center>LOW</center>  | <center>HIGH</center> | <center>Giro sentido B</center> |
| <center>LOW</center> | <center>LOW</center> | <center>Motor parado</center> |

La velocidad de cada uno de los motores se controlará mediante los pines ENA, para controlar el motor A, y ENB, para el motor B. Bastará con enviar una señal PWM a cada uno de estos pines para variar la velocidad de cada motor.

Sabiendo todo esto se hace uso del sketch `01_CODIGOS_ARDUINO/prueba_sentido_motores.ino` para comprobar el sentido de giro de cada motor a partir de los valores de los pines que se acaban de mencionar.

El sketch contiene cinco funciones para comprobar las distintas funciones de movimiento del robot: `Adelante()`, `Atras()`, `Derecha()`, `Izquierda()` y `Parar()`. Cada una de ellas se seleccionará mediante el envío de una letra a través del terminal.

| LETRA | FUNCIÓN |
|--------|--------|
| <center>F</center> | <center>`Adelante()`</center> |
| <center>B</center> | <center>`Atras()`</center> |
| <center>R</center> | <center>`Derecha()`</center> |
| <center>L</center> | <center>`Izquierda()`</center> |
| <center>S</center> | <center>`Parar()`</center> |

Si alguna función resulta errónea bastará con modificar los valores que se envían a los pines IN1 e IN2, para el motor A, o IN3 e IN4, para el motor B.

***
# Circuito de pruebas
![Robot siguelineas](./images/circuito.jpg)

El circuito que se muestra en la imagen será en el que se realicen las pruebas para comprobar y ajustar el funcionamiento del robot.

La línea negra tiene un grosor de unos 35mm.

***
# Robot\_siguelineas\_v1

El principio de funcionamiento de esta primera versión es:

* Si el sensor central detecta la línea negra el robot se desplazará hacia adelante.
* Si el sensor derecho detecta la línea negra el robot girará hacia la derecha.
* Si el sensor izquierdo detecta la línea negra el robot girará hacia la izquierda.

El sketch de esta versión se encuentra en `01_CODIGOS_ARDUINO/Robot_siguelineas_v1`

En la siguiente versión se implementará un PID.