#pragma once

#include <string>
#include "../tester.hpp"
#include "../utils.hpp"

void test_int_to_hex_string()
{
    std::string hex = int_to_hex_string(10);
    IS_EQUAL(hex.compare("0000000A"), 0);
}

void test_hex_string_to_int()
{
    std::string hex1 = "B";
    std::string hex2 = "00000000B";
    std::string hex3 = "00000A001";

    IS_EQUAL(hex_string_to_int(hex1), 11);
    IS_EQUAL(hex_string_to_int(hex2), 11);
    IS_EQUAL(hex_string_to_int(hex3), 40961);
}

void test_utils()
{
    test_int_to_hex_string();

    test_hex_string_to_int();
}