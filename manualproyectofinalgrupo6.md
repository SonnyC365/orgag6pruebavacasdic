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


## Funcionamiento del Sistema

El sistema funciona recibiendo comandos desde una computadora a través de comunicación serial. Estos comandos son interpretados por el Arduino, el cual ejecuta las acciones correspondientes sobre los dispositivos conectados.

El estado del sistema se actualiza en tiempo real y se muestra en la pantalla LCD, permitiendo al usuario conocer qué dispositivos se encuentran activos. Adicionalmente, el sistema puede almacenar configuraciones en memoria EEPROM para restaurarlas automáticamente tras un reinicio.

### Flujo General del Sistema

1. El usuario envía un comando desde la computadora.
2. Arduino recibe e interpreta el comando.
3. Se ejecuta la acción correspondiente sobre los actuadores.
4. El estado del sistema se actualiza.
5. La información se muestra en la pantalla LCD.
6. Las configuraciones relevantes se almacenan en EEPROM si es necesario.

---

## Diagrama del Circuito

![Captura de pantalla 2025-12-29 223048](https://hackmd.io/_uploads/BJO9hCx4Wl.png)

---

## Montaje de Circuito y Maqueta

![WhatsApp Image 2025-12-30 at 1.12.48 AM](https://hackmd.io/_uploads/rkNrtWZVbe.jpg)

![WhatsApp Image 2025-12-30 at 1.13.35 AM](https://hackmd.io/_uploads/rkESYbbEZg.jpg)
![WhatsApp Image 2025-12-30 at 1.12.49 AM (3)](https://hackmd.io/_uploads/S1dStZ-EWl.jpg)

![WhatsApp Image 2025-12-30 at 1.12.49 AM (2)](https://hackmd.io/_uploads/SkuSF-WN-l.jpg)

![WhatsApp Image 2025-12-30 at 1.12.49 AM (1)](https://hackmd.io/_uploads/SJFHYW-V-g.jpg)

![WhatsApp Image 2025-12-30 at 1.12.49 AM](https://hackmd.io/_uploads/SkdSK-W4-g.jpg)

## GUI en Processing

![proc1](https://hackmd.io/_uploads/Bk2LRZ-V-e.png)
![proc4](https://hackmd.io/_uploads/Syp8CWZ4Wl.png)
![proc3](https://hackmd.io/_uploads/r1lP0-WNbg.png)
![proc2](https://hackmd.io/_uploads/HyxD0-ZN-x.png)

### Componentes Principales del Processing

1. **ControlCasa.pde** - Archivo principal que maneja la interfaz y comunicación
2. **Boton.pde** - Clase base para botones interactivos
3. **BotonCarga.pde** - Botón especializado para cargar archivos
4. **BotonMostrar.pde** - Botón para visualizar escenas guardadas
5. **GestorArchivos.pde** - Procesador de archivos .org
6. **Console.pde** - Consola de mensajes (implementación básica)

## Funcionamiento de la Interfaz

### Inicialización (`setup()`)

1. **Configuración de ventana**: 980x540 píxeles
2. **Carga de fuentes**: Arial normal y bold
3. **Conexión serial**: 
   - Intenta conectar al primer puerto disponible
   - Velocidad: 9600 baudios
   - Si falla, continúa en modo simulación
4. **Creación de interfaz**: Genera todos los botones de control

### Secciones de Control

#### 1. Control de Iluminación
- **5 zonas**: Sala, Comedor, Cocina, Baño, Habitación
- **Comandos individuales**: L1ON, L1OFF, L2ON, L2OFF, etc.
- **Comandos globales**: ALLON, ALLOFF
- Cada zona tiene color distintivo para identificación visual

#### 2. Ventilador
- **4 velocidades**: Apagado (FAN0), Baja (FAN1), Media (FAN2), Alta (FAN3)
- Intensidad visual según velocidad

#### 3. Control de Puerta
- **TOGGLE** (DOOR): Alterna estado
- **ABRIR** (DOOROPEN): Abre puerta
- **CERRAR** (DOORCLOSE): Cierra puerta

#### 4. Escenas Predefinidas
- **FIESTA**: Activa escena de fiesta
- **RELAX**: Activa escena de relajación
- **NOCHE** (NIGHT): Activa escena nocturna
- **DETENER** (STOP): Detiene escena en ejecución

#### 5. Comandos del Sistema
- **ESTADO** (STATUS): Consulta estado del Arduino
- **VERSION**: Solicita versión del firmware
- **REINICIAR** (RESET): Reinicia sistema
- **LISTAR ESCENAS** (LIST_SCENES): Lista escenas en EEPROM
- **BORRAR ESCENAS** (ERASE_SCENES): Borra todas las escenas
- **CARGAR ARCHIVO .ORG**: Abre selector de archivos
- **MOSTRAR ESCENA**: Visualiza contenido de escena guardada


## Proceso de Carga de Archivos .org

### Flujo de Ejecución

```
Usuario hace clic → BotonCarga.alClick() → selectInput() 
→ Usuario selecciona archivo → fileSelected() 
→ GestorArchivos.procesarArchivo() → Envío a Arduino
```

### Pasos Detallados en `GestorArchivos.procesarArchivo()`

#### 1. Validación
```java
if (!ruta.toLowerCase().endsWith(".org")) {
    // Rechaza el archivo
}
```

#### 2. Extracción del Nombre
```java
String nombreEscena = split(nombreArchivo, '.')[0].toUpperCase();
// Ejemplo: "fiesta.org" → "FIESTA"
```

#### 3. Lectura del Archivo
```java
String[] lineas = loadStrings(archivo);
```

#### 4. Protocolo de Envío al Arduino

**Paso 1 - Inicio de carga:**
```
Envía: LOAD_SCENE\n
Espera: 300ms
```

**Paso 2 - Envío de comandos:**
```
Para cada línea válida:
  - Ignora líneas vacías
  - Ignora comentarios (líneas que empiezan con #)
  - Agrega prefijo [M] a la línea
  - Envía: [M]COMANDO\n
  - Espera: 150ms (tiempo para escribir en EEPROM)
```

**Ejemplo de envío:**
```
[M]SALA:ON:500:20
[M]COMEDOR:OFF:500:20
[M]COCINA:ON:300:30
```
