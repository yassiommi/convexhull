/**
 * @file tester.hpp
 * @author Yassaman Ommi (ommiy@mcmaster.ca)
 * @brief Basic testing utilities
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

/**
 * @brief A macro to check if a condition is true
 */
#define IS_TRUE(x)                                                                    \
    {                                                                                 \
        if (!(x))                                                                     \
            std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; \
    }

/**
 * @brief A macro to check if a condition is false
 */
#define IS_FALSE(x)                                                                   \
    {                                                                                 \
        if (x)                                                                        \
            std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; \
    }

/**
 * @brief A macro to check if two values are equal
 *
 */
#define IS_EQUAL(x, y)                                                                                                         \
    {                                                                                                                          \
        if (x != y)                                                                                                            \
            std::cout << __FUNCTION__ << " failed on line " << __LINE__ << " - expected: " << y << " got: " << x << std::endl; \
    }

/**
 * @brief A macro to check if two values are not equal
 *
 */
#define IS_NOT_EQUAL(x, y)                                                            \
    {                                                                                 \
        if (x == y)                                                                   \
            std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; \
    }