document.addEventListener('DOMContentLoaded', () => {
    const changeEffectButton = document.getElementById('changeEffectButton');
    const speedSlider = document.getElementById('speedSlider');
    const speedValue = document.getElementById('speedValue');
    let cooldown = false;


    // URLs routing del API 
    let urlChangeEffect = 'http://192.168.248.68:8000/api/leds/change-effect';
    let urlSetSpeed = 'http://192.168.248.68:8000/api/leds/change-speed';


    const enableButton = () => {
        changeEffectButton.disabled = false;
        cooldown = false;
    };


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
            speedValue.textContent = data.velocity; // Actualizar la velocidad mostrada en pantalla
            setTimeout(() => { cooldown = false; }, 500); // Cooldown de 0.5 segundos
        })
        .catch(error => {
            console.error('Error al cambiar la velocidad:', error);
            cooldown = false;
        });
    });
});
