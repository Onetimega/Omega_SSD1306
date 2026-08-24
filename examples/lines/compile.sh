#!/usr/bin/env bash

echo "Compiling Example: lines"

g++ lines.cpp -Iinclude -Linclude -lOmega_SSD1306 -o lines

echo "Finished"
