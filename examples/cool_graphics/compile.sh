#!/usr/bin/env bash

echo "Compiling Example: cool_graphics"

g++ cool_graphics.cpp -Iinclude -Linclude -lOmega_SSD1306 -o cool_graphics

echo "Finished"
