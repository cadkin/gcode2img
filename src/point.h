#ifndef POINT_H_
#define POINT_H_

/*
 * Point: simple container class for two doubles with a few niceties.
 */
class Point {
    public:
        // Default constructor.
        Point();
        // Constructor with two points.
        Point(const double& x, const double& y);

        // Get x.
        double x();
        // Get y.
        double y();

        // Set the x value.
        void setX(const double& x);
        // Set the y value.
        void setY(const double& y);

        // Returns true if lhs is considered less than rhs. To visually describe this, consider lhs as the
        // origin of a coordinate plane. LHS < RHS if RHS lies in quadrant 2, 3, or 4.
        bool operator<(const Point& rhs);
        // Similar to the above operator execept LHS > RHS if RHS lies in quadrant 1, 2, or 4.
        bool operator>(const Point& rhs);

        // Returns the distance to another point.
        double distance(const Point& other);

    private:
        double m_x;
        double m_y;
};

#endif // POINT_H_
