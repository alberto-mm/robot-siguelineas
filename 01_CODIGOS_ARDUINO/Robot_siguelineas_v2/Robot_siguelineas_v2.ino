#define VELOCIDAD_MAXIMA 255
#define VELOCIDAD_BASE 150

// Motor A --> IZQUIERDO
const int ENA = 6;
const int IN1 = 13;
const int IN2 = 12;
// Motor B --> DERECHO
const int ENB = 5;
const int IN3 = 11;
const int IN4 = 10;
// Pines de los 3 sensores
const int sensorDerecha = 2;
const int sensorCentro = 3;
const int sensorIzquierda = 4;

// Variables de ajuste del PID
const float Kp = 50;
const float Kd = 30;
// Variables del PID
float P = 0, D = 0, PID = 0;
float error = 0, errorAnterior = 0;

void setup()
{
  //Serial.begin(9600) ;
  // Pines del driver L298N
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  // Pines de los sensores
  pinMode(sensorCentro, INPUT);
  pinMode(sensorDerecha, INPUT);
  pinMode(sensorIzquierda, INPUT);
} // Fin del setup

void loop()
{
  int valorDerecha;
  int valorCentro;
  int valorIzquierda;
  // Lectura de los sensores
  valorDerecha = digitalRead(sensorDerecha);
  valorCentro = digitalRead(sensorCentro);
  valorIzquierda = digitalRead(sensorIzquierda);

  if (valorIzquierda == LOW && valorCentro == LOW && valorDerecha == HIGH) error = 2;         // Robot a la izda
  else if (valorIzquierda == LOW && valorCentro == HIGH && valorDerecha == HIGH) error = 1;   // Robot a la izda
  else if (valorIzquierda == LOW && valorCentro == HIGH && valorDerecha == LOW) error = 0;    // Robot centrado
  else if (valorIzquierda == HIGH && valorCentro == HIGH && valorDerecha == LOW) error = -1;  // Robot a la dcha
  else if (valorIzquierda == HIGH && valorCentro == LOW && valorDerecha == LOW) error = -2;   // Robot a la dcha

  // Calculo del PID
  P = error;
  D = error - errorAnterior;
  PID = (Kp * P) + (Kd * D);

  // Se alamacena el error para el siguiente loop
  errorAnterior = error;

  // Se calcula la nueva velocidad
  int velocidadIzquierda = VELOCIDAD_BASE + PID;
  int velocidadDerecha = VELOCIDAD_BASE - PID;

  //constrain(velocidadIzquierda, 0, VELOCIDAD_MAXIMA);
  //constrain(velocidadDerecha, 0, VELOCIDAD_MAXIMA);

  if (velocidadIzquierda > 255) velocidadIzquierda = VELOCIDAD_MAXIMA;
  else if (velocidadIzquierda < 0) velocidadIzquierda = 0;
  if (velocidadDerecha > 255) velocidadDerecha = VELOCIDAD_MAXIMA;
  else if (velocidadDerecha < 0) velocidadDerecha = 0;

  GirarMotoresAdelante(velocidadIzquierda, velocidadDerecha);

} // Fin del loop

void GirarMotoresAdelante(int velIzda, int velDcha)
{
  // Direccion motor A (Izquierdo)
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  analogWrite (ENA, velIzda); // Velocidad motor A
  // Direccion motor B (Derecho)
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  analogWrite (ENB, velDcha); // Velocidad motor B
} // Fin de GirarMotoresAdelante()

void Parar()
{
  // Direccion motor A
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
  analogWrite (ENA, 0); // Velocidad motor A
  // Direccion motor B
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
  analogWrite (ENB, 0); // Velocidad motor A
} // Fin de Parar()
