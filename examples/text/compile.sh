#!/usr/bin/env bash

echo "Compiling Example: text"

g++ text.cpp -Iinclude -Linclude -lOmega_SSD1306 -o text

echo "Finished"
