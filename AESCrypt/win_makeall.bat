gcc -c aes.c
gcc -c main.c
gcc -c hex_utility.c
gcc aes.o hex_utility.o main.o -o aes_demo.exe
del *.o
aes_demo.exe
pause