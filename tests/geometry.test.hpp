#pragma once

#include "../tester.hpp"
#include "../geometry.hpp"

// Point class unit tests
void test_initialize_point_without_coordinates()
{
    Point point = Point();

    IS_EQUAL(point.get_x(), 0);
    IS_EQUAL(point.get_y(), 0);
}

void test_initialize_point_with_coordinates()
{
    Point point = Point(1, 2);

    IS_EQUAL(point.get_x(), 1);
    IS_EQUAL(point.get_y(), 2);
}

void test_distance_between_two_points()
{
    Point p1 = Point(0, 0);
    Point p2 = Point(3, 4);

    IS_EQUAL(p1.distance_to(p2), 5.0);
}

void test_point_assignment_operator()
{
    Point p1 = Point(0, 0), p2 = Point(1, 1), p3 = Point(2, 2);
    p2 = p1;

    IS_EQUAL(p1.get_x(), p2.get_x());
    IS_EQUAL(p1.get_y(), p2.get_y());

    p1 = p3;

    // check if only values are copied
    IS_NOT_EQUAL(p1.get_x(), p2.get_x());
    IS_NOT_EQUAL(p1.get_y(), p2.get_y());
}

void test_point_equality_operator()
{
    Point p1 = Point(0, 0), p2 = Point(0, 0), p3 = Point(1, 1);

    IS_TRUE(p1 == p2);
    IS_FALSE(p1 == p3);
}

void test_point_inequality_operator()
{
    Point p1 = Point(0, 0), p2 = Point(0, 0), p3 = Point(1, 1);

    IS_FALSE(p1 != p2);
    IS_TRUE(p1 != p3);
}

void test_point_subtraction_operator()
{
    Point p1 = Point(1, 1), p2 = Point(2, 2), p3 = Point(-1, -1);

    IS_EQUAL(p1 - p2, p3);
}

// Line class unit tests
void test_initialize_line_without_points()
{
    Line line = Line();
    
    IS_EQUAL(line.get_start(), Point(0, 0));
    IS_EQUAL(line.get_end(), Point(0, 0));
}

void test_initialize_line_with_points()
{
    Point start = Point(0, 0), end = Point(1, 1);
    Line line = Line(start, end);

    IS_EQUAL(line.get_start(), start);
    IS_EQUAL(line.get_end(), end);
}

void test_reversed_line()
{
    Point start = Point(0, 0), end = Point(1, 1);
    Line line = Line(start, end);
    Line reversed = line.reversed_line();

    IS_EQUAL(reversed.get_start(), end);
    IS_EQUAL(reversed.get_end(), start);
}

void test_line_slope_and_intersection_values()
{
    Point start = Point(0, 0), end = Point(1, 1);
    Line line = Line(start, end);

    IS_EQUAL(line.slope(), 1.0);
    IS_EQUAL(line.intersection(), 0.0);
}

void test_line_distance_from_point()
{
    Point start = Point(0, 0), end = Point(0, 1), p = Point(1, 0);
    Line line = Line(start, end);

    IS_EQUAL(line.distance_from_point(p), 1);
}

void test_point_on_the_left_of_the_line()
{
    Point start = Point(0, 0), end = Point(0, 1), p1 = Point(1, 0), p2 = Point(-1, 0);
    Line line = Line(start, end);

    IS_TRUE(line.is_point_on_left_of_line(p1));
    IS_FALSE(line.is_point_on_left_of_line(p2));
}

void test_line_subtraction()
{
    Point start = Point(0, 0), end = Point(0, 1), p1 = Point(1, 0), p2 = Point(-1, 0);
    Line first_line = Line(start, end);
    Line second_line = Line(p1, p2);
    Line sub_line = first_line - second_line;

    IS_EQUAL(sub_line.get_start(), start - p1);
    IS_EQUAL(sub_line.get_end(), end - p2);
}


void test_geometry()
{
    // run Point unit tests
    test_initialize_point_without_coordinates();

    test_initialize_point_with_coordinates();

    test_distance_between_two_points();

    test_point_assignment_operator();

    test_point_equality_operator();

    test_point_subtraction_operator();

    // run Line unit tests
    test_initialize_line_without_points();

    test_initialize_line_with_points();

    test_reversed_line();

    test_line_slope_and_intersection_values();

    test_line_distance_from_point();

    test_point_on_the_left_of_the_line();

    test_line_subtraction();
}