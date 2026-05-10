#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <cmath>
#include "Matrix.h"
#include "Pixel.h"

class Image
{
private:

    Matrix<Pixel> pixels;  // variable to store the image in the form of pixels in a 2-Dmatrix
    int width;
    int height;

public:

    Image(int w = 0, int h = 0)
        : width(w), height(h), pixels(h, w)  // it creates a matrix of pixels with h rows and w coulmns
    {
    }

    bool load(string filename)
    {
        ifstream file(filename, ios::binary);  // opening file in binary because it is raw data not text

        if (!file)
        {
            return false;
        }

        string format;
        file >> format;

        if (format != "P6")  // p6 is binary RGB kind of image format
        {
            return false;
        }

        file >> width >> height;

        int maxValue;
        file >> maxValue;   // this is used to reada color value

        file.ignore();

        pixels = Matrix<Pixel>(height, width);   //creating a matrix to store the image 

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Pixel p;  //creating temporary pixel object 

                file.read((char*)&p.r, 1);   //reading RGBvalues
                file.read((char*)&p.g, 1);  //  we are using char& because we are dealing with raw bits so pixel address becomes character pointers 
                file.read((char*)&p.b, 1);

                pixels(i, j) = p;  // stores pixels into the matrix
            }
        }

        file.close();
        return true;
    }

    bool save(string filename)
    {
        ofstream file(filename, ios::binary);

        if (!file)
        {
            return false;
        }

        file << "P6\n";  // write the file header 
        file << width << " " << height << "\n255\n";

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Pixel p = pixels(i, j);   // gets one pixel from the matrix for writing the file

                file.write((char*)&p.r, 1);  // takes the addres of red value and converts it into the pointer same for blue and red 
                file.write((char*)&p.g, 1);
                file.write((char*)&p.b, 1);
            }
        }

        file.close();
        return true;
    }

    Pixel getPixel(int x, int y)
    {
        return pixels(y, x);
    }

    void setPixel(int x, int y, Pixel value)  // we are using it because image uses x,y whereas matrices uses rows, colums which mean y,x so in order to get wirght oreder we use this 
    {
        pixels(y, x) = value;
    }

    int getWidth()
    {
        return width;
    }

    int getHeight()
    {
        return height;
    }

    void grayscale()  // we are converting the image colors to black and white because they are easier to compress
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Pixel& p = pixels(i, j);

                unsigned char gray =
                    (p.r + p.g + p.b) / 3;

                p.r = gray;
                p.g = gray;
                p.b = gray;
            }
        }
    }

    void brightness(int value)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Pixel& p = pixels(i, j);  // as we are usong refference here it directly effects the original image without creating any copy of that image

                p.r = min(255, max(0, p.r + value));  // keeps the value of RGB in between 0-255
                p.g = min(255, max(0, p.g + value));
                p.b = min(255, max(0, p.b + value));
            }
        }
    }

    void sharpen()
    {
        for (int i = 1; i < height - 1; i++)
        {
            for (int j = 1; j < width - 1; j++)
            {
                Pixel& p = pixels(i, j);

                p.r = min(255, p.r + 30);
                p.g = min(255, p.g + 30);
                p.b = min(255, p.b + 30);
            }
        }
    }

    void edgeDetection()   //
    {
        for (int i = 1; i < height - 1; i++)
        {
            for (int j = 1; j < width - 1; j++)
            {
                Pixel p1 = pixels(i - 1, j);
                Pixel p2 = pixels(i + 1, j);

                int diff = abs(p1.r - p2.r);

                unsigned char edge =
                    diff > 50 ? 255 : 0;

                pixels(i, j) =
                    Pixel(edge, edge, edge);
            }
        }
    }
};

#endif