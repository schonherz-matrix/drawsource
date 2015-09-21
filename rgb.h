#pragma once

#ifndef RGB_H
#define RGB_H

class RGB {
public:
    uint8_t r, g ,b;

    RGB(uint8_t r_ = 0, uint8_t g_ = 0, uint8_t b_ = 0);
    RGB(const RGB&) = default;
    RGB& operator=(const RGB&) = default;
};

inline RGB::RGB(uint8_t r_, uint8_t g_, uint8_t b_): r(r_), g(g_), b(b_) {}

#endif

