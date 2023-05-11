//
// Created by Jonas Bennink bolt on 5/11/23.
//

#include "ft_ssl.h"
#include "ft_clib.h"
#include <string.h>
#include <unistd.h>

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

int main(int ac, char** av) {
    (void)ac;
    command cmd = get_command(av[1]);
    if (cmd == UNKNOWN) {
        print_error(av[1]);
        return 0;
    }
    if (cmd == GENRSA) {
        // starting here
    } else {
        write(STDOUT_FILENO, "not implemented yet\n", 20);
    }
    return 0;
}
