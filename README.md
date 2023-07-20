Solar Tracker - README
Solar Tracker

Este es el código y documentación para el proyecto Solar Tracker, que es un dispositivo que se encarga de seguir automáticamente el movimiento del sol para mantener un panel solar siempre orientado hacia él y maximizar la eficiencia de la celda fotovoltaica.

Descripción del Proyecto
El Solar Tracker utiliza un Arduino Mega 2560 como su controlador principal. Cuenta con dos servomotores Hitec HS-422: uno para el movimiento vertical y otro para el movimiento horizontal del panel solar. Además, tiene cuatro fotorresistencias (LDR 5538) colocadas estratégicamente para detectar la posición del sol.

El proyecto tiene tres modos de funcionamiento, que se pueden seleccionar mediante botones y se indican mediante LEDs:

Modo Manual: En este modo, los servos están controlados por un módulo Arduino Joystick (Modelo KY 023), permitiendo al usuario realizar el seguimiento del sol de forma manual.

Modo Solo Motor Horizontal: En este modo, el servomotor vertical se detiene, y el servomotor horizontal sigue automáticamente las órdenes proporcionadas por las fotorresistencias para mantener el panel solar orientado horizontalmente hacia el sol.

Modo Automático: En este modo, ambos servomotores siguen automáticamente el movimiento del sol, ajustándose tanto en el eje vertical como en el horizontal para mantener el panel solar siempre en dirección al sol.

El Solar Tracker también incluye un módulo de reloj Tiny RTC para mantener la fecha y hora actualizada. Además, cuenta con un sensor de corriente ACS712 para medir el voltaje, amperaje y potencia del panel solar.

Los datos medidos se guardan en una tarjeta microSD en formato JSON, junto con el lugar físico donde se encuentra el Solar Tracker. La tarjeta microSD también almacena la variable mIntervaloSensado, que define el intervalo en minutos en el que se deben guardar los datos.

El dispositivo está equipado con un display OLED SSD1306 de 0.96" para mostrar información relevante, como el lugar físico, fecha y hora actual, voltaje, amperaje, potencia y nivel de batería. Además, si hay algún problema con la tarjeta SD, se mostrará un mensaje de error en el display.

Instalación y Configuración
Para utilizar el Solar Tracker, sigue estos pasos:

Conecta los componentes según se indica en el código y asegúrate de tener las bibliotecas adecuadas instaladas en tu entorno de desarrollo.

Carga el código del Solar Tracker en tu Arduino Mega 2560 utilizando PlatformIO Labs.

Conecta el Arduino Mega 2560 a una fuente de alimentación y asegúrate de que todos los componentes estén correctamente conectados.

Utiliza los botones para seleccionar el modo de funcionamiento deseado y observa cómo el panel solar sigue automáticamente la posición del sol.

El display OLED mostrará información actualizada, incluyendo el lugar físico, fecha y hora actual, voltaje, amperaje, potencia y nivel de batería.

Para cambiar la configuración del Solar Tracker, como el intervalo de sensado o la fecha del reloj Tiny RTC, utiliza la APK desarrollada en Python para comunicarte con el dispositivo a través del módulo Bluetooth HM-05.

APK (Aplicación Python)
La comunicación con el Solar Tracker se realiza mediante una APK desarrollada en Python. La APK puede enviar comandos para cambiar el intervalo de sensado, la fecha del reloj Tiny RTC y el lugar físico del Solar Tracker. Además, puede recibir datos del Solar Tracker en formato JSON, incluyendo la hora y fecha actual, voltaje, amperaje, potencia y los datos almacenados en la tarjeta microSD.

Para desarrollar la APK, se puede utilizar la biblioteca PySerial para la comunicación por puerto serie y la biblioteca Requests para enviar y recibir datos JSON.

Notas Finales
El proyecto del Solar Tracker es una solución eficiente para maximizar la eficiencia de un panel solar al seguir automáticamente el movimiento del sol a lo largo del día. Con la posibilidad de controlar el dispositivo mediante la APK, se pueden realizar ajustes y recibir información actualizada de manera remota.

Esperamos que este proyecto te sea útil y te inspire en futuros desarrollos. Si tienes alguna pregunta o necesitas ayuda adicional, no dudes en consultar la documentación o preguntar en la comunidad.

¡Disfruta de tu Solar Tracker y el aprovechamiento de la energía solar!
