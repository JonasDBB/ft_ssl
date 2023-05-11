//
// Created by Jonas Bennink bolt on 5/11/23.
//

#ifndef FT_SSL_FT_SSL_H
#define FT_SSL_FT_SSL_H

#include <stdbool.h>

typedef enum {
    GENRSA,
    RSA,
    RSAUTL,
    UNKNOWN
} command;

float prime_probability(unsigned long int n);

#endif //FT_SSL_FT_SSL_H
