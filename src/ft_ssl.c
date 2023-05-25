//
// Created by Jonas Bennink bolt on 5/11/23.
//

#include "ft_ssl.h"
#include "ft_clib.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

command get_command(const char* str) {
    if (strcmp(str, "genrsa") == 0) {
        return GENRSA;
    } else if (strcmp(str, "rsa") == 0) {
        return RSA;
    } else if (strcmp(str, "rsautl") == 0) {
        return RSAUTL;
    }
    return UNKNOWN;
}

void print_error(const char* str) {
    write(STDERR_FILENO, "ft_ssl: Error: '", 16);
    write(STDERR_FILENO, str, ft_strlen(str));
    write(STDERR_FILENO, "' is an invalid command.\n", 25);
}

uint64_t get_random_uint64() {
    uint64_t ret;
    int devrandom = open("/dev/urandom", O_RDONLY);
    if (devrandom == -1) {
        ERROR("opening /dev/random failed. errno is %s", errno_name(errno));
        // TODO: exit gracefully
        return 0;
    }
    if (read(devrandom, &ret, 8) != 8) {
        close(devrandom);
        ERROR("failed reading 8 random bytes. errno is %s", errno_name(errno));
        // TODO: exit gracefully
        return 0;
    }
    close(devrandom);
    return ret;
}


int main(int ac, char** av) {
    (void)ac;
    command cmd = get_command(av[1]);
    if (cmd == UNKNOWN) {
        print_error(av[1]);
        return 0;
    }
    if (cmd == GENRSA) {
        // get random uint64
        uint64_t prime1;
        uint64_t prime2;
        while (1) {
            prime1 = get_random_uint64();
            write(1, ".", 1);
            if (miller_rabin_is_prime(prime1) == false) {
                continue;
            }
            write(1, "\n", 1);
            LOG("found %llu", prime1);
            break;
        }
        write(1, "\n", 1);
        while (1) {
            prime2 = get_random_uint64();
            write(1, ".", 1);
            if (miller_rabin_is_prime(prime2) == false) {
                continue;
            }
            write(1, "\n", 1);
            LOG("found %llu", prime2);
            break;
        }
    } else {
        write(STDOUT_FILENO, "not implemented yet\n", 20);
    }
    return 0;
}
