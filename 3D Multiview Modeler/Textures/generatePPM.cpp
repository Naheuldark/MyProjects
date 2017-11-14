#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>

unsigned char* ReadBMP(char* filename, int &width, int &height)
{
    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        throw "Argument Exception";

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    width = *(int*)&info[18];
    height = *(int*)&info[22];

    //std::cout << std::endl;
    //std::cout << "  Name: " << filename << std::endl;
    //std::cout << " Width: " << width << std::endl;
    //std::cout << "Height: " << height << std::endl;

    int row_padded = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;

    for(int i = 0; i < height; i++)
    {
        fread(data, sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < width*3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;

            //std::cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< std::endl;
        }
    }

    fclose(f);
    return data;
}
 
int main(int argc, char *argv[])
{
    int width, height;
    int maxVal = 255;
    unsigned char *data = ReadBMP(argv[1], width, height);

    std::ofstream ppm;

    std::string rawname = std::string(argv[1]);
    size_t lastindex = rawname.find_last_of("."); 
    rawname = rawname.substr(4, lastindex-4); 
    char name[80];
    strcpy(name, "PPM/");
    strcat(name, rawname.c_str());
    strcat(name, ".ppm");

    ppm.open(name);

    ppm << "P3" << std::endl;
    ppm << width << " " << height << std::endl;
    ppm << maxVal << std::endl;
    
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < 3*width; j+=3) {
            ppm << (int)data[j] << " " << (int)data[j + 1] << " " << (int)data[j + 2] << "\t";
        }
        ppm << std::endl;
    }

    ppm.close();

    return EXIT_SUCCESS;
}