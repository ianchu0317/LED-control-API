document.addEventListener('DOMContentLoaded', () => {
    const changeEffectButton = document.getElementById('changeEffectButton');
    const speedSlider = document.getElementById('speedSlider');
    const speedValue = document.getElementById('speedValue');
    let cooldown = false;

    const enableButton = () => {
        changeEffectButton.disabled = false;
        cooldown = false;
    };

    changeEffectButton.addEventListener('click', () => {
        if (cooldown) return;
        cooldown = true;
        changeEffectButton.disabled = true;

        fetch('http://192.168.248.68:8000/api/led/change_effect', {
            method: 'POST'/*,
            /*headers: {
                'Content-Type': 'application/json'
            },*/
            //body: JSON.stringify({ efecto: 'siguiente' })
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

        fetch('http://192.168.248.68:8000/api/led/change_speed', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ level: speed })
        })
        .then(response => response.json())
        .then(data => {
            console.log('Velocidad cambiada:', data);
            speedValue.textContent = data.velocidad; // Actualizar la velocidad mostrada en pantalla
            setTimeout(() => { cooldown = false; }, 500); // Cooldown de 0.5 segundos
        })
        .catch(error => {
            console.error('Error al cambiar la velocidad:', error);
            cooldown = false;
        });
    });
});
