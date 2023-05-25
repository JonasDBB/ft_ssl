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

uint64_t get_random_uint64();
bool miller_rabin_is_prime(uint64_t potential_prime);

#endif //FT_SSL_FT_SSL_H
