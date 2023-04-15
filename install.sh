#!/bin/bash
# Commenter les 4 lignes suivantes si non nécessaires
sudo apt-get update
sudo apt-get install libgtk-3-dev 
sudo apt-get install libcanberra-gtk-dev
sudo apt upgrade
# Compilation des MonPG + MediaPlayer
gcc -Wall MonPG1.c -o MonPG1.exe
gcc -Wno-format -o MonPG2.exe MonPG2.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
gcc -Wall MonPG3.c -o MonPG3.exe
gcc -Wall MonPG4.c -o MonPG4.exe
gcc -Wall MonPG5.c -o MonPG5.exe
gcc -Wall MonPG6.c -o MonPG6.exe
gcc -Wno-format -o MediaPlayer.exe MediaPlayer.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
