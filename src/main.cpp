// C
#include <stdio.h>

// Linux
#include <sys/stat.h>

// Local
#include "arg.h"
#include "message.h"
#include "parse.h"

int main(int argc, char** argv) {
    setenv(ARGP_HELP_FMT_EVAR, ARGP_HELP_FMT_FMT, 0);

    struct arg_struct parsed_args;
    argp_parse(&arg_params, argc, argv, 0, nullptr, &parsed_args);
    if (!parsed_args.valid) return 128;

    //printf("in: %d, out: %p\n", fileno(parsed_args.in), parsed_args.out);

    // Augement args.
    if (parsed_args.all_layers) parsed_args.layers.clear();
    if (parsed_args.dir.empty()) parsed_args.dir = "./";

    struct stat stat_buf;

    if (parsed_args.out == nullptr) {
        if (stat(parsed_args.dir.c_str(), &stat_buf) != 0) pquit(128, "Output directory '%s' cannot be accessed.\n", parsed_args.dir);
        else if (!(stat_buf.st_mode & S_IFDIR)) pquit(128, "Output directory '%s' is not a directory.\n", parsed_args.dir);
    }

    // Generate segments
    auto gcode_segments = parse_gcode(parsed_args.in, parsed_args.layers);

    // Write to the output.
    int layer_nr = 0;
    for (auto& layer : gcode_segments) {
        if (layer.empty()) {
            layer_nr++;
            continue;
        }

        FILE* fptr;
        if (parsed_args.out) fptr = parsed_args.out;
        else {
            char name[10];
            sprintf(name, "%03d.jgr", layer_nr);

            std::string file = parsed_args.dir + "/" + std::string(name);

            fptr = fopen(file.c_str(), "w+");
            if (!fptr) {
                pquit(128, "Unable to open output file '%s'.\n", file.c_str());
            }
        }

        fprintf(fptr, "newgraph\n\nxaxis nodraw\nyaxis nodraw\n");
        for (auto& seg : layer) {
           fprintf(fptr, "(* Segment: (%f, %f) -> (%f, %f) *)\n", seg.start().x(), seg.start().y(), seg.end().x(), seg.end().y());

           fprintf(fptr, "%s\n", seg.writePoly(parsed_args.bead_width).c_str());
        }


        if (!parsed_args.out) fclose(fptr);
        layer_nr++;
    }

    return 0;
}
