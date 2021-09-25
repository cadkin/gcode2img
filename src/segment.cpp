#include "segment.h"

// C
#include <math.h>

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

std::string Segment::writePoly(const float& width) {
    std::string ret = "newline poly pcfill 1 0 0 color 1 0 0 ";

    if (m_start.x() == m_end.x() && m_start.y() == m_end.y()) return std::string();

    double dx = m_end.x() - m_start.x();
    double dy = m_end.y() - m_start.y();

    // Normalize vector (dx, dy)
    double norm = sqrt((dx * dx) + (dy * dy));
    dx /= norm;
    dy /= norm;

    // Points will act as vectors right normal and left normal.
    Point rn(-dy * width, dx * width);
    Point ln(dy * width, -dx * width);

    Point rect[4];

    rect[0] = m_start + rn;
    rect[1] = m_start + ln;
    rect[2] = m_end   + ln;
    rect[3] = m_end   + rn;

    ret += "pts ";

    for (int i = 0; i < 4; i++) {
        ret += std::to_string(rect[i].x()) + " " + std::to_string(rect[i].y()) + " ";
    }

    ret += "\n";

    return ret;
}
