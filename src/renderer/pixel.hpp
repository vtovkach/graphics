#pragma once

#include <cstdint>

struct __attribute__((packed)) Pixel
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0; 
    uint8_t a = 255; 
};