#ifndef SEGMENT_H_
#define SEGMENT_H_

// C++
#include <string>

// Local
#include "point.h"

/*
 * Segment: simple class to contain path geometry and write the appropriate JGraph polygon commands.
 */
class Segment {
    public:
        // Constructor with two points.
        Segment(const Point& start, const Point& end);

        // Returns the length of this segment.
        double length();

        // Returns a string with the corresponding polygon for this segment. Requires a defined width.
        std::string writePoly(const float& width);

    private:
        Point m_start;
        Point m_end;
};

#endif // SEGMENT_H_
