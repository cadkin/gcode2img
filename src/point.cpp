#include "point.h"

// C
#include <math.h>

Point::Point() {
    m_x = 0;
    m_y = 0;
}

Point::Point(const double& x, const double& y) {
    m_x = x;
    m_y = y;
}

double Point::x() {
    return m_x;
}

double Point::y() {
    return m_y;
}

void Point::setX(const double& x) {
    m_x = x;
}

void Point::setY(const double& y) {
    m_y = y;
}

bool Point::operator<(const Point& rhs) {
    if (m_x < rhs.m_x || m_y < rhs.m_y) return true;

    return false;
}

bool Point::operator>(const Point& rhs) {
    if (m_x > rhs.m_x || m_y > rhs.m_y) return true;

    return false;
}

double Point::distance(const Point& other) {
    return sqrt(pow(other.m_x - m_x, 2) + pow(other.m_y - m_y, 2));
}
