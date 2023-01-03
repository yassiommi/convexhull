/**
 * @file main.cpp
 * @author Yassaman Ommi (ommiy@mcmaster.ca)
 * @brief A program to find the convex hull of a given set of point
 */

#include <iostream>
#include <vector>
#include "utils.hpp"
#include "geometry.hpp"
#include "bmp.hpp"
#include "visualizer.hpp"
#include "convex_hull.hpp"

#define DIM 512
#define DATA_COUNT 20

/**
 * @brief main function to run the program that finds the convex hull of a randomly generated set of points
 * 
 * @return int 
 */
int main()
{
    // generate random data and save to a bmp file
    double **image_array = initialize_image_array(DIM, DIM);
    std::vector<Point> data = generate_random_data_points(DATA_COUNT);
    for (vector<Point>::iterator it = data.begin(); it != data.end(); it++)
    {
        Point point = (Point)*it;
        image_array = add_point_to_image_array(image_array, DIM, DIM, point);
    }
    std::string hex_image = create_bitmap_hex_from_image_array(image_array, DIM, DIM);
    create_bmp_file_from_hex(hex_image, (char *)"data.bmp");

    // run gift wrapping algorithm on the data
    std::vector<Point> convex_hull = quick_hull(data);
    for (vector<Point>::iterator it = convex_hull.begin(); it != convex_hull.end(); it++)
    {
        Point point = (Point)*it;
        cout << point << endl;
    }
    std::vector<Line> convex_hull_lines = get_convex_hull_lines(convex_hull);
    for (vector<Line>::iterator it = convex_hull_lines.begin(); it != convex_hull_lines.end(); it++)
    {
        Line line = (Line)*it;
        image_array = add_line_to_image_array(image_array, DIM, DIM, line);
    }
    hex_image = create_bitmap_hex_from_image_array(image_array, DIM, DIM);
    create_bmp_file_from_hex(hex_image, (char *)"convex_hull.bmp");

    return 0;
}
