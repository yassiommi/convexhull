/**
 * @file bmp.hpp
 * @author Yassaman Ommi (ommiy@mcmaster.ca)
 * @brief Bitmap Image Functions
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <string>
#include "utils.hpp"

using namespace std;

#define BMP_HEADER_SIZE 14
#define DIB_HEADER_SIZE 40
#define WHITE "FFFFFF"
#define BLACK "000000"
#define RED "0000FF"

// following https://en.wikipedia.org/wiki/BMP_file_format guide for creating BMP
/**
 * @brief calculate the size of the bitmap image
 * @param width
 * @param height
 * @return uint64_t size of the bitmap image
 */
uint64_t calculate_file_size(uint64_t width, uint64_t height)
{
    // each pixel is presented with 3 bytes, plus a padding to keep it
    // at 4 byte alignment
    uint64_t row_bytes = 3 * width + ((3 * width) % 4 == 0 ? 0 : 4 - ((3 * width) % 4));
    uint64_t data_size = row_bytes * height;
    return data_size + BMP_HEADER_SIZE + DIB_HEADER_SIZE;
}

/**
 * @brief Create a bitmap file header object
 *
 * @param width
 * @param height
 * @return std::string
 */
std::string create_bitmap_file_header(uint64_t width, uint64_t height)
{
    std::string BITMAP_HEADER = "";
    // "BM"
    std::string ID_FIELD = "424D";
    // file size
    uint64_t bmp_file_size = calculate_file_size(width, height);
    std::string SIZE = reverse_every_two_bytes_in_hex(int_to_hex_string(bmp_file_size));
    // unused fields in the middle of string
    std::string UNUSED = "00000000";
    // for this version, always 14 + 40 = 54 bytes
    std::string OFFSET = "36000000";

    BITMAP_HEADER += ID_FIELD;
    BITMAP_HEADER += SIZE;
    BITMAP_HEADER += UNUSED;
    BITMAP_HEADER += OFFSET;

    return BITMAP_HEADER;
}

/**
 * @brief Create a DIB header object
 *
 * @param width
 * @param height
 * @return std::string
 */
std::string create_dib_header(uint64_t width, uint64_t height)
{
    std::string DIB_HEADER = "";
    // header always 40 bytes in this bitmap version
    std::string DIB_HEADER_BYTES = "28000000";
    // width of image
    std::string WIDTH = reverse_every_two_bytes_in_hex(int_to_hex_string(width));
    // height of image
    std::string HEIGHT = reverse_every_two_bytes_in_hex(int_to_hex_string(height));
    // number of color planes: always 1
    std::string PLANES = "0100";
    // number of bits per pixel: always 24
    std::string BITS = "1800";
    // no compression used
    std::string COMPRESSION = "00000000";
    // size of raw data including the padding
    uint64_t raw_data_size = calculate_file_size(width, height) - BMP_HEADER_SIZE - DIB_HEADER_SIZE;
    std::string DATA_SIZE = reverse_every_two_bytes_in_hex(int_to_hex_string(raw_data_size));
    // print resolution: none
    std::string PRINT = "0000000000000000";
    // colors in the palette
    std::string PALETTE = "00000000";
    // important colors: all
    std::string IMPORTANT_COLORS = "00000000";

    DIB_HEADER += DIB_HEADER_BYTES;
    DIB_HEADER += WIDTH;
    DIB_HEADER += HEIGHT;
    DIB_HEADER += PLANES;
    DIB_HEADER += BITS;
    DIB_HEADER += COMPRESSION;
    DIB_HEADER += DATA_SIZE;
    DIB_HEADER += PRINT;
    DIB_HEADER += PALETTE;
    DIB_HEADER += IMPORTANT_COLORS;

    return DIB_HEADER;
}

/**
 * @brief Create a bitmap hex from image array object
 *
 * @param image_array
 * @param width
 * @param height
 * @return std::string
 */
std::string create_bitmap_hex_from_image_array(double **image_array, uint64_t width, uint64_t height)
{
    std::string image;
    std::string BITMAP_FILE_HEADER = create_bitmap_file_header(width, height);
    std::string DIB_HEADER = create_dib_header(width, height);

    image += BITMAP_FILE_HEADER;
    image += DIB_HEADER;

    for (uint64_t i = 0; i < height; i++)
    {
        for (uint64_t j = 0; j < width; j++)
        {
            image += image_array[i][j] == 1 ? BLACK : (image_array[i][j] == 2 ? RED : WHITE);
        }
    }

    return image;
}

/**
 * @brief Create a bmp file from hex object
 *
 * @param image
 * @param filename
 */
void create_bmp_file_from_hex(std::string image, char *filename)
{
    std::string binary = hex_string_to_binary_string(image);
    FILE *image_file;
    image_file = fopen(filename, "wb");
    fwrite(binary.c_str(), sizeof(char), binary.length(), image_file);
    fclose(image_file);
}