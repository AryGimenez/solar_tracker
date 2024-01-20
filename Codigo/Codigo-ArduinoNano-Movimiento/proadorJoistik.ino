const int pinHorizontal = A4; // Pin para el eje horizontal del joystick
const int pinVertical = A5;   // Pin para el eje vertical del joystick

void setup() {
  Serial.begin(9600); // Inicia la comunicación serial
}

void loop() {
  int valorHorizontal = analogRead(pinHorizontal); // Lee el valor horizontal
  int valorVertical = analogRead(pinVertical);     // Lee el valor vertical

  // Imprime los valores en el Monitor Serial
  Serial.print("Horizontal: ");
  Serial.print(valorHorizontal);
  Serial.print(", Vertical: ");
  Serial.println(valorVertical);

  delay(500); // Pequeña pausa para que sea más fácil leer los valores
}