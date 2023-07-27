#include "ServoSolarTrak.h"

// Constructor de la clase, que inicializa los pines de los servomotores
ServoSolarTrak::ServoSolarTrak(int verticalPin, int horizontalPin)
{
    _servoVerticalPin = verticalPin;
    _servoHorizontalPin = horizontalPin;
}

// Inicialización de los pines de los servomotores
void ServoSolarTrak::attach()
{
    _servoVertical.attach(_servoVerticalPin);
    _servoHorizontal.attach(_servoHorizontalPin);
}

// Detiene los Servomotores
void ServoSolarTrak::detach()
{
    _servoVertical.detach();
    _servoHorizontal.detach();
}

// Establece el ángulo del servomotor vertical
void ServoSolarTrak::setVerticalAngle(int angle)
{
    angle = constrain(angle, 0, 180);
    _servoVertical.write(angle);
}

// Establece el ángulo del servomotor horizontal
void ServoSolarTrak::setHorizontalAngle(int angle)
{
    angle = constrain(angle, 0, 180);
    _servoHorizontal.write(angle);
}

void ServoSolarTrak::setModoUso(unsigned char modoFuncionamiento) {
    // Validar el valor del modo de funcionamiento
    // Solo permitir los valores 1, 2 o 3
    if (modoFuncionamiento >= 1 && modoFuncionamiento <= 3) {
        _modoFuncionamiento = modoFuncionamiento;
    } else {
        _modoFuncionamiento = 3; // Si mandan un numero que no es igual a 3 que seria detenido
    }
}

// Actuializa el estado de los servos 
void ServoSolarTrak::upgradeServo() {
    
    if (_modoFuncionamiento == 1) {
        // Modo Manual: Ajustar los ángulos según la configuración deseada
        setVerticalAngle(90); // Por ejemplo, ángulo vertical a 90 grados
        setHorizontalAngle(180); // Por ejemplo, ángulo horizontal a 180 grados
    } else if (_modoFuncionamiento == 2) {


    switch (_modoFuncionamiento) {
        case 1: // Modo Manual



        break;
        case 2: // Modo Motor Horizontal


            // Realizar el seguimiento automático en el eje horizontal
            int ldrRightValue = analogRead(_LDR_RIGHT_PIN);
            int ldrLeftValue = analogRead(_LDR_LEFT_PIN);

            int horizontalAngle = map(ldrLeftValue - ldrRightValue, _LDR_MAX, _LDR_MAX, _HORIZONTAL_MIN_ANGLE, _HORIZONTAL_MAX_ANGLE);

            servoHorizontal.write(horizontalAngle);        
        break;
        case 3: // Modo Automatico


            break
    }





    } else if (_modoFuncionamiento == 3) {
            // Leer los valores analógicos de los sensores KY-023
            
            int verticalValue = analogRead(_JOYSTICK_VERTICAL_PIN);
            int horizontalValue = analogRead(_JOYSTICK_HORISONTAL_PIN);

            // Mapear los valores leídos a ángulos para los servos
            int verticalAngle = map(verticalValue, 0, 1023, VERTICAL_MIN_ANGLE, VERTICAL_MAX_ANGLE);
            int horizontalAngle = map(horizontalValue, 0, 1023, HORIZONTAL_MIN_ANGLE, HORIZONTAL_MAX_ANGLE);

            // Mover los servos a los ángulos calculados
            _servoVertical.write(verticalAngle);
            _servoHorizontal.write(horizontalAngle);

    }
} 


// Modifica el los Angulos de los servos utilizando el Joystick Arduino KY 023
// Codigo de ejemplo falta terminalr de implementar https://blog.uelectronics.com/tarjetas-deValor_Xmaxsarrollo/arduino/control-de-servomotores-sg90-con-modulo-ky-023-sensor-joystick/
void ServoSolarTrak::_upgradeJoystick() {
    int valX = analogRead(_JOYSTICK_HORISONTAL_PIN);
    int valY = analogRead(_JOYSTICK_VERTICAL_PIN);

    int Valor_Xmax = 1023; //Constante del valor máximo para X
    int Valor_Xmin = 0;    //Constante del valor mínimo para X
    
    int Valor_Ymax = 1023; //Constante del valor máximo para Y
    int Valor_Ymin = 0;    //Constante del valor mínimo para Y

    
    if (valX > 511) {               //Movimiento del eje X a lado Izquierdo partiendo del centro (valor de 511)
        Valor_Xmax = 1023 - valX + 511; //La constante del valor máximo para X se modificara con el nuevo valor 
        Valor_Xmin = 0;                 //La constante del valor mínimo se mantendrá
    } else if (valX < 511) {          //Movimiento del eje X a lado Derecho partiendo del centro (valor de 511)
        Valor_Xmax = 1023;              //La constante del valor máximo se mantendrá
        Valor_Xmin = 511 - valX;         //La constante del valor mínimo para X se modificara con el nuevo valor 
    } 
    
    if (valY > 511) {                //Movimiento del eje Y hacia Arriba partiendo del centro (valor de 511)
        Valor_Ymax = 1023 - valY + 511; //La constante del valor máximo para Y se modificara con el nuevo valor 
        Valor_Ymin = 0;                  //La constante del valor mínimo se mantendrá 
    } else if (valY < 511) {          //Movimiento del eje Y hacia Abajo partiendo del centro (valor de 511)
        Valor_Ymax = 1023;              //La constante del valor máximo se mantendrá
        Valor_Ymin = 511 - valY;         //La constante del valor mínimo para Y se modificara con el nuevo valor
    }



    int mappedX = map(valX, Valor_Xmin, Valor_Xmax, 0, 180);
    int mappedY = map(valY, Valor_Ymin, Valor_Ymax, 0, 180);

    setHorizontalAngle(mappedX);
    setVerticalAngle(mappedY); 
}


// Modifica el angulo del servo vertical utilizando el Joystick Arduino KY 023 
void ServoSolarTrak::_upgradeJoystickVertical() {
   
    int valY = analogRead(_JOYSTICK_VERTICAL_PIN);
    
    int Valor_Ymax = 1023; //Constante del valor máximo para Y
    int Valor_Ymin = 0;    //Constante del valor mínimo para Y

    bool flag = false; // Bandera para saber si se ha movido el joystick

    if (valY > 511) {                //Movimiento del eje Y hacia Arriba partiendo del centro (valor de 511)
        Valor_Ymax = 1023 - valY + 511; //La constante del valor máximo para Y se modificara con el nuevo valor 
        Valor_Ymin = 0;                  //La constante del valor mínimo se mantendrá 
    } else if (valY < 511) {          //Movimiento del eje Y hacia Abajo partiendo del centro (valor de 511)
        Valor_Ymax = 1023;              //La constante del valor máximo se mantendrá
        Valor_Ymin = 511 - valY;         //La constante del valor mínimo para Y se modificara con el nuevo valor
    }
    int mappedX = map(valX, Valor_Xmin, Valor_Xmax, 0, 180);
    int mappedY = map(valY, Valor_Ymin, Valor_Ymax, 0, 180);

    setHorizontalAngle(mappedX);
    setVerticalAngle(mappedY); 
}


// Modifica los angulos de los servos utilizando las fotoreistencias LDR
void ServoSolarTrak::_upgredeLDR(){
    // Realizar el seguimiento automático en ambos ejes
    int ldrUpValue = analogRead(_LDR_UP_PIN);
    int ldrDownValue = analogRead(_LDR_DOWN_PIN);
    int ldrRightValue = analogRead(_LDR_RIGHT_PIN);
    int ldrLeftValue = analogRead(_LDR_LEFT_PIN);

    int verticalAngle = map(ldrUpValue - ldrDownValue, -_LDR_MAX, _LDR_MAX, _VERTICAL_MIN_ANGLE, _VERTICAL_MAX_ANGLE);
    int horizontalAngle = map(ldrLeftValue - ldrRightValue, _LDR_MAX, _LDR_MAX, _HORIZONTAL_MIN_ANGLE, _HORIZONTAL_MAX_ANGLE);

    servoVertical.write(verticalAngle);
    servoHorizontal.write(horizontalAngle);
}

// Modifica el angulo del servo vertical utilizando las fotoreistencias LDR
void ServoSolarTrak::_upbradeLDRHorisontal(){
    // Realizar el seguimiento automático en ambos ejes
    int ldrRightValue = analogRead(_LDR_RIGHT_PIN);
    int ldrLeftValue = analogRead(_LDR_LEFT_PIN);

    int horizontalAngle = map(ldrLeftValue - ldrRightValue, _LDR_MAX, _LDR_MAX, _HORIZONTAL_MIN_ANGLE, _HORIZONTAL_MAX_ANGLE);

    servoHorizontal.write(horizontalAngle);        
}



