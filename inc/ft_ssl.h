//
// Created by Jonas Bennink bolt on 5/11/23.
//

#ifndef FT_SSL_FT_SSL_H
#define FT_SSL_FT_SSL_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    GENRSA,
    RSA,
    RSAUTL,
    UNKNOWN
} command;

void genrsa();

uint64_t get_random_uint64();

bool miller_rabin_is_prime(uint64_t potential_prime);

char* base64_encode_create(const unsigned char* input, size_t len);
unsigned char* base64_decode_create(const char* input);

#endif //FT_SSL_FT_SSL_H
