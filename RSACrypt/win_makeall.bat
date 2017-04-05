gcc -c -O2 *.c
gcc *.o -o rsa_exp.exe
del *.o
rsa_exp.exe
pause