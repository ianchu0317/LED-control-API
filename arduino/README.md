# LEDs-arduino
Parte del código de Arduino fue reutilizado de un proyecto anterior: [LEDs-Arduino](https://github.com/ianchu0317/LEDs-arduino/).

En esta versión, se añadieron nuevas funciones, incluyendo botones que funcionan de manera virtual, 
ya que son controlados mediante pulsaciones enviadas desde la Raspberry Pi. 
Para gestionar esta funcionalidad, se crearon los archivos `button_receiver.h` y `button_receiver.cpp`, 
donde se configuran los botones y su interacción con el sistema.

El sistema de velocidad cuenta con **9 niveles**, donde **1** es el más lento y **9** el más rápido. 
Por defecto, **el programa inicia en el nivel 5**. 
Más adelante, se explica en detalle cómo modificar las variables relacionadas con la velocidad.


## Cómo conectar los componentes físicos
Los componentes se conectan de la siguiente manera como se muestra en la imagen: 


## Instalación
1. **Abrir el código en Arduino IDE**
    - Abrimos el archivo app.ino en el Arduino IDE.
    - Conectamos el Arduino a la computadora.
   
![image](https://github.com/user-attachments/assets/6a17b676-88e4-43f4-8e40-ff669ecbfad5)



2. **Subir el código**
    - Hacemos clic en el botón "Upload" para compilar y cargar el código en el Arduino.

![image](https://github.com/user-attachments/assets/0a296712-c6cd-4ed0-99ee-b962b68fdc37)



## Configuración de velocidades 
Las velocidades de los patrones están definidas en milisegundos y representan el tiempo de debounce antes de avanzar al siguiente paso.

### Modificar velocidades iniciales
Para ajustar las velocidades de los patrones de LEDs, edita las líneas **25** a **28** del archivo  `effects.cpp`:
```cpp
// Velocidades para los efectos
int intercalate_vel = 65;         // ms
int fade_vel = 55;                // ms 
int intercalate_in_out_vel = 85;  // ms
```

### Modificar la cantidad de avance por nivel
Para cambiar los incrementos de velocidad en cada nivel, modifica las líneas **27** a **30** del archivo `button_receiver.cpp`
```cpp
// Pasos para cada nivel
const int fade_step = 5;
const int intercalate_step = 10; 
const int intercalate_in_out_vel = 10; 
```

