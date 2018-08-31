#!/bin/bash
# Variables
FILE1=gobmk_trace.txt
FILE2=mcf_trace.txt


echo ""
echo "================================================================"
echo "Running gshare.out"
echo "================================================================"
echo ""

#compile the file
g++ -std=c++11 gshare.cpp -o gshare.out
#############################################################################
#                           PART A (Change N)                               #
#############################################################################
printf "MCF: misprediction rate:\n"
./gshare.out 8 5 mcf_trace.txt
printf "\n"
printf "GoBMK: misprediction rate:\n"
./gshare.out 8 5 gobmk_trace.txt
printf "\n"
printf "\n"

printf "MCF: misprediction rate:\n"
./gshare.out 4 2 mcf_trace.txt
printf "\n"
printf "GoBMK: misprediction rate:\n"
./gshare.out 4 2 gobmk_trace.txt
printf "\n"
printf "\n"

printf "MCF: misprediction rate:\n"
./gshare.out 3 1 mcf_trace.txt
printf "\n"
printf "GoBMK: misprediction rate:\n"
./gshare.out 3 1 gobmk_trace.txt
printf "\n"
printf "\n"