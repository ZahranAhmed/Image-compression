// ============================
// COMPRESSION.H
// ============================

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <fstream>
#include "Image.h"

class Compressor
{
public:

    static void compress(Image& img, string filename) //we used static so that we we can call it directly without creating any object 
    {
        ofstream file(filename, ios::binary);  // compressess the image and stores the data in the file

        int width = img.getWidth();
        int height = img.getHeight();

        file.write((char*)&width, sizeof(width));  //compressed files begins with width and hieght so that the decompresor know the size of the image
        file.write((char*)&height, sizeof(height));

        for (int i = 0; i < height; i++)
        {
            int count = 1;  // keeping the track of pixel how many times does it repeat

            Pixel prev = img.getPixel(0, i);  // stores the first pixel as a reference 

            for (int j = 1; j < width; j++)
            {
                Pixel current = img.getPixel(j, i);  // gets current pixel

                if (current.r == prev.r &&  // if the pixels match with each other increement the count
                    current.g == prev.g &&
                    current.b == prev.b)
                {
                    count++;
                }
                else
                {
                    file.write((char*)&count, sizeof(count));  // how many repitations occured

                    file.write((char*)&prev, sizeof(Pixel));  //stores pixel value

                    prev = current;  // now reset everthing and start counting again
                    count = 1;
                }
            }

            file.write((char*)&count, sizeof(count));  // these two are for the last sequence because it is not saved yet

            file.write((char*)&prev, sizeof(Pixel));
        }

        file.close();
    }

    static Image decompress(string filename) //reads the compresed file and decompress it 
    {
        ifstream file(filename, ios::binary);

        int width;
        int height;

        file.read((char*)&width, sizeof(width));
        file.read((char*)&height, sizeof(height));

        Image img(width, height);

        int x = 0;
        int y = 0;

        while (!file.eof())
        {
            int count;
            Pixel p;

            file.read((char*)&count, sizeof(count));  //reads repiotion count

            file.read((char*)&p, sizeof(Pixel)); // reads pixel value

            if (file.eof())
            {
                break;
            }

            for (int i = 0; i < count; i++)
            {
                img.setPixel(x, y, p);  // restores orignal pixels

                x++;  // moves to next column

                if (x >= width)
                {
                    x = 0;
                    y++;
                }
            }
        }

        file.close();

        return img;
    }
};

#endif