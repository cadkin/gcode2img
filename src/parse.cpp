#include "parse.h"

// Local
#include "cura.h"
#include "message.h"
#include "point.h"
#include "segment.h"

int _to_int(std::string& str) {
    char* endptr;
    int ret;

    ret = strtol(str.c_str(), &endptr, 10);

    if ((ret == 0 && errno != 0) || (*endptr != '\0')) {
        pquit(64, "Unable to read int from GCode file.\n");
    }

    return ret;
}

double _to_double(std::string& str) {
    char* endptr;
    double ret;

    ret = strtod(str.c_str(), &endptr);

    if ((ret == 0 && errno != 0) || (*endptr != '\0')) {
        pquit(128, "Unable to read float from GCode file.\n");
    }

    return ret;
}

std::vector<std::string> _tokenize(const std::string& str, const char delim) {
    std::vector<std::string> ret;

    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
        end = str.find(delim, start);
        ret.push_back(str.substr(start, end - start));
    }

    return ret;
}

std::vector<std::vector<Segment>> parse_gcode(FILE* fptr, const std::set<int>& layers) {
    std::vector<std::vector<Segment>> ret;

    struct {
        CuraRegion region;
        Point last_point;
        int layer = -1;
        bool write = false;
    } state;

    for (;;) {
        char* buf = NULL;
        size_t buf_len = 0;

        ssize_t read = getline(&buf, &buf_len, fptr);
        if (read < 0) break;
        buf[read - 1] = '\0';

        //printf("%s", buf);
        std::string line(buf);
        free(buf);

        // TODO: Better setup for parsing.

        // Check for keywords in comments.

        if (line.rfind(CURA_LAYER_COUNT, 0) == 0) {
            std::string layerc_str = line.substr(line.find(":") + 1);
            int layerc = _to_int(layerc_str);

            if (ret.size()) pquit(64, "Quitting: multiple layer counts in GCode file.\n");
            ret.resize(layerc);

            //printf("Matches LAYERCOUNT: %d\n", layerc);
            continue;
        }
        if (line.rfind(CURA_TYPE, 0) == 0) {
            std::string type = line.substr(line.find(":") + 1);
            state.region = CuraRegionTypeString[type];

            //printf("Matches TYPE: %s\n", type.c_str());
            continue;
        }
        if (line.rfind(CURA_LAYER, 0) == 0) {
            std::string layer_str = line.substr(line.find(":") + 1);
            int layer = _to_int(layer_str);

            state.layer = layer;
            state.write = (layers.count(layer) || layers.empty()) ? true : false;

            if (!state.write) state.last_point = Point();

            //printf("Matches LAYER: %d\n", layer);
            continue;
        }

        // Read G1/G0 (extrude/travel) commands.
        if (!state.write) continue;

        auto cmd = _tokenize(line, ' ');
        if (!(cmd[0] == "G1" || cmd[0] == "G0")) continue;

        std::string x_str;
        std::string y_str;

        for (auto& token : cmd) {
            if (token.rfind("X", 0) == 0) x_str = token.substr(1);
            if (token.rfind("Y", 0) == 0) y_str = token.substr(1);
        }

        if (x_str.empty() || y_str.empty()) continue;

        //printf("(X, Y) = (%s, %s)\n", x_str.c_str(), y_str.c_str());

        double x = _to_double(x_str);
        double y = _to_double(y_str);

        Point new_point(x, y);
        if (!(state.last_point.x() == 0 && state.last_point.y() == 0)) {
            Segment seg(state.last_point, new_point);
            seg.setType(state.region);

            // We have a generated segment now. Put it in the return.
            ret[state.layer].push_back(seg);
        }

        state.last_point = new_point;
    }

    return ret;
}
