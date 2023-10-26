#!/bin/bash

# Check if the --debug flag is present
if [[ "$*" == *--debug* ]]; then
    DEBUG_FLAG="--debug"
else
    DEBUG_FLAG=""
fi

# Build the C++ program using the Makefile
make

# Run the executable with or without the debug flag
./*.exe $DEBUG_FLAG
