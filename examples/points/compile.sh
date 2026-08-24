#!/usr/bin/env bash

echo "Compiling Example: points"

g++ points.cpp -Iinclude -Linclude -lOmega_SSD1306 -o points

echo "Finished"
