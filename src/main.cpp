// C
#include <stdio.h>

// Local
#include "arg.h"

int main(int argc, char** argv) {
    setenv(ARGP_HELP_FMT_EVAR, ARGP_HELP_FMT_FMT, 0);

    struct arg_struct parsed_args;
    argp_parse(&arg_params, argc, argv, 0, nullptr, &parsed_args);
    if (!parsed_args.valid) return 128;

    return 0;
}
