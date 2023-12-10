#!/usr/bin/env bash

# Check if the 'hello' executable exists and remove it if it does
if [ -f min ]; then
    rm -f main
fi

# Compile the C program 'hello.c' and create an executable named 'hello'
gcc main.c  -o main -lm

# Run the compiled program 'hello'
./main
