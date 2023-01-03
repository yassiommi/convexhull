/**
 * @file visualizer.hpp
 * @author Yassaman Ommi (ommiy@mcmaster.ca)
 * @brief Visualization Utilities for Convex Hull Presentation
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <string>
#include <cmath>
#include <fstream>
#include "geometry.hpp"

#define PADDING 2
#define POINT_THICKNESS 2
#define LINE_THICKNESS 1

/**
 * @brief A function to initialize a 2d array of width * height to be used as an image
 *
 * @param width width of the image
 * @param height height of the image
 * @return double** an array of width * height
 */
double **initialize_image_array(uint64_t width, uint64_t height)
{
    double **array;
    array = new double *[height];

    for (uint64_t i = 0; i < height; ++i)
    {
        array[i] = new double[width];
    }

    for (uint64_t i = 0; i < height; ++i)
    {
        for (uint64_t j = 0; j < width; ++j)
        {
            array[i][j] = 0;
        }
    }

    return array;
}

/**
 * @brief Get the coordinate location on image object
 *
 * @param coord
 * @param length
 * @return uint64_t
 */
inline uint64_t get_coordinate_location_on_image(double coord, uint64_t length)
{
    return (uint64_t)floor(coord * (length - 2 * (PADDING + POINT_THICKNESS))) + PADDING + POINT_THICKNESS;
}

/**
 * @brief A function to add a point to an image array
 *
 * @param image_array
 * @param width
 * @param height
 * @param p
 * @return double**
 */
double **add_point_to_image_array(double **image_array, uint64_t width, uint64_t height, Point p)
{
    uint64_t center_x = get_coordinate_location_on_image(p.get_x(), width);
    uint64_t center_y = get_coordinate_location_on_image(p.get_y(), height);
    // cout << center_x << " " << center_y << endl;
    for (uint64_t i = center_x - POINT_THICKNESS; i <= center_x + POINT_THICKNESS; i++)
    {
        for (uint64_t j = center_y - POINT_THICKNESS; j <= center_y + POINT_THICKNESS; j++)
        {
            image_array[i][j] = 1;
        }
    }
    return image_array;
}

/**
 * @brief A function to add a line to an image array
 *
 * @param image_array
 * @param width
 * @param height
 * @param line
 * @return double**
 */
double **add_line_to_image_array(double **image_array, uint64_t width, uint64_t height, Line line)
{
    uint64_t start_point_x = get_coordinate_location_on_image(line.get_start().get_x(), width);
    uint64_t start_point_y = get_coordinate_location_on_image(line.get_start().get_y(), height);
    uint64_t end_point_x = get_coordinate_location_on_image(line.get_end().get_x(), width);
    uint64_t end_point_y = get_coordinate_location_on_image(line.get_end().get_y(), height);

    Line image_coordinate_line = Line(Point(start_point_x, start_point_y), Point(end_point_x, end_point_y));

    double slope = image_coordinate_line.slope(), intersection = image_coordinate_line.intersection();

    uint64_t start_x, end_x;
    if (start_point_x < end_point_x)
    {
        start_x = start_point_x;
        end_x = end_point_x;
    }
    else
    {
        start_x = end_point_x;
        end_x = start_point_x;
    }

    if (start_x == end_x)
    {
        uint64_t start_y = start_point_y < end_point_y ? start_point_y : end_point_y;
        uint64_t end_y = start_point_y >= end_point_y ? end_point_y : start_point_y;
        for (uint64_t i = start_y; i < end_y; i++)
        {
            image_array[start_x][i] = 2;
        }
    }
    else
    {
        for (uint64_t i = start_x; i < end_x; i++)
        {
            uint64_t y = (uint64_t)floor(slope * i + intersection);
            for (uint64_t j = i - LINE_THICKNESS; j <= i + LINE_THICKNESS; j++)
            {
                for (uint64_t k = y - LINE_THICKNESS; k <= y + LINE_THICKNESS; k++)
                {
                    image_array[j][k] = 2;
                }
            }
        }
    }

    return image_array;
}
