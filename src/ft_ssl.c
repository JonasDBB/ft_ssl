//
// Created by Jonas Bennink bolt on 5/11/23.
//

#include <stdio.h>
#include "ft_printf.h"
#include "ft_ssl.h"
#include "ft_clib.h"

command get_command(const char* str) {
    if (ft_strcmp(str, "genrsa") == 0) {
        return GENRSA;
    } else if (ft_strcmp(str, "rsa") == 0) {
        return RSA;
    } else if (ft_strcmp(str, "rsautl") == 0) {
        return RSAUTL;
    }
    return UNKNOWN;
}

int main(int ac, char** av) {
    if (ac < 2) {
        // TODO: make correct error
        ft_fprintf(stderr, "need arguments");
        return 1;
    }
    command cmd = get_command(av[1]);
    if (cmd == UNKNOWN) {
        ft_fprintf(stderr, "ft_ssl: Error: '%s' is an invalid command.\n", av[0]);
        return 0;
    }
    if (cmd == GENRSA) {
        genrsa();
    } else {
        ft_fprintf(stderr, "not implemented yet\n");
    }
    return 0;
}
