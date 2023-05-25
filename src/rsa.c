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

void genrsa() {
    uint64_t prime1 = get_prime();
    uint64_t prime2 = get_prime();
    LOG("prime 1 = %llu", prime1);
    LOG("prime 2 = %llu", prime2);
}