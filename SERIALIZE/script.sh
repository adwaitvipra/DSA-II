#!/usr/bin/bash

# script to initialize and test the student record system

# comile and link the application 
make

# run the python script to generate database
./script.py

# run the script and generate output
./SERIALIZE < input.txt > output.txt
