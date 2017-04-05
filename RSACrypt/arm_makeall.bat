armcc -c -O2 cmd_encrypt.c
armcc -c -O2 hex_utility.c
armcc -c -O2 md5.c
armcc -c -O2 mini-gmp.c
armcc -c -O2 rsa_common.c
armcc -c -O2 rsa_test.c
armcc cmd_encrypt.o hex_utility.o md5.o mini-gmp.o rsa_common.o rsa_test.o -o rsa_exp.bin 
del *.o
pause