/**
 * @file convex_hull.hpp
 * @brief A file to implement the gift wrapping and Quickhull algorithm to find the convex hull of a set of points
 * @author Yassaman Ommi (ommiy@mcmaster.ca)
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include "geometry.hpp"

using namespace std;

#define INF_DOUBLE std::numeric_limits<double>::infinity()

/**
 * @brief A function to find the convex hull of a set of points using the gift wrapping algorithm
 *
 * @param points given set of points
 * @return vector<Point> a vector of points that form the convex hull
 */
vector<Point> gift_wrapping(vector<Point> points)
{
    vector<Point> hull;
    Point start = points[0], previous, current, next;
    double max_slope = -INF_DOUBLE, max_dot = -1;

    for (vector<Point>::iterator it = points.begin(); it != points.end(); it++)
    {
        Point point = (Point)*it;
        if (point.get_x() < start.get_x() || (point.get_x() == start.get_x() && point.get_y() < start.get_y()))
        {
            start = point;
        }
    }

    hull.push_back(start);
    previous = start;

    for (vector<Point>::iterator it = points.begin(); it != points.end(); it++)
    {
        Point point = (Point)*it;
        if (point == previous)
        {
            continue;
        }
        double slope = (point.get_y() - previous.get_y()) / abs(point.get_x() - previous.get_x());
        if (slope > max_slope)
        {
            max_slope = slope;
            current = point;
        }
    }

    while (current != *hull.begin())
    {
        max_dot = -1;
        for (vector<Point>::iterator it = points.begin(); it != points.end(); it++)
        {
            Point point = (Point)*it;
            if (point == current)
            {
                continue;
            }
            double dot_product = Line(previous, current) * Line(current, point);
            if (dot_product > max_dot)
            {
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
vector<Point> find_hull(vector<Point> points, Line base)
{
    if (points.empty())
    {
        return points;
    }
    vector<Point> left_points;
    for (vector<Point>::iterator it = points.begin(); it != points.end(); it++)
    {
        Point point = (Point)*it;
        if (point == base.get_start() || point == base.get_end())
        {
            continue;
        }
        if (base.is_point_on_left_of_line(point))
        {
            left_points.push_back(point);
        }
    }

    double max_dist = -INF_DOUBLE;
    Point farthest;
    for (vector<Point>::iterator it = left_points.begin(); it != left_points.end(); it++)
    {
        Point point = (Point)*it;
        if (base.distance_from_point(point) > max_dist)
        {
            farthest = point;
            max_dist = base.distance_from_point(point);
        }
    }

    vector<Point> outside_triangle;
    Line first_line = Line(base.get_start(), farthest), second_line = Line(farthest, base.get_end());

    for (vector<Point>::iterator it = left_points.begin(); it != left_points.end(); it++)
    {
        Point point = (Point)*it;
        if (point == farthest)
        {
            continue;
        }
        if (first_line.is_point_on_left_of_line(point) || second_line.is_point_on_left_of_line(point))
        {
            outside_triangle.push_back(point);
        }
    }

    vector<Point> first_hull = find_hull(outside_triangle, first_line);
    vector<Point> second_hull = find_hull(outside_triangle, second_line);
    vector<Point> merged_hull;
    if (farthest != Point())
    {
        merged_hull.push_back(farthest);
    }
    merged_hull.insert(merged_hull.end(), first_hull.begin(), first_hull.end());
    merged_hull.insert(merged_hull.end(), second_hull.begin(), second_hull.end());

    return merged_hull;
}

/**
 * @brief A function to find the convex hull of a set of points using the Quickhull algorithm
 *
 * @param points given set of points
 * @return vector<Point> a vector of points that form the convex hull
 */
vector<Point> quick_hull(vector<Point> points)
{
    vector<Point> hull;
    Point leftest = points[0], rightest = points[0];

    for (vector<Point>::iterator it = points.begin(); it != points.end(); it++)
    {
        Point point = (Point)*it;
        if (point.get_x() < leftest.get_x() || (point.get_x() == leftest.get_x() && point.get_y() < leftest.get_y()))
        {
            leftest = point;
        }

        if (point.get_x() > rightest.get_x() || (point.get_x() == rightest.get_x() && point.get_y() > rightest.get_y()))
        {
            rightest = point;
        }
    }

    Line left_right_line = Line(leftest, rightest);
    vector<Point> left_points;
    vector<Point> right_points;

    for (vector<Point>::iterator it = points.begin(); it != points.end(); it++)
    {
        Point point = (Point)*it;
        if (point == leftest || point == rightest)
        {
            continue;
        }
        if (left_right_line.is_point_on_left_of_line(point))
        {
            left_points.push_back(point);
        }
        else
        {
            right_points.push_back(point);
        }
    }

    vector<Point> left_hull = find_hull(left_points, left_right_line);
    vector<Point> right_hull = find_hull(right_points, left_right_line.reversed_line());
    vector<Point> merged_hull;
    merged_hull.push_back(leftest);
    merged_hull.push_back(rightest);
    merged_hull.insert(merged_hull.end(), left_hull.begin(), left_hull.end());
    merged_hull.insert(merged_hull.end(), right_hull.begin(), right_hull.end());
    return merged_hull;
}

/**
 * @brief Gets the set of lines that form the convex hull / connect the points of the convex hull
 *
 * @param convex_hull a set of points that form the convex hull
 * @return vector<Line>
 */
vector<Line> get_convex_hull_lines(vector<Point> convex_hull)
{
    vector<Line> hull_lines;

    for (vector<Point>::iterator it1 = convex_hull.begin(); it1 != convex_hull.end(); it1++)
    {
        Point p1 = (Point)*it1;
        for (vector<Point>::iterator it2 = convex_hull.begin(); it2 != convex_hull.end(); it2++)
        {
            Point p2 = (Point)*it2;
            if (p1 == p2)
            {
                continue;
            }
            bool all_on_right = true;
            Line p12_line = Line(p1, p2);
            for (vector<Point>::iterator it3 = convex_hull.begin(); it3 != convex_hull.end(); it3++)
            {
                Point p3 = (Point)*it3;
                if (p1 == p3 || p2 == p3)
                {
                    continue;
                }
                all_on_right = all_on_right && p12_line.is_point_on_left_of_line(p3);
            }
            if (all_on_right)
            {
                hull_lines.push_back(p12_line);
                break;
            }
        }
    }

    return hull_lines;
}