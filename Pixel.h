// ============================
// PIXEL.H
// ============================

#ifndef PIXEL_H
#define PIXEL_H

struct Pixel
{
    unsigned char r;         //these are the RGB colors  and are unsigned because RGB values normally ranges from 0-255
    unsigned char g;
    unsigned char b;

    Pixel(unsigned char r = 0,
        unsigned char g = 0,
        unsigned char b = 0)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

#endif