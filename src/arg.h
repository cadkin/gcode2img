#ifndef ARG_H
#define ARG_H

// C
#include <argp.h>

// C++
#include <string>
#include <set>

// The default 80 cols of argp is a bit limiting. If user hasn't setup their own
// ARGP_HELP_FMT variable, change it to be wider. Will not replace if already set.
#define ARGP_HELP_FMT_EVAR "ARGP_HELP_FMT"
#define ARGP_HELP_FMT_FMT  "rmargin=180, opt-doc-col=40, no-dup-args-note"

const char prog_doc[] = "Simple program to generate jgraph files from a provided GCode file. Currently accepts GCode in the Marlin syntax. Use '-' to read from stdin.";
static char args_doc[] = "[GCODE_FILE]";

struct arg_struct {
    bool all_layers = false;
    bool generate_img = false;
    std::set<int> layers;
    float bead_width = 0;
    std::string dir;
    FILE* in  = nullptr;
    FILE* out = nullptr;

    bool valid = false;
};

const struct argp_option arg_options[] = {
    {"all-layers",      'a', nullptr,       0,  "Generate jgraph files for all layers in the GCode",                                                                0},
    {"single-layer",    'l', "LAYER",       0,  "Generate jgraph files for single layers in the GCode. Can be specified multiple times",                            0},
    {"bead-width",      'w', "WIDTH",       0,  "Width of the segment visualization in the same units as the GCode",                                                0},
    {"generate-images", 'i', nullptr,       0,  "Runs 'cat [file] | ./jgraph -P | ps2pdf - | convert -density 300 - -quality 100 [file].png' for every output",     0},
    {"output-dir",      'd', "PATH",        0,  "Directory to output files. Defaults to current directory",                                                         0},
    {"stdout",          's', nullptr,       0,  "Output jgraph specification to stdout",                                                                            0},
    { 0 }
};

error_t parse_opt(int key, char* arg, struct argp_state* state);

const struct argp arg_params = {arg_options, &parse_opt, args_doc, prog_doc};

#endif // ARG_H
