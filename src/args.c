#include "args.h"
#include "ft_clib.h"
#include "ft_printf.h"

const char* const flags[end] = {
        [INFORM]    = "inform",
        [OUTFORM]   = "outform",
        [INFILE]    = "in",
        [OUTFILE]   = "out",
        [PASSIN]    = "passin",
        [PASSOUT]   = "passout",
        [TEXT]      = "text",
        [NOOUT]     = "noout",
        [MODULUS]   = "modulus",
        [CHECK]     = "check",
        [PUBIN]     = "pubin",
        [PUBOUT]    = "pubout",
        [HELP]      = "help"
};

static flag_e match_flag(char* s) {
    for (size_t i = 0; i < end; ++i) {
        if (i == HAS_ARG_FLAG) {
            continue;
        }
        if (ft_strcmp(flags[i], s) == 0) {
            return i;
        }
    }
    return end;
}

static void set_flag(args* settings, flag_e f, char* next_arg) {
    switch (f) {
        case INFORM:
            settings->inform = next_arg;
            break;
        case OUTFORM:
            settings->outform = next_arg;
            break;
        case INFILE:
            settings->infile = next_arg;
            break;
        case OUTFILE:
            settings->outfile = next_arg;
            break;
        case PASSIN:
            settings->passin = next_arg;
            break;
        case PASSOUT:
            settings->passout = next_arg;
            break;
        case TEXT:
            settings->text = true;
            break;
        case NOOUT:
            settings->noout = true;
            break;
        case MODULUS:
            settings->modulus = true;
            break;
        case CHECK:
            settings->check = true;
            break;
        case PUBIN:
            settings->pubin = true;
            break;
        case PUBOUT:
            settings->pubout = true;
            break;
        case HELP:
            settings->help = true;
            break;
        default:
            settings->error = true;
//            ERROR("unknown flag");
    }
}

args get_flags(int ac, char** av) {
    int i = 2;
    args ret;
    ft_bzero(&ret, sizeof(args));
    while (i < ac) {
        if (av[i][0] != '-') {
//            ERROR("expecting flag but found `%s`", av[i]);
            ret.error = true;
            return ret;
        }
        flag_e f = match_flag(av[i] + 1);
        if (f == end) {
            ret.error = true;
            return ret;
        }
        char* next_arg = NULL;
        if (f < HAS_ARG_FLAG) {
            if (ac - 1 < ++i) {
//                ERROR("expecting arg for flag `%s` but not supplied", av[i - 1]);
                ret.error = true;
                return ret;
            }
            next_arg = av[i];
        }
        set_flag(&ret, f, next_arg);
        ++i;
    }
    return ret;
}

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

void print_help() {
    const char* helpstr =
            "Usage: rsa [options]\n"
            "\n"
            "General options:\n"
            " -help               Display this summary\n"
            " -check              Verify key consistency\n"
            " -*                  Any supported cipher\n"
            "\n"
            "Input options:\n"
            " -in val             Input file\n"
            " -inform format      Input format (DER/PEM/P12/ENGINE)\n"
            " -pubin              Expect a public key in input file\n"
            " -passin val         Input file pass phrase source\n"
            "\n"
            "Output options:\n"
            " -out outfile        Output file\n"
            " -outform format     Output format, one of DER PEM PVK\n"
            " -pubout             Output a public key\n"
            " -passout val        Output file pass phrase source\n"
            " -noout              Don't print key out\n"
            " -text               Print the key in text\n"
            " -modulus            Print the RSA key modulus\n"
            ;
    ft_fprintf(stderr, "%s", helpstr);
}
