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

> Se alimentarán con el portapilas mencionado anteriormente, es decir, 6V.

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

| DRIVER | MOTOR IZQUIERDO | MOTOR DERECHO |
|:--------:|:--------:|:--------:|
| OUT1 | ROJO  | -     |
| OUT2 | NEGRO | -     |
| OUT3 | -     | ROJO  |
| OUT4 | -     | NEGRO |

**Conexión del driver con el Arduino:**

> *Retirar los jumpers de los terminales ENA y ENB*

| DRIVER | ARDUINO |
|:--------:|:--------:|
| GND | GND |
| +5V | 5V  |
| ENA | D6  |
| IN1 | D13 |
| IN2 | D12 |
| IN3 | D11 |
| IN4 | D10 |
| ENB | D5  |

**Conexión de los sensores infrarrojos con el Arduino:**

Se emplearán los terminales D0 de los sensores y los terminales VCC y GND de cada uno de ellos se conectarán a 5V y GND, respectivamente.

| MÓDULO INFRARROJO | ARDUINO |
|:--------:|:--------:|
| Sensor izquierda | D4 |
| Sensor central   | D3 |
| Sensor derecha   | D2 |

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
|:--------:|:--------:|:--------:|
| HIGH      | LOW       | Giro sentido A |
| LOW       | HIGH      | Giro sentido B |
| LOW       | LOW       | Motor parado   |

La velocidad de cada uno de los motores se controlará mediante los pines ENA, para controlar el motor A, y ENB, para el motor B. Bastará con enviar una señal PWM a cada uno de estos pines para variar la velocidad de cada motor.

Sabiendo todo esto se hace uso del sketch `01_CODIGOS_ARDUINO/prueba_sentido_motores.ino` para comprobar el sentido de giro de cada motor a partir de los valores de los pines que se acaban de mencionar.

El sketch contiene cinco funciones para comprobar las distintas funciones de movimiento del robot: `Adelante()`, `Atras()`, `Derecha()`, `Izquierda()` y `Parar()`. Cada una de ellas se seleccionará mediante el envío de una letra a través del terminal.

| LETRA | FUNCIÓN       |
|:--------:|:--------:|
| F     | `Adelante()`  |
| B     | `Atras()`     |
| R     | `Derecha()`   |
| L     | `Izquierda()` |
| S     | `Parar()`     |

Si alguna función resulta errónea bastará con modificar los valores que se envían a los pines IN1 e IN2, para el motor A, o IN3 e IN4, para el motor B.

El [sketch](./01_CODIGOS_ARDUINO/prueba_sentido_motores/prueba_sentido_motores.ino) que se ha utilizado ha sido extraído del [proyecto](https://www.prometec.net/direccion-siguelineas/) de [Prometec](https://www.prometec.net/).

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

***
# Robot\_siguelineas\_v2

En esta versión se implementará un PID para controlar la velocidad de giro de cada una de las ruedas del robot.

Para implementar el PID será necesario definir un valor de error y actuar en función de este valor. El error se obtendrá según las lecturas de los sensores infrarrojos, y los distintos valores posibles se recogen en la siguiente tabla:

| Sensor izquierdo | Sensor central | Sensor derecho | ERROR  |
|:--------:|:--------:|:--------:|:--------:|
| 0                | 0              | 1              | **2**  |
| 0                | 1              | 1              | **1**  |
| 0                | 1              | 0              | **0**  |
| 1                | 1              | 0              | **-1** |
| 1                | 0              | 0              | **-2** |

> *EJEMPLO:* Si nos encontramos en el caso en el que el robot se va hacia la izquierda el error valdrá 1 (Caso 011). Será necesario disminuir la velocidad del motor derecho y aumentar la velocidad del motor izquierdo.

Según el ejemplo anterior las variaciones de velocidad de cado uno de los motores quedarían:

	velocidadMotorIzquierdo = velocidadBase + ERROR
	velocidadMotorDerecho = velocidadBase - ERROR

Aquí entra en juego el PID, ya que el valor del error es muy pequeño para controlar el robot de manera óptima.

> *Al ser un robot pequeño únicamente se emplearán el término proporcional y el derivativo.*

El término proporcional (Kp) se usa para que el robot responda más rápidamente y el término derivativo (Kd) para eliminar las oscilaciones. Las fórmulas a emplear serán las siguientes:

	P = error
	D = error - errorAnterior
	PID = (Kp * P) + (Kd * D)

Calculando así la nueva velocidad para cada motor:

	velocidadMotorIzquierdo = velocidadBase + PID
	velocidadMotorDerecho = velocidadBase - PID

> *La velocidad en este punto se limitará con una cota máxima. Ver [sketch](./01_CODIGOS_ARDUINO/Robot_siguelineas_v2/Robot_siguelineas_v2.ino) (Líneas 71-74).*

Los pasos seguidos para obtener los valores de Kp y Kd son:

1. Fijar Kd=0 y aproximar el valor de Kp.
	* Si responde despacio: disminuar Kp.
	* Si se vuelve inestable: aumentar Kp.
2. Cuando se haya encontrado un valor razonable de Kp, fijar Kd=Kp/2 y aproximar en torno a ese valor.
	* Aumentar Kd si hay sobrepico.
	* Disminuir Kd si es inestable.

> *Es posible que también afecte el valor "Sample/Loop Rate" por lo que puede que sea necesario trabajar con un `delay` al final del bucle.*

En resumen, la secuencia del loop sería la siguiente:

1. Lectura de los sensores infrarrojos y determinación de la variable de error.
2. Calcular PID.
3. Almacenar valor del error para el siguiente loop.
4. Calcular y acotar la nueva velocidad de los motores.
5. Enviar información de velocidad a los motores.

En siguientes versiones se implementará la detección de obstáculos mediante sensores ultrasónicos para medir distancia.