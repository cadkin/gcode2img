#ifndef PARSE_H_
#define PARSE_H_

// C++
#include <vector>
#include <set>

// Local
#include "segment.h"

// Generates a set of segments from a GCode file.
// ARGS: fptr       - File to read from.
//       layers     - Set of layers to include. If empty, all layers are included.
std::vector<std::vector<Segment>> parse_gcode(FILE* fptr, const std::set<int>& layers = std::set<int>());

#endif // PARSE_H_
