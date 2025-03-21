#!/bin/bash -x

gcc -Wall proj3.c -o proj3.out

./proj3.out examples/alice1.txt examples/alice1.txt; cat differencesFoundInFile1.txt differencesFoundInFile2.txt;
