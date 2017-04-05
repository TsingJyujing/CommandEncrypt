#!/bin/sh
gcc -c -O2 *.c 
gcc *.o -o rsa_exp.out
rm *.o
./rsa_exp.out
