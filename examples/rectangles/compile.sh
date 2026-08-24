#!/usr/bin/env bash

echo "Compiling Example: rectangles"

g++ rectangles.cpp -Iinclude -Linclude -lOmega_SSD1306 -o rectangles

echo "Finished"
