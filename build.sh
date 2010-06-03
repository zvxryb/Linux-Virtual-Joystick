#! /bin/sh
gcc -std=c99 `python-config --includes` `python-config --libs` -o vjoy main.c vjoy.c vjoy_python.c
