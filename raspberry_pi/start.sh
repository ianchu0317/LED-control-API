#!/bin/bash

printf "[+] INICIANDO SERVIDORES\n"
printf "Inciando servidor web...\n"
sudo service apache2 start

printf "\nActivando entorno virtual...\n"
source ./api/.venv/bin/activate

printf "\nIniciando servidor API...\n"
fastapi run ./api/main.py

printf "\nDesactivando entorno virtual...\n"
deactivate

printf "\nDeteniendo servidor web...\n"
sudo service apache2 stop

printf "\n[+]SERVIDORES TERMINADOS\n"
