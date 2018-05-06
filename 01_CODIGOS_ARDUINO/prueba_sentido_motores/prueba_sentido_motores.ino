// Motor A --> IZQUIERDO
int ENA = 6;
int IN1 = 13;
int IN2 = 12;

// Motor B --> DERECHO
int ENB = 5;
int IN3 = 11;
int IN4 = 10;

int velocidad = 200;

void setup()
{
  Serial.begin(9600) ;
  
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
}

void loop()
{
  // Lectura del puerto serie
  if (Serial.available())
    switch (Serial.read())
    {
      case 'F':
        Adelante();
        break;
      case 'B':
        Atras();
        break;
      case 'R':
        Derecha();
        break;
      case 'L':
        Izquierda();
        break;
      case 'S':
        Parar();
        break;
    }
}

void Adelante ()
{
  // Direccion motor A
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  analogWrite (ENA, velocidad); // Velocidad motor A
  // Direccion motor B
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  analogWrite (ENB, velocidad); // Velocidad motor B
}

void Atras ()
{
  // Direccion motor A
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  analogWrite (ENA, velocidad); // Velocidad motor A
  // Direccion motor B
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  analogWrite (ENB, velocidad); // Velocidad motor B
}

void Derecha ()
{
  // Direccion motor A
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  analogWrite (ENA, velocidad); // Velocidad motor A
  // Direccion motor B
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  analogWrite (ENB, velocidad); // Velocidad motor B
}

void Izquierda ()
{
  // Direccion motor A
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  analogWrite (ENA, velocidad); // Velocidad motor A
  // Direccion motor B
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  analogWrite (ENB, velocidad); // Velocidad motor B
}

void Parar ()
{
  // Direccion motor A
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
  analogWrite (ENA, 0); // Velocidad motor A
  // Direccion motor B
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
  analogWrite (ENB, 0); // Velocidad motor B
}

