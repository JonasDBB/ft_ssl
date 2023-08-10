#ifndef FT_SSL_ARGS_H
#define FT_SSL_ARGS_H

#include <stdbool.h>

typedef enum {
    GENRSA,
    RSA,
    RSAUTL,
    UNKNOWN
} command;

typedef enum {
    INFORM, // + arg
    OUTFORM, // + arg
    INFILE, // + arg
    OUTFILE, // + arg
    PASSIN, // + arg
    PASSOUT, // + arg
    HAS_ARG_FLAG,
    TEXT,
    NOOUT,
    MODULUS,
    CHECK,
    PUBIN,
    PUBOUT,
    HELP,
    end
} flag_e;

typedef struct {
    char* inform;
    char* outform;
    char* infile;
    char* outfile;
    char* passin;
    char* passout;
    bool text;
    bool noout;
    bool modulus;
    bool check;
    bool pubin;
    bool pubout;
    bool help;
    bool error;
} args;

command get_command(const char* str);
args get_flags(int ac, char** av);
void print_help();

#endif
