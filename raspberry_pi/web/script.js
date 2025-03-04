document.addEventListener('DOMContentLoaded', () => {
    const changeEffectButton = document.getElementById('changeEffectButton');
    const speedSlider = document.getElementById('speedSlider');
    const speedValue = document.getElementById('speedValue');
    let cooldown = false;


    // URLs routing del API 
    let urlChangeEffect = 'http://192.168.248.68:8000/api/leds/change-effect';
    let urlSetSpeed = 'http://192.168.248.68:8000/api/leds/change-speed';
    let urlGetSpeed = 'http://192.168.248.68:8000/api/leds/get-speed';

    // Constante de intervalo para fetch velocidad
    const FETCH_INTERVAL_MS = 1000; // 1000 milisegundos (1 segundo)


    const enableButton = () => {
        changeEffectButton.disabled = false;
        cooldown = false;
    };


    // Fetch inicial para obtener la velocidad actual
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

    // Llamar al fetch inicial
    fetchSpeed();

    // Intervalo para actualizar la velocidad cada 2 segundos
    setInterval(fetchSpeed, FETCH_INTERVAL_MS);


    changeEffectButton.addEventListener('click', () => {
        if (cooldown) return;
        cooldown = true;
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
            setTimeout(enableButton, 500); // Cooldown de 0.5 segundos
        })
        .catch(error => {
            console.error('Error al cambiar el efecto:', error);
            enableButton();
        });
    });


    speedSlider.addEventListener('input', () => {
        if (cooldown) return;
        cooldown = true;

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
            speedValue.textContent = data.level; // Actualizar la velocidad mostrada en pantalla
            setTimeout(() => { cooldown = false; }, 500); // Cooldown de 0.5 segundos
        })
        .catch(error => {
            console.error('Error al cambiar la velocidad:', error);
            cooldown = false;
        });
    });
});
