# Servidor Raspberry Pi
En este proyecto, tanto la API como el servidor web son gestionados por la Raspberry Pi 
para mantener el producto final portátil y ligero.

El servidor web se configura utilizando Apache 2, 
mientras que la API se maneja con FastAPI en Python.

En esta sección se incluye un script que automatiza la instalación de los archivos necesarios, 
así como otro script para iniciar los servidores de manera automática.


## Instalación, Configuración y Ejecución
Para configurar y ejecutar el proyecto en la Raspberry Pi, sigue estos pasos en la terminal:
1. **Clonar el repositorio**
   ```bash
   git clone https://github.com/ianchu0317/LED-control-API.git
   cd raspberry_pi/
   ```

2. **Configurar el entorno**: Ojo asegurarse de que el script `setup.sh` tenga permisos de ejecución:
   ```bash
    chmod +x setup.sh
    sudo ./setup.sh
   ```

3. **Iniciar los servidores**: Una vez configurado, iniciar los servidores de la API y web con el siguiente comando:
   ```console
   ./start.sh
   ```

---

## Frontend (interfaz web)
La interfaz web está alojada en la Raspberry Pi utilizando el servicio Apache 2.

Para acceder a la página web, solo necesitas abrir un navegador y dirigirte a la IP local de la Raspberry Pi, 
utilizando la siguiente URL: `http://<ip_raspberrypi>`

También es importante modificar los URLs de la API en las líneas **12** a **15** de `script.js` para que las solicitudes se envíen correctamente. 
Asegurar de actualizar las direcciones IP en el código como se muestra a continuación:

```js
    // URLs routing del API 
    let urlChangeEffect = 'http://<ip_raspberrypi>:8000/api/leds/change-effect';
    let urlSetSpeed = 'http://<ip_raspberrypi>:8000/api/leds/change-speed';
    let urlGetSpeed = 'http://<ip_raspberrypi>:8000/api/leds/get-speed';
```

Para hallar la IP local se puede utilizar el comando `ifconfig`.
 
---

## Backend (API)
La API está escrita con FastAPI en Python. 
Esta API se encarga de recibir las solicitudes de la web y enviar pulsaciones correespondientes al Arduino
para modificar las velocidades y los patrones de los LEDs.

### URLs de la API 
Para cambiar el efecto actual, se debe realizar una solicitud **POST** a `http://<ip_raspberrypi>:8000/api/leds/change-effect` con el siguiente Body:
```js
{
  effect: 'next'
}
```

Para cambiar la velocidad, se realizar una solicitud **POST** a `http://<ip_raspberrypi>:8000/api/leds/change-speed`
indicando el nivel de la velocidad deseada. Debe contener un Body con la siguiente estructura: 
```js
{
  level: <num 1-9>    // cualquier número de 1 a 9
}
```

Para obtener la velocidad actual se debe realizar una solicitud **GET** a `http://<ip_raspberrypi>:8000/api/leds/get-speed`. 
Se recibirá una respuesta del siguiente formato: 
```js
{
  level: <num 1-9>    // cualquier número de 1 a 9
}
```
