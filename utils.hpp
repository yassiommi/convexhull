/**
 * @file utils.hpp
 * @author Yassaman Ommi (ommiy@mcmaster.ca)
 * @brief  Some Utility Functions
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <iostream>
#include <bitset>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "geometry.hpp"

/**
 * @brief Generate random data points
 *
 * @param count the number of points to generate
 * @return std::vector<Point> a vector of randomly generated points
 */
std::vector<Point> generate_random_data_points(uint64_t count)
{
    srand((unsigned)time(0));
    std::vector<Point> data;

    for (uint64_t i = 0; i < count; i++)
    {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        data.push_back(Point(x, y));
    }

    return data;
}

/**
 * @brief reversing every two bytes in a hex string
 * @param hex a string to be reversed
 * @return std::string
 */
std::string reverse_every_two_bytes_in_hex(std::string hex)
{
    std::string reversed = hex;
    std::reverse(reversed.begin(), reversed.end());
    for (uint64_t i = 0; i < reversed.length(); i += 2)
    {
        swap(reversed[i], reversed[i + 1]);
    }
    return reversed;
}

// https://www.techiedelight.com/convert-an-integer-to-hex-string-in-cpp/
/**
 * @brief Convert an integer to a hex string
 *
 * @param number the number to be converted to hex string
 * @return std::string
 */
std::string int_to_hex_string(uint64_t number)
{
    std::ostringstream ss;
    ss << std::uppercase << std::setfill('0') << std::setw(8) << std::hex << number;
    return ss.str();
}

// https://www.techiedelight.com/convert-a-hexadecimal-string-to-an-integer-in-cpp/
/**
 * @brief Convert a hex string to an integer
 *
 * @param hex_string the string to be converted to an integer
 * @return uint64_t
 */
uint64_t hex_string_to_int(std::string hex_string)
{
    uint64_t number;
    std::istringstream iss(hex_string);
    iss >> std::hex >> number;
    return number;
}

/**
 * @brief Convert a hex string to a binary string
 *
 * @param hex the hex string to be converted to binary string
 * @return std::string
 */
std::string hex_string_to_binary_string(std::string hex)
{
    std::string binary_string = "";
    for (uint64_t i = 0; i < hex.length(); i += 2)
    {
        uint64_t character_code = hex_string_to_int(hex.substr(i, 2));
        binary_string += (char)character_code;
    }
    return binary_string;
}