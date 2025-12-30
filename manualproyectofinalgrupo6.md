# Universidad San Carlos de Guatemala
Facultad de Ingeniería
Ingeniería en Ciencias y Sistemas

---

# Proyecto: Casa Domotizada con Control de Ambientes y Ventilador Automatizado

**Curso:** Organización Computacional  
**Sección:** P  
**Grupo:** 6  
**Repositorio:** ORGA_G6_DIC2025

---

## Integrantes del Equipo

| Nombre Completo | Carné | Rol en el Proyecto |
|-----------------|-------|-------------------|
| Sonny Evans Castillo Soto | 202211058 | Processing + Arduino|
| Kevin Haroldo	Albizures Sirín | 202006681 | Arduino + Doc. |
| Brenda Paola Gramajo Paniagua | 201801539 | Arduino + Doc. |
| Augusto Sebastián Alvarado Letona | 202003485 | Processing + Arduino|
| Obed Bosbely Fuentes Eredia | 200516309 | Arduino + Maqueta/Circuito Físico |

---

## Introducción

La presente documentación describe el diseño conceptual de un sistema de casa domotizada, cuyo objetivo es integrar dispositivos electrónicos controlados por un microcontrolador para simular el funcionamiento inteligente de una vivienda moderna.

El sistema propuesto combina hardware basado en Arduino con actuadores electrónicos como LEDs, un motor DC y un servomotor, así como una interfaz de comunicación serial que permite controlar el sistema desde una computadora. Adicionalmente, se incorpora una pantalla LCD con interfaz I2C para proporcionar retroalimentación visual del estado del sistema.

A través de esta práctica se aplican conceptos fundamentales de sistemas embebidos, comunicación serial, control de actuadores y manejo de memoria no volátil, permitiendo comprender cómo interactúan los componentes físicos y lógicos dentro de un entorno de automatización residencial.

---

## Marco Teórico

### Domótica

La domótica es el conjunto de tecnologías orientadas a automatizar y controlar de forma inteligente los sistemas de una vivienda. Su finalidad principal es mejorar la comodidad del usuario, optimizar el consumo energético y aumentar la seguridad mediante la integración de dispositivos electrónicos controlados por sistemas computacionales.

Un sistema domótico se compone generalmente de sensores, actuadores, una unidad de control y un medio de comunicación que permite la interacción entre el usuario y el sistema. En este proyecto, el enfoque se centra en la automatización de iluminación, ventilación y acceso.

---

### Sistemas Embebidos

Un sistema embebido es un sistema computacional diseñado para realizar una función específica dentro de un sistema mayor. En este proyecto, el microcontrolador Arduino actúa como el núcleo del sistema, encargado de recibir comandos, procesar la lógica de control y accionar los dispositivos conectados.

Los sistemas embebidos se caracterizan por su operación en tiempo real, su bajo consumo de recursos y su capacidad de interactuar directamente con el hardware, lo que los hace ideales para aplicaciones de automatización y control.

---

### Comunicación Serial

La comunicación serial es un método de transmisión de datos en el cual la información se envía bit a bit a través de un canal de comunicación. En sistemas embebidos, el protocolo UART es uno de los más utilizados debido a su simplicidad y confiabilidad.

En el sistema propuesto, la comunicación serial se establece entre el Arduino y una computadora mediante una conexión USB, permitiendo el envío de comandos en formato de texto y la recepción de mensajes de estado. Este mecanismo facilita el control remoto del sistema domótico y la validación de su funcionamiento.

---

### Control de Iluminación por Ambientes

El control de iluminación se implementa mediante LEDs que representan las luces de cada ambiente de la vivienda. Cada LED puede ser controlado de manera individual, permitiendo encender o apagar áreas específicas según las necesidades del usuario.

Además del control manual, el sistema permite la creación de escenas luminosas, las cuales agrupan configuraciones de iluminación predefinidas. Estas escenas permiten ejecutar múltiples acciones con un solo comando, simulando escenarios reales como modos nocturnos, ambientes relajados o iluminación general.

---

### Motor DC y Ventilación Automatizada

El motor DC se utiliza para simular un sistema de ventilación dentro de la vivienda. Su funcionamiento se controla mediante señales PWM (Pulse Width Modulation), lo que permite variar la velocidad del motor de acuerdo con el nivel seleccionado.

Este tipo de control es común en sistemas domóticos, ya que permite regular el funcionamiento de dispositivos eléctricos de forma eficiente, adaptándose a diferentes condiciones ambientales o preferencias del usuario.

---

### Servomotor y Control de Acceso

El servomotor es un actuador que permite controlar la posición angular de su eje con alta precisión. En este proyecto, se utiliza para simular la apertura y cierre de una puerta automatizada.

El sistema implementa una lógica de alternancia que permite cambiar el estado de la puerta entre abierta y cerrada mediante un único comando, representando un sistema de acceso inteligente típico en viviendas domotizadas.

---

### Memoria EEPROM

La memoria EEPROM es un tipo de memoria no volátil que permite almacenar información incluso cuando el sistema se apaga. En sistemas domóticos, la EEPROM es utilizada para conservar configuraciones importantes, como el estado de dispositivos o la última escena activa.

Su uso en este proyecto permite que el sistema recupere automáticamente su configuración previa al reiniciarse, proporcionando una experiencia más realista y robusta.

---

## Objetivos

### Objetivo General

Diseñar conceptualmente un sistema de casa domotizada que integre control de iluminación, ventilación y acceso, utilizando un microcontrolador Arduino, comunicación serial y almacenamiento persistente de configuraciones.

### Objetivos Específicos

1. Analizar la arquitectura de un sistema domótico basado en Arduino.
2. Describir el control de iluminación por ambientes mediante actuadores electrónicos.
3. Explicar el funcionamiento de motores DC y servomotores en sistemas de automatización.
4. Comprender el uso de comunicación serial para el control remoto del sistema.
5. Analizar la importancia de la memoria EEPROM en la persistencia de datos.

---

## Arquitectura del Sistema

El sistema de casa domotizada se divide conceptualmente en los siguientes módulos:

1. **Módulo de Control (Arduino)**  
   Encargado de procesar los comandos recibidos, ejecutar la lógica de control y accionar los dispositivos conectados.

2. **Módulo de Actuadores**  
   Incluye los LEDs para iluminación, el motor DC para ventilación y el servomotor para el control de acceso.

3. **Módulo de Comunicación Serial**  
   Permite la interacción entre el usuario y el sistema mediante comandos enviados desde una computadora.

4. **Módulo de Visualización**  
   Proporciona retroalimentación visual del estado del sistema mediante una pantalla LCD con interfaz I2C.

---
