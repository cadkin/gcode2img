#ifndef SEGMENT_H_
#define SEGMENT_H_

// C++
#include <string>

// Local
#include "point.h"
#include "cura.h"

/*
 * Segment: simple class to contain path geometry and write the appropriate JGraph polygon commands.
 */
class Segment {
    public:
        // Constructor with two points.
        Segment(const Point& start, const Point& end);

        // Set the type of region this segment belongs to.
        void setType(CuraRegion type);

        // Returns segment start.
        Point start();
        // Returns segment end.
        Point end();
        // Returns the length of this segment.
        double length();

        // Returns a string with the corresponding polygon for this segment. Requires a defined width.
        std::string writePoly(const float& width);

    private:
        Point m_start;
        Point m_end;

        CuraRegion m_type;
};

#endif // SEGMENT_H_
