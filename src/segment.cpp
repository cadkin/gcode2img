#include "segment.h"

Segment::Segment(const Point& start, const Point& end) {
    m_start = start;
    m_end   = end;
}

double Segment::length() {
    return m_start.distance(m_end);
}

std::string writePoly(const float& width) {
    return std::string();
}
