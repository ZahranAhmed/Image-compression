// ============================
// MAIN.CPP
// ============================

#include <iostream>
#include <fstream>

#include "Image.h"
#include "Compression.h"

using namespace std;

long getFileSize(string filename)  // for getting the file size in bytes
{
    ifstream file(filename, ios::binary | ios::ate);  // ate over here moves the file pointer to eof sp that file position becomes total size of the file

    return file.tellg();
}

int main()
{
    Image img;

    if (!img.load("input.ppm"))
    {
        cout << "Image loading failed\n";
        return 0;
    }

    cout << "Original Image Loaded\n";

    cout << "Width: " << img.getWidth() << endl;

    cout << "Height: " << img.getHeight() << endl;

    cout << "Original Size: " << getFileSize("input.ppm") << " bytes\n";

    // IMAGE PROCESSING

    img.grayscale();

    img.brightness(20);

    img.sharpen();

    img.edgeDetection();

    img.save("processed.ppm");

    cout << "Processed Image Saved\n";

    cout << "Processed Size: " << getFileSize("processed.ppm") << " bytes\n";

    // COMPRESSION

    Compressor::compress(img, "compressed.bin");

    cout << "Compression Done\n";
    cout << "Compressed Size: " << getFileSize("compressed.bin") << " bytes\n";

    // COMPRESSION RATE

    double original = getFileSize("processed.ppm");

    double compressed = getFileSize("compressed.bin");

    double rate = ((original - compressed) / original) * 100;

    cout << "Compression Rate: " << rate << "%\n";

    // DECOMPRESSION

    Image reconstructed = Compressor::decompress("compressed.bin");

    reconstructed.save("reconstructed.ppm");

    cout << "Reconstructed Image Saved\n";

    return 0;
}