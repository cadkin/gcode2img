// C
#include <stdio.h>

// Local
#include "arg.h"
#include "parse.h"

int main(int argc, char** argv) {
    setenv(ARGP_HELP_FMT_EVAR, ARGP_HELP_FMT_FMT, 0);

    struct arg_struct parsed_args;
    argp_parse(&arg_params, argc, argv, 0, nullptr, &parsed_args);
    if (!parsed_args.valid) return 128;

    //printf("in: %d, out: %p\n", fileno(parsed_args.in), parsed_args.out);

    if (parsed_args.all_layers) parsed_args.layers.clear();
    auto gcode_segments = parse_gcode(parsed_args.in, parsed_args.layers);

    printf("newgraph\n\n");
    for (auto& layer : gcode_segments) {
        for (auto& seg : layer) {
           printf("(* Segment: (%f, %f) -> (%f, %f) *)\n", seg.start().x(), seg.start().y(), seg.end().x(), seg.end().y());

           printf("%s\n", seg.writePoly(parsed_args.bead_width).c_str());
        }
    }


    return 0;
}
