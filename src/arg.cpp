#include "arg.h"

// Linux
#include <sys/stat.h>

// Local
#include "message.h"

error_t parse_opt(int key, char* arg, argp_state* state) {
    struct arg_struct* as = (struct arg_struct*)state->input;

    switch (key) {
        case 'a': {
            as->all_layers = true;

            if (!as->layers.empty()) {
                fprintf(stderr, "Warning: the all flag overrides any per-layer selections.\n");
            }

            break;
        }
        case 'l': {
            char* endptr;
            int layer = strtol(arg, &endptr, 10);

            if ((layer == 0 && errno != 0) || (*endptr != '\0') || (layer < 0)) {
                pquit(128, "Unable to read interger for layer.\n");
            }

            if (as->all_layers) {
                fprintf(stderr, "Warning: the all flag overrides any per-layer selections.\n");
            }

            as->layers.insert(layer);

            break;
        }
        case 'w': {
            char* endptr;
            float width = strtof(arg, &endptr);

            if ((width == 0 && errno != 0) || (*endptr != '\0') || (width < 0)) {
                pquit(128, "Unable to read float for width.\n");
            }

            as->bead_width = width;

            break;
        }
        case 'i': {
            as->generate_img = true;

            break;
        }
        case 'd': {
            if (!as->dir.empty()) {
                pquit(128, "Output directory was specified more than once, quitting.\n");
            }


            struct stat stat_buf;

            if (stat(arg, &stat_buf) != 0) {
                pquit(128, "Output directory '%s' cannot be accessed.\n", arg);
            }
            else if (!(stat_buf.st_mode & S_IFDIR)) {
                pquit(128, "Output directory '%s' is not a directory.\n", arg);
            }

            as->dir = std::string(arg);

            break;
        }
        case 's': {
            as->out = stdout;

            break;
        }
        case ARGP_KEY_ARG: {
            if (state->arg_num > 1) argp_usage(state);
            if (as->in) argp_usage(state);

            std::string sarg(arg);
            if (sarg == "-") {
                as->in = stdin;
                break;
            }

            FILE* fptr = fopen(arg, "r");
            if (!fptr) {
                pquit(128, "Unable to open input GCode file '%s'.\n", arg);
            }

            as->in = fptr;

            break;
        }
        case ARGP_KEY_END: {
            if (state->arg_num < 1) argp_usage(state);
            else as->valid = true;

            break;
        }
        default: {
            return ARGP_ERR_UNKNOWN;
        }
    }

    return 0;
}
