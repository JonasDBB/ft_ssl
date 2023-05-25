//
// Created by Jonas Bennink bolt on 5/11/23.
//

#include <string.h>
#include <stdio.h>
#include "ft_ssl.h"

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

int main(int ac, char** av) {
    (void)ac;
    command cmd = get_command(av[1]);
    if (cmd == UNKNOWN) {
        fprintf(stderr, "ft_ssl: Error: '%s' is an invalid command.\n", av[0]);
        return 0;
    }
    if (cmd == GENRSA) {
        genrsa();
    } else {
        fprintf(stderr, "not implemented yet\n");
    }
    return 0;
}
