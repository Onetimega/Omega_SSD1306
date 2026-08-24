#!/usr/bin/env bash

mkdir -p build

echo "Compiling Omega_SSD1306 library"
g++ -v -c source/Omega_SSD1306.cpp -o build/Omega_SSD1306.o

echo "Compilation Terminated, generating *.a file"
ar rcs build/libOmega_SSD1306.a build/Omega_SSD1306.o


echo "Compiled files are found in /build folder"
