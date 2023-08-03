//
// Created by Jonas Bennink bolt on 5/25/23.
//

#include "ft_ssl.h"
#include "ft_clib.h"
#include "ft_printf.h"

static uint32_t get_prime() {
    uint32_t ret;
    while (1) {
        ret = get_random_uint64();
        ft_printf(".");
        if (miller_rabin_is_prime(ret) == false) {
            continue;
        }
        break;
    }
    ft_printf("\n");
    return ret;
}

uint64_t greatest_common_denominator(uint64_t a, uint64_t b) {
    if (a == 0) {
        return b;
    }
    return greatest_common_denominator(b % a, a);
}

int64_t extended_euclidean(int64_t a, int64_t b, int64_t* x, int64_t* y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int64_t x_tmp;
    int64_t y_tmp;
    int64_t ret = extended_euclidean(b % a, a, &x_tmp, &y_tmp);
    *x = y_tmp - (b / a) * x_tmp;
    *y = x_tmp;
    return ret;
}

int64_t modular_multiplicative_inverse(int64_t a, int64_t m) {
    int64_t x, y;

    int64_t g = extended_euclidean(a, m, &x, &y);
    if (g != 1) {
        WARN("no inverse exists");
        return 0;
    }
    return (x % m + m) % m;
}

void genrsa() {
    uint64_t p = get_prime();
    uint64_t q = get_prime();
//    LOG("p   %llu", p);
//    LOG("q   %llu", q);

//    uint64_t n = p * q;

    uint64_t lambda_n = ((p - 1) * (q - 1)) / greatest_common_denominator(p - 1, q - 1);

    // encryption key part
    uint64_t e = 65537;

    // decryption key part
    int64_t d = modular_multiplicative_inverse((int64_t)e, (int64_t)lambda_n);
    LOG("d   %llu", d);
}