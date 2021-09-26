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

static std::map<CuraRegion, std::string> CuraRegionColorString = {
    {CuraRegion::kFill,              "0.1 0.7 0.2"},
    {CuraRegion::kSkin,              "0.8 0.1 0.8"},
    {CuraRegion::kSupport,           "0.8 0.3 0.1"},
    {CuraRegion::kSupportInterface,  "0.8 0.5 0.1"},
    {CuraRegion::kWallInner,         "0.1 0.3 0.8"},
    {CuraRegion::kWallOuter,         "0.1 0.8 0.7"}
};

#endif // CURA_H_
