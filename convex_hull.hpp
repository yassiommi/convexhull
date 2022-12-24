/**
 * @file convex_hull.hpp
 * @author Yassaman Ommi (ommiy@mcmaster.ca)
 * @brief A program to find the convex hull of a given set of point
 */

#ifndef convex_hull_h
#define convex_hull_h

#include <iostream>
#include <vector>
#include <limits>
#include <math.h>

using namespace std;

double INF_DOUBLE = std::numeric_limits<double>::infinity();

/**
 * @brief A class to store a 2d point data and perform operations on it
 */
class Point {
    private:
    /**
     * @brief The points' coordinates in 2d
     */
        double x, y;
/**
 * @brief Set the coordinates object
 * 
 * @param X first coordinate of the point
 * @param Y second coordinate of the point
 */
        void set_coordinates(double X, double Y) {
            x = X;
            y = Y;
        }

/**
 * @brief Set the x value
 * 
 * @param X 
 */
        void set_x(double X) {
            x = X;
        }
/**
 * @brief Set the y value
 * 
 * @param Y 
 */
        void set_y(double Y) {
            y = Y;
        }
    
    public:
/**
 * @brief Construct a new Point object without given input
 * initiates with (0, 0)
 * 
 */
        Point() {
            x = 0;
            y = 0;
        }

/**
 * @brief Construct a new Point object with given input
 * 
 * @param X 
 * @param Y 
 */
        Point(double X, double Y) {
            set_x(X);
            set_y(Y);
        }
/**
 * @brief Construct a new Point object
 * 
 * @param other 
 */
        Point(const Point& other) {
            x = other.x;
            y = other.y;
        }

/**
 * @brief Get the x variable's value
 * 
 * @return x's value
 */
        double get_x(){
            return x;
        }
/**
 * @brief Get the y variable's value
 * 
 * @return y's value  
 */
        double get_y(){
            return y;
        }

/**
 * @brief Calculates the point's distance from origin 
 * 
 * @return distance 
 */
        double origin_distance(){
            float x = get_x(), y = get_y();
            return sqrt(x * x + y * y);
        }

/**
 * @brief Calculates the distance between two points
 * 
 * @param b The point to calculate the distance from
 * @return distance between two points
 */
        double distance(Point b) {
            float ax = get_x(), ay = get_y(), bx = b.get_x(), by = b.get_y();
            return sqrt(pow(bx - ax,2) + pow(by - ay, 2));
        }

/**
 * @brief Determines the orientation of three ordered points using slope
 * 
 * @param b The second point
 * @param c The third point
 * @return 0 if the lines are colinear, -1 if they are clockwise and +1 if counterclockwise
 */
        int orientation(Point b, Point c) {
            int check = (b.get_y() - get_y()) * (c.get_x() - b.get_x()) - (b.get_x() - get_x()) * (c.get_y() - b.get_y());
            if (check == 0)
                  return 0;
                  return (check > 0) ? -1 : 1;
        }
/**
 * @brief Overloaded == operator for Point class
 * 
 * @param p The second point to check the first one with
 * @return true if two points are the same
 * @return false otherwise
 */
        bool operator==(Point p) {
            return (p.get_x() == get_x()) && (p.get_y() == get_y());
        }
/**
 * @brief Overloaded != operator for Point class
 * 
 * @param p The second point to check the first one with
 * @return true if two points are not the same
 * @return false otherwise
 */
        bool operator!=(Point p) {
            return !(p == *this);
        }

        friend std::ostream & operator << (ostream &out, Point p);
};
/**
 * @brief Overloaded extraction operator for Point class
 * 
 * @param out 
 * @param p The point to get printed
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &out, Point p) {
    out<<"("<<p.x<<", "<<p.y<<")";
    return out;
}

/**
 * @brief A class to store a line with its start and end point
 */
class Line {
    private:
    /**
     * @brief start and end points of the line
     */
        Point start, end;
/**
 * @brief Set the start point of the line
 * 
 * @param start_point given start point
 */
        void set_start(Point start_point) {
            start = start_point;
        }
/**
 * @brief Set the end point of the line
 * 
 * @param end_point given end point 
 */
        void set_end(Point end_point) {
            end = end_point;
        }
    
    public:
/**
 * @brief Construct a new Line object with given start and end points
 * 
 * @param start the first point of the line
 * @param end  the end point of line 
 */
        Line(Point start, Point end) {
            set_start(start);
            set_end(end);
        }
/**
 * @brief A function to reverse the start and end point of a line
 * 
 * @return reversed line
 */
        Line reverse() {
            return Line(end, start);
        }
/**
 * @brief Get the start point of the line
 * 
 * @return Start point 
 */
        Point get_start() { return start; }

/**
 * @brief Get the end point of the line
 * 
 * @return End Point 
 */
        Point get_end() { return end; }
/**
 * @brief A function to calculate the slop of a line
 * 
 * @return the line's slope
 */
        double slope() {
            return (end.get_y() - start.get_y()) / (end.get_x() - start.get_x());
        }
/**
 * @brief A function to calculate the intersection of the line with the y-axis
 * 
 * @return intersection of the line with the y-axis
 */
        double intersection() {
            return end.get_y() - slope() * start.get_y();
        }
/**
 * @brief A function to calculate the distance of a point from the line
 * 
 * @param p given point
 * @return distance of the point from the line
 */
        double distance(Point p) {
            double m = slope(), b = intersection();
            return abs(m * p.get_x() - p.get_y() + b) / sqrt(1 + m * m);
        }
/**
 * @brief A function to determine if a given point is on the left of a line or not
 * 
 * @param p 
 * @return true if the point is on the left of the line
 * @return false otherwise 
 */
        bool is_on_left(Point p) {
            double d = (p.get_x() - start.get_x()) * (end.get_y() - start.get_y()) - (p.get_y() - start.get_y()) * (end.get_x() - start.get_x());
            return d > 0;
        }
};

