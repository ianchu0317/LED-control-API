document.addEventListener('DOMContentLoaded', () => {
    const effectButton = document.getElementById('changeEffectButton');
    const speedSlider = document.getElementById('speedSlider');
    const speedValue = document.getElementById('speedValue');

    // Cooldown del efecto del botón
    let effectCooldown = false;
    let speedCooldown = false;
    let effectCooldownTime = 1000;  // 1000 ms
    let speedCooldownTime = 1000;    // 1000 ms

    // URLs routing del API 
    let urlChangeEffect = 'http://192.168.248.68:8000/api/leds/change-effect';
    let urlSetSpeed = 'http://192.168.248.68:8000/api/leds/change-speed';
    let urlGetSpeed = 'http://192.168.248.68:8000/api/leds/get-speed';

    // Constante de intervalo para fetch velocidad
    const FETCH_INTERVAL_MS = 500; // 500 milisegundos (0.5 segundos)

    
    // ==========================
    // FUNCIONES AUXILIARES
    // ==========================

   /**
    * Habilitar botón de cambio de efectos
    */
     
    const enableEffectButton = () => {
        changeEffectButton.disabled = false;
        effectCooldown = false;
    };



    // ==========================
    // FUNCIONES PRINCIPALES
    // ==========================

   /**
    * Fetch para obtener y sincronizar velocidad con servidor
    */
    async function fetchSpeed() {
        try {
            const response = await fetch(urlGetSpeed);
            if (!response.ok) throw new Error("Error al obtener la velocidad");

            const data = await response.json();
            speedSlider.value = data.level; // Asigna el valor a la barra
            speedValue.textContent = data.level; // Muestra el valor en pantalla
        } catch (error) {
            console.error("Error al obtener la velocidad:", error);
        }
    }


   /**
    * Fetch para sincronizar velocidad con servidor
    */
    function changeEffect() {
        if (effectCooldown) return;

        effectCooldown = true;
        changeEffectButton.disabled = true;

        fetch(urlChangeEffect, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ 'effect': 'next' })
        })
        .then(response => response.json())
        .then(data => {
            console.log('Efecto cambiado:', data);
            setTimeout(enableEffectButton, effectCooldownTime);
        })
        .catch(error => {
            console.error('Error al cambiar el efecto:', error);
            enableButton();
        });
    };


   /**
    * Cambiar velocidad con POST api
    */
    function changeSpeed() {
        if (speedCooldown) return;
        speedCooldown = true;

        const speed = speedSlider.value;

        fetch(urlSetSpeed, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ level: speed })
        })
        .then(response => response.json())
        .then(data => {
            console.log('Velocidad cambiada:', data);
            speedSlider.value = data.level;
            speedValue.textContent = data.level; // Actualizar la velocidad mostrada en pantalla
            setTimeout(() => { speedCooldown = false; }, speedCooldownTime); // Cooldown de 500 segundos
        })
        .catch(error => {
            console.error('Error al cambiar la velocidad:', error);
            speedCooldown = false;
        });
    };



    // Llamar al fetch inicial
    fetchSpeed();

    // Intervalo para actualizar la velocidad cada 1 segundos
    setInterval(fetchSpeed, FETCH_INTERVAL_MS);

    // Añadir las funciones a los elementos
    effectButton.addEventListener('click', changeEffect); 
    speedSlider.addEventListener('change', changeSpeed);

});
