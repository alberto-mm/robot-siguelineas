// Motor A --> IZQUIERDO
const int ENA = 6;
const int IN1 = 13;
const int IN2 = 12;

// Motor B --> DERECHO
const int ENB = 5;
const int IN3 = 11;
const int IN4 = 10;

const int sensorDerecha = 2;
const int sensorCentro = 3;
const int sensorIzquierda = 4;

int velocidad = 150;

void setup()
{
  Serial.begin(9600) ;
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  pinMode(sensorCentro, INPUT);
  pinMode(sensorDerecha, INPUT);
  pinMode(sensorIzquierda, INPUT);
}

void loop() {
  int valorDerecha = 0;
  int valorCentro = 0;
  int valorIzquierda = 0;
  valorDerecha = digitalRead(sensorDerecha);
  valorCentro = digitalRead(sensorCentro);
  valorIzquierda = digitalRead(sensorIzquierda);

  if (valorCentro == HIGH && valorDerecha == LOW && valorIzquierda == LOW)
  {
    Adelante();
  }

  if (valorCentro == LOW && valorDerecha == HIGH && valorIzquierda == LOW)
  {
    Derecha();
  }

  if (valorCentro == LOW && valorDerecha == LOW && valorIzquierda == HIGH)
  {
    Izquierda();
  }
  /*
    if (valorCentro == LOW && valorDerecha == LOW && valorIzquierda == LOW) {
      Parar();
    }*/

}

void Adelante() {
  // Direccion motor A
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  analogWrite (ENA, velocidad); // Velocidad motor A
  // Direccion motor B
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  analogWrite (ENB, velocidad); // Velocidad motor B
}

void Derecha() {
  // Direccion motor A
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  analogWrite (ENA, velocidad); // Velocidad motor A
  // Direccion motor B
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  analogWrite (ENB, velocidad); // Velocidad motor B
}

void Izquierda() {
  // Direccion motor A
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  analogWrite (ENA, velocidad); // Velocidad motor A
  // Direccion motor B
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  analogWrite (ENB, velocidad); // Velocidad motor B
}

void Parar() {
  // Direccion motor A
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
  analogWrite (ENA, 0); // Velocidad motor A
  // Direccion motor B
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
  analogWrite (ENB, 0); // Velocidad motor B
}