/**
 * @brief A function that uses the gift-wrapping algorithm to find the points on the convex hull of a given set of points 
 * 
 * @param points a vector containing the input points
 * @return vector<Point> a vector containing the set of the points on the convex hull
 */
vector<Point> gift_wrapping(vector<Point> points) {
    vector<Point> hull;
    Point start = points[0], previous, current, next;
    double max_slope = -INF_DOUBLE, max_dot = -1;
    
    for (vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
        Point point = (Point) *it;
        if (point.get_x() < start.get_x() || (point.get_x() == start.get_x() && point.get_y() < start.get_y())) {
            start = point;
        }
    }

    hull.push_back(start);
    previous = start;

    for (vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
        Point point = (Point) *it;
        if (point == previous) {
            continue;
        }
        double slope = (point.get_y() - previous.get_y()) / abs(point.get_x() - previous.get_x());
        if (slope > max_slope) {
            max_slope = slope;
            current = point;
        }
    }

    while (current != *hull.begin()) {
        max_dot = -1;
        for (vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
            Point point = (Point) *it;
            if (point == current) {
                continue;
            }
            double dot_product = (current.get_x() - previous.get_x()) * (point.get_x() - current.get_x())
                + (current.get_y() - previous.get_y()) * (point.get_y() - current.get_y());
            dot_product /= current.distance(previous) * current.distance(point);
            if (dot_product > max_dot) {
                max_dot = dot_product;
                next = point;
            }
        }
        previous = current;
        current = next;
        hull.push_back(current);
    }
    
    return hull;
}

/**
 * @brief A helper function for the Quickhull algorithm that removes the points that are on the right of the given line and chooses the point with the largest distance to the line
 * 
 * @param points the set of remaining points
 * @param base the line to use for eliminating and choosing the points 
 * @return vector<Point> 
 */
vector<Point> find_hull(vector<Point> points, Line base) {
    if (points.empty()) {
        return points;
    }
    vector<Point> left_points;
    for (vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
        Point point = (Point) *it;
        if (point == base.get_start() || point == base.get_end()) {
            continue;
        }
        if (base.is_on_left(point)) {
            left_points.push_back(point);
        }
    }

    double max_dist = -INF_DOUBLE;
    Point farthest;
    for (vector<Point>::iterator it = left_points.begin(); it != left_points.end(); it++) {
        Point point = (Point) *it;
        if (base.distance(point) > max_dist) {
            farthest = point;
            max_dist = base.distance(point);
        }
    }

    vector<Point> outside_triangle;
    Line first_line = Line(base.get_start(), farthest), second_line = Line(farthest, base.get_end());

    for (vector<Point>::iterator it = left_points.begin(); it != left_points.end(); it++) {
        Point point = (Point) *it;
        if (point == farthest) {
            continue;
        }
        if (first_line.is_on_left(point) || second_line.is_on_left(point)) {
            outside_triangle.push_back(point);
        }
    }

    vector<Point> first_hull = find_hull(outside_triangle, first_line);
    vector<Point> second_hull = find_hull(outside_triangle, second_line);
    vector<Point> merged_hull;
    merged_hull.push_back(farthest);
    merged_hull.insert(merged_hull.end(), first_hull.begin(), first_hull.end());
    merged_hull.insert(merged_hull.end(), second_hull.begin(), second_hull.end());
    
    return merged_hull;
}

/**
 * @brief A function that uses the Quickhull algorithm to find the points on the convex hull of a given set of points 
 * 
 * @param points a vector containing the input points
 * @return vector<Point> a vector containing the set of the points on the convex hull
 */
vector<Point> quick_hull(vector<Point> points) {
    vector<Point> hull;
    Point leftest = points[0], rightest = points[0];
    
    for (vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
        Point point = (Point) *it;
        if (point.get_x() < leftest.get_x() || (point.get_x() == leftest.get_x() && point.get_y() < leftest.get_y())) {
            leftest = point;
        }

        if (point.get_x() > rightest.get_x() || (point.get_x() == rightest.get_x() && point.get_y() > rightest.get_y())) {
            rightest = point;
        }
    }

    Line left_right_line = Line(leftest, rightest);
    vector<Point> left_points;
    vector<Point> right_points;

    for (vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
        Point point = (Point) *it;
        if (point == leftest || point == rightest) {
            continue;
        }
        if (left_right_line.is_on_left(point)) {
            left_points.push_back(point);
        }
        else {
            right_points.push_back(point);
        }
    }

    vector<Point> left_hull = find_hull(left_points, left_right_line);
    vector<Point> right_hull = find_hull(right_points, left_right_line.reverse());
    vector<Point> merged_hull;
    merged_hull.push_back(leftest);
    merged_hull.push_back(rightest);
    merged_hull.insert(merged_hull.end(), left_hull.begin(), left_hull.end());
    merged_hull.insert(merged_hull.end(), right_hull.begin(), right_hull.end());
    return merged_hull;
}


#endif
/* convex_hull_h */
