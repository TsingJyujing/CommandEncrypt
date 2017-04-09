/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   aes.h
 * Author: yuanyifan
 *
 * Created on 2017年4月9日, 下午11:54
 */

#ifndef AES_H
#define AES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    extern int Nk;
    
    extern int Nr;
    
    extern int Nb;

    extern void key_expansion(uint8_t *key, uint8_t *w);

    extern void cipher(uint8_t *in, uint8_t *out, uint8_t *w);

    extern void inv_cipher(uint8_t *in, uint8_t *out, uint8_t *w);



#ifdef __cplusplus
}
#endif

#endif /* AES_H */

