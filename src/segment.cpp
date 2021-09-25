#include "segment.h"

Segment::Segment(const Point& start, const Point& end) {
    m_start = start;
    m_end   = end;
}

void Segment::setType(CuraRegion type) {
    m_type = type;
}

Point Segment::start() {
    return m_start;
}

Point Segment::end() {
    return m_end;
}

double Segment::length() {
    return m_start.distance(m_end);
}

std::string writePoly(const float& width) {
    return std::string();
}
