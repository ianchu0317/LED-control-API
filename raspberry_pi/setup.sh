#!/bin/bash

## CONFIGURACIONES SERVIDOR WEB
printf "\n[+] INICIANDO CONFIGURACIONES\n"
# Instalar o actualizar apache2
printf "\nInstalando servidor apache2...\n"
sudo apt install apache2

# Mover archivos al carpeta de destino
printf "\nMoviendo archivos a /var/www/html...\n"
sudo cp -r ./web/* /var/www/html/

## CONFIGURACIONES API
printf "\nInstalando y/o actualizando Python 3...\n"
sudo apt install python3

# Crear entorno virtual para instalar dependencias
printf "\nCreando carpeta virtual ./api/.venv...\n"
cd ./api
python3 -m venv .venv
source .venv/bin/activate

printf "\nInstalando paquetes de Python 3 para servidor API...\n"
python3 -m pip install -r ../requeriments.txt
deactivate

printf "\nConfigurando start.sh ...\n"
cd ..
chmod +x start.sh


printf "\n[+]CONFIGURACIONES FINALIZADAS !!!\n"
