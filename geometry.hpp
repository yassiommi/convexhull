/**
 * @file geometry.hpp
 * @author Yassaman Ommi (ommiy@mcmaster.ca)
 * @brief A file to store the Point and Line classes and perform operations on them
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief A class to store a 2d point data and perform operations on it
 */
class Point
{
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
    void set_coordinates(double x_to_set, double y_to_set)
    {
        set_x(x_to_set);
        set_y(y_to_set);
    }

    /**
     * @brief Set the x value
     *
     * @param X
     */
    void set_x(double x_to_set)
    {
        x = x_to_set;
    }

    /**
     * @brief Set the y value
     *
     * @param Y
     */
    void set_y(double y_to_set)
    {
        y = y_to_set;
    }

public:
    /**
     * @brief Construct a new Point object without given input
     * initiates with (0, 0)
     *
     */
    Point()
    {
        set_coordinates(0, 0);
    }

    /**
     * @brief Construct a new Point object with given input
     *
     * @param X
     * @param Y
     */
    Point(double x_to_set, double y_to_set)
    {
        set_coordinates(x_to_set, y_to_set);
    }

    /**
     * @brief Get the x variable's value
     *
     * @return x's value
     */
    double get_x()
    {
        return x;
    }

    /**
     * @brief Get the y variable's value
     *
     * @return y's value
     */
    double get_y()
    {
        return y;
    }

    /**
     * @brief Get the distance between this point and another point
     *
     * @param other
     * @return double
     */
    double distance_to(Point other)
    {
        double this_x = get_x(),
               this_y = get_y(),
               other_x = other.get_x(),
               other_y = other.get_y();
        return sqrt(pow(other_x - this_x, 2) + pow(other_y - this_y, 2));
    }

    /**
     * @brief overload assignment operator
     *  *
     * @param other
     */
    void operator=(const Point &other)
    {
        set_coordinates(other.x, other.y);
    }

    // keep the default behavior for other assignment operations
    Point(const Point &) = default;
    Point(Point &&) = default;
    Point &operator=(Point &&) = default;

    /**
     * @brief overload equality operator
     *
     * @param other
     * @return true if two points are the same
     * @return false otherwise
     */
    bool operator==(Point other)
    {
        return (get_x() == other.get_x()) && (get_y() == other.get_y());
    }

    /**
     * @brief overload inequality operator
     *
     * @param other
     * @return true if two points are not the same
     * @return false otherwise
     */
    bool operator!=(Point other)
    {
        return (get_x() != other.get_x()) || (get_y() != other.get_y());
    }

    /**
     * @brief overload subtraction operator
     *
     * @param other another point
     * @return Point
     */
    Point operator-(Point other)
    {
        return Point(get_x() - other.get_x(), get_y() - other.get_y());
    }

    friend std::ostream &operator<<(std::ostream &out, Point p);
};

/**
 * @brief A class to store a line data and perform operations on it
 */
class Line
{
private:
    /**
     * @brief The line's start and end points
     */
    Point start, end;

    /**
     * @brief Set the line coordinates object
     *
     * @param start_to_set
     * @param end_to_set
     */
    void set_line_coordinates(Point start_to_set, Point end_to_set)
    {
        set_start(start_to_set);
        set_end(end_to_set);
    }

    /**
     * @brief Set the start point of the line
     *
     * @param start_to_set given start point
     */
    void set_start(Point start_to_set)
    {
        start = start_to_set;
    }

    /**
     * @brief Set the end point of the line
     *
     * @param end_to_set given end point
     */
    void set_end(Point end_to_set)
    {
        end = end_to_set;
    }

public:
    /**
     * @brief Construct a new Line object without given input
     */
    Line()
    {
        set_line_coordinates(Point(), Point());
    }

    /**
     * @brief Construct a new Line object with given input
     *
     * @param start_to_set start point of the line
     * @param end_to_set end point of the line
     */
    Line(Point start_to_set, Point end_to_set)
    {
        set_line_coordinates(start_to_set, end_to_set);
    }

    /**
     * @brief Get the start point of the line
     *
     * @return Point
     */
    Point get_start()
    {
        return start;
    }

    /**
     * @brief Get the end point of the line
     *
     * @return Point
     */
    Point get_end()
    {
        return end;
    }

    /**
     * @brief Get the reversed line
     *
     * @return reversed line
     */
    Line reversed_line()
    {
        return Line(end, start);
    }

    /**
     * @brief Get the slope of the line
     *
     * @return the line's slope
     */
    double slope()
    {
        return (end.get_y() - start.get_y()) / (end.get_x() - start.get_x());
    }

    /**
     * @brief A function to calculate the intersection of the line with the y-axis
     *
     * @return intersection of the line with the y-axis
     */
    double intersection()
    {
        return end.get_y() - slope() * end.get_x();
    }

    /**
     * @brief Get the length of the line
     *
     * @return length of the line
     */
    double length()
    {
        return start.distance_to(end);
    }

    /**
     * @brief Get the distance between the line and a point
     *
     * @param p the point to calculate the distance from
     * @return distance between the line and the point
     */
    double distance_from_point(Point p)
    {
        double m = slope(), b = intersection();
        if (isinf(m))
        {
            return p.get_x() - get_start().get_x();
        }
        return abs(m * p.get_x() - p.get_y() + b) / sqrt(1 + m * m);
    }

    /**
     * @brief Check if a point is on the left of the line
     *
     * @param p
     * @return true if the point is on the left of the line
     * @return false otherwise
     */
    bool is_point_on_left_of_line(Point p)
    {
        double d = (p.get_x() - start.get_x()) * (end.get_y() - start.get_y()) - (p.get_y() - start.get_y()) * (end.get_x() - start.get_x());
        return d > 0;
    }

    /**
     * @brief overload subtraction operator
     *
     * @param other
     * @return Line
     */
    Line operator-(Line other)
    {
        return Line(get_start() - other.get_start(), get_end() - other.get_end());
    }

    /**
     * @brief dot product operator between two lines
     *
     * @param other
     * @return dot product
     */
    double operator*(Line other)
    {
        double x_dot = (get_end() - get_start()).get_x() * (other.get_end() - other.get_start()).get_x();
        double y_dot = (get_end() - get_start()).get_y() * (other.get_end() - other.get_start()).get_y();
        return (x_dot + y_dot) / (length() * other.length());
    }

    // extraction
    friend std::ostream &operator<<(std::ostream &out, Point p);
};

/**
 * @brief overload insertion operator
 *
 * @param out
 * @param p The point to get printed
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &out, Point p)
{
    out << "(" << p.get_x() << ", " << p.get_y() << ")";
    return out;
}

/**
 * @brief overload insertion operator
 *
 * @param out
 * @param line
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &out, Line line)
{
    out << line.get_start() << "->" << line.get_end();
    return out;
}
