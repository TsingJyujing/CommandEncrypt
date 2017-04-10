armcc -c aes.c
armcc -c main.c
armcc -c hex_utility.c
armcc aes.o hex_utility.o main.o -o aes_demo.bin
del *.o
pause