//
// Created by Jonas Bennink bolt on 5/25/23.
//

#include <stdio.h>
#include "ft_ssl.h"
#include "ft_clib.h"

static uint64_t get_prime() {
    uint64_t ret;
    while (1) {
        ret = get_random_uint64();
        printf(".");
        if (miller_rabin_is_prime(ret) == false) {
            continue;
        }
        break;
    }
    printf("\n");
    return ret;
}

uint64_t greatest_common_denominator(uint64_t a, uint64_t b) {
    if (a == 0) {
        return b;
    }
    return greatest_common_denominator(b % a, a);
}

void genrsa() {
    uint64_t p = get_prime();
    uint64_t q = get_prime();
    LOG("p   %llu", p);
    LOG("q   %llu", q);

    uint64_t n = p * q;
    LOG("n   %llu", n);

    uint64_t phi = (p - 1) * (q - 1);
    LOG("phi %llu", phi);

    uint64_t lambda_n = ((p - 1) * (q - 1)) / greatest_common_denominator(p - 1, q - 1);
    LOG("lcm %llu", lambda_n);

    // encryption key part
    uint64_t e = 65537;

    // decryption key part
    uint64_t d;
//    d === e^-1, d is modular multiplicative inverse of e modulo lambda_n


}