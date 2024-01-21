const int pinLDR_Arriba = A0;    // Pin para el LDR de "Arriba"
const int pinLDR_Izquierda = A3; // Pin para el LDR de "Izquierda"
const int pinLDR_Abajo = A2;     // Pin para el LDR de "Abajo"
const int pinLDR_Derecha = A1;   // Pin para el LDR de "Derecha"

void setup() {
  Serial.begin(9600); // Inicia la comunicación serial
}

void loop() {
  int valorLDR_Arriba = analogRead(pinLDR_Arriba);       // Lee el valor de "Arriba"
  int valorLDR_Izquierda = analogRead(pinLDR_Izquierda); // Lee el valor de "Izquierda"
  int valorLDR_Abajo = analogRead(pinLDR_Abajo);         // Lee el valor de "Abajo"
  int valorLDR_Derecha = analogRead(pinLDR_Derecha);     // Lee el valor de "Derecha"

  // Imprime los valores en el Monitor Serial
  Serial.print("LDR Arriba: ");
  Serial.print(valorLDR_Arriba);
  Serial.print(", LDR Izquierda: ");
  Serial.print(valorLDR_Izquierda);
  Serial.print(", LDR Abajo: ");
  Serial.print(valorLDR_Abajo);
  Serial.print(", LDR Derecha: ");
  Serial.println(valorLDR_Derecha);

  delay(500); // Pequeña pausa para facilitar la lectura de los valores
}