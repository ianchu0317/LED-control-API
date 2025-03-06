# LED-control-API
Este proyecto permite controlar los patrones de luces LED mediante Arduino,
con una interfaz de usuario desarrollada en Raspberry Pi que facilita su gestión desde distintos dispositivos. 
Además, cuenta con un botón físico para cambiar entre patrones o efectos, 
y una API que permite tanto modificar los patrones como ajustar su velocidad

---

## Objetivos del Proyecto
- Desarrollar un sistema para controlar patrones de luces LED de forma remota.
- Implementar una API en Raspberry Pi para gestionar los efectos y la velocidad de los LEDs.
- Crear una interfaz web intuitiva para el control desde distintos dispositivos.
- Permitir el cambio manual de patrones mediante un botón físico.
- Asegurar una integración eficiente entre Arduino y Raspberry Pi.

## Objetivos de Aprendizaje
- Aprender a gestionar un proyecto desde cero.
- Iniciar con el desarrollo backend creando una API.
- Combinar electrónica, programación y software para aplicaciones en domótica.
- Entender la conexión entre frontend y backend.
- Aprender a comunicar Arduino con Raspberry Pi.
---

## Estructura
```
/Led-control-API
  /design         -> Diseños, diagramas y planificación del proyecto
  /arduino        -> Código para el Arduino
  /raspberry_pi   -> Código para la Raspberry Pi (servidor API y web)
    /web          -> Frontend (interfaz web)
    /api          -> Backend y servidor API en Python
    /scripts      -> Scripts de Python para pruebas y testeo
```

## Materiales
- Microcontroladores:
  - Arduino UNO R3
  - Raspberry Pi 4 Model B
- Luces y resistencias:
  - 6 LEDs
  - 6 resistencias de 220 Ω
  - 3 resistencias de 10 kΩ
- Conexiones:
  - 12 cables macho-macho
  - 3 cables macho-hembra
- Otros:
  - Protoboard de 830 puntos
  - Botón puente doble H


## Requisitos (software)

- **Arduino IDE** para cargar el código en el microcontrolador.
- **Python 3** y **pip** para ejecutar el servidor y la API en la Raspberry Pi.
- Misma conexión local (LAN) para comunicar los dispositivos.


## Ejecución del Proyecto
1. **Configurar el Arduino:**
   - Abrir el archivo `app.ino` en el Arduino IDE.
   - Conectar el Arduino a la computadora y cargar el código.

2. **Configurar la Raspberry Pi:**
   - Clonar el repositorio en tu Raspberry Pi.
   - Ejecutar `setup.sh` para configurar carpetas e instalar dependencias
   - Iniciar el servidor web y API ejecutando `start.sh`


## Más información
Para detalles más específicos sobre la configuración de Arduino, consulta el archivo [`arduino/README.md`](arduino/README.md).  
Para detalles sobre la configuración de la Raspberry Pi y la API, consulta el archivo [`raspberry_pi/README.md`](raspberry_pi/README.md).

La planificación del proyecto se encuentra en formato PDF dentro de [`/design`](design/)
