#include <stdbool.h>
#include "ft_ssl.h"
#include "ft_printf.h"

#define MILLER_RABIN_PRECISION 5

uint64_t addmod(uint64_t x, uint64_t y, uint64_t mod) {
    x = x % mod;
    y = y % mod;
    if (x >= mod - y) {
        return x - (mod - y);
    }
    return x + y;
}

uint64_t multmod(uint64_t x, uint64_t y, uint64_t mod) {
    uint64_t ret = 0;
    for (; y > 0; y >>= 1) {
        if (y % 2 == 1) {
            ret = addmod(ret, x, mod);
        }
        x = addmod(x, x, mod);
    }
    return ret;
}

uint64_t powmod(uint64_t x, uint64_t y, uint64_t mod) {
    uint64_t ret = 1;
    x = x % mod;
    for (; y > 0; y >>= 1) {
        if (y % 2 == 1) {
            ret = multmod(ret, x, mod);
        }
        x = multmod(x, x, mod);
    }
    return ret;
}

bool check(uint64_t potential_prime, uint64_t odd_nr) {
    uint64_t random_uint64 = (get_random_uint64() % (potential_prime - 4)) + 2;
    uint64_t x = powmod(random_uint64, odd_nr, potential_prime);
    if (x == 1 || x == potential_prime - 1) {
        return true;
    }
    while (odd_nr != potential_prime - 1) {
        x = (x * x) % potential_prime;
        odd_nr *= 2;
        if (x == 1) {
            return false;
        }
        if (x == potential_prime - 1) {
            return true;
        }
    }
    return false;
}

bool miller_rabin_is_prime(uint64_t potential_prime) {
    if (potential_prime == 2 || potential_prime == 3) {
        return true;
    } else if (potential_prime == 0 || potential_prime == 1 || potential_prime % 2 == 0) {
        return false;
    }

    uint64_t odd_nr = potential_prime - 1;
    while (odd_nr % 2 == 0) {
        odd_nr /= 2;
    }

    for (int i = 0; i < MILLER_RABIN_PRECISION; ++i) {
        if (!check(potential_prime, odd_nr)) {
            return false;
        }
        ft_printf("+");
    }
    return true;
}
