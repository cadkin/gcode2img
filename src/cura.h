#ifndef CURA_H_
#define CURA_H_

// C++
#include <map>

#define CURA_TYPE           ";TYPE:"
#define CURA_LAYER          ";LAYER:"
#define CURA_LAYER_COUNT    ";LAYER_COUNT:"

enum class CuraRegion {
    kFill,
    kSkin,
    kSupport,
    kSupportInterface,
    kWallInner,
    kWallOuter
};

static std::map<std::string, CuraRegion> CuraRegionTypeString = {
    {"FILL",                CuraRegion::kFill},
    {"SKIN",                CuraRegion::kSkin},
    {"SUPPORT",             CuraRegion::kSupport},
    {"SUPPORT-INTERFACE",   CuraRegion::kSupportInterface},
    {"WALL-INNER",          CuraRegion::kWallInner},
    {"WALL-OUTER",          CuraRegion::kWallOuter}
};

#endif // CURA_H_
