// Definicion de cada uno de los pines a los que se conectan los sensores infrarrojos
const int sensorDerecha = 2;
const int sensorCentro = 3;
const int sensorIzquierda = 4;

void setup()
{
  pinMode(sensorCentro, INPUT);
  pinMode(sensorDerecha, INPUT);
  pinMode(sensorIzquierda, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  int value = 0; // Variable para alamacenar el valor de la lectura
  value = digitalRead(sensorIzquierda);  //Lectura digital de pin

  if (value == HIGH)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
