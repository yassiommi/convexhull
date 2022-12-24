/**
 * @file convex_hull.cpp
 * @author Yassaman Ommi (ommiy@mcmaster.ca)
 * @brief A program to find the convex hull of a given set of point
 */

#include <iostream>
#include "convex_hull.hpp"

int main() {
    Point p1 = Point(0, 0), p2 = Point(-1, -1), p3 = Point(0, 4), p4 = Point(3, 2), p5 = Point(5, 6), p6 = Point(0, 1.5);
    vector<Point> points;
    points.push_back(p1); points.push_back(p2); points.push_back(p3); points.push_back(p4); points.push_back(p5), points.push_back(p6);

    vector<Point> cvx_hull_quick = quick_hull(points);
    cout << "Points on the convex hull: (Quickhull)" << endl;
    for (vector<Point>::iterator it1 = cvx_hull_quick.begin(); it1 != cvx_hull_quick.end(); it1++) {
        Point point1 = (Point) *it1;
        cout << point1 << endl;
    }

    vector<Point> cvx_hull_gift = quick_hull(points);
    cout << "Points on the convex hull: (Gift-wrapping)" << endl;
    for (vector<Point>::iterator it2 = cvx_hull_gift.begin(); it2 != cvx_hull_gift.end(); it2++) {
        Point point2 = (Point) *it2;
        cout << point2 << endl;
    }
}
