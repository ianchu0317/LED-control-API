#!/bin/bash

sudo service apache2 start

fastapi run ./api/main.py
