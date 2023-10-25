#!/bin/bash

rm game.exe

# Check if the --debug flag is present
if [[ "$*" == *--debug* ]]; then
    DEBUG_FLAG="--debug"
else
    DEBUG_FLAG=""
fi

g++ src/*.cpp -m64 -g -Wall -I include -lSDL2 -lSDL2_image -o game.exe

# run with debug flag if present
./game.exe $DEBUG_FLAG
