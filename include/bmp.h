#ifndef BMP_H
#define BMP_H

#include <stdint.h>

// 2022 Ian Moffett

struct __attribute__((packed)) BMP {
    struct __attribute__((packed)) Header {
        uint16_t signature;                     // 'BM'.
        uint32_t file_size;
        uint32_t reserved;
        uint32_t data_offset;
    } header;

    struct __attribute__((packed)) InfoHeader {
        uint32_t size;              // Sizeof info_header.
        uint32_t width;             // Width of bitmap in pixels.
        uint32_t height;            // Height of bitmap in pixels.
        uint16_t nplanes;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t image_size;
        uint32_t xpixels_per_meter;
        uint32_t ypixels_per_meter;
        uint32_t colors_used;
        uint32_t important_colors;
    } info_header;

    struct __attribute__((packed)) ColorTable {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t reserved;
    } color_table;

    char* pixel_data;
};


#endif
