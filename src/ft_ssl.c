#include <stdio.h>
#include "ft_printf.h"
#include "ft_ssl.h"
#include "args.h"


int main(int ac, char** av) {
    if (ac < 2) {
        // TODO: make correct error
        ft_fprintf(stderr, "need arguments");
        return 1;
    }
    command cmd = get_command(av[1]);
    if (cmd == UNKNOWN) {
        ft_fprintf(stderr, "ft_ssl: Error: '%s' is an invalid command.\n", av[1]);
        return 0;
    }
    if (cmd == HELP) {

    }
    if (cmd == GENRSA) {
        genrsa();
    } else if (cmd == RSA) {
        args args = get_flags(ac, av);
        if (args.error == true) {
            ft_fprintf(stderr, "rs: Use -help for summary.\n");
            return 1;
        }
        if (args.help == true) {
            print_rsa_help();
            return 0;
        }
    } else {
        ft_fprintf(stderr, "not implemented yet\n");
    }
    return 0;
}
