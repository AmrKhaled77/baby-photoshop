#include "Image_Class.h"

using namespace  std;


void invert(Image image){
    int red=0;
    int green=0;
    int blue=0;

    for (int i = 0; i <image.width ; ++i) {
        for (int j = 0; j <image.height ; ++j) {

            red=image(i,j,0);
            green=image(i,j,1);
            blue=image(i,j,2);

            image(i,j,0)=255-red;
            image(i,j,1)=255-green;
            image(i,j,2)=255-blue;
        }

    }
    image.saveImage("test1.png");
}

void makeFrame(Image image){
    //ceil and ground
    for (int i = 0; i <image.width ; ++i) {
        for (int j = 0; j <45 ; ++j) {

            image(i,j,0)=0;
            image(i,j,1)=0;
            image(i,j,2)=200;

            image(i,image.height-45+j,0)=0;
            image(i,image.height-45+j,1)=0;
            image(i,image.height-45+j,2)=200;


        }


    }


// left and right
    for (int i = 0; i <45 ; ++i) {
        for (int j = 0; j <image.height ; ++j) {

            image(i,j,0)=0;
            image(i,j,1)=0;
            image(i,j,2)=200;
            image(image.width-45+i,j,0)=0;
            image(image.width-45+i,j,1)=0;
            image(image.width-45+i,j,2)=200;


        }


    }

    image.saveImage("test1.png");
}

void makeBlure(Image image){
    int kernelSize=10;

    // Iterate over each pixel in the image
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            int totalR = 0, totalG = 0, totalB = 0;
            int count = 0;
            // Iterate over each pixel in the kernel neighborhood
            for (int dy = -kernelSize; dy <= kernelSize; ++dy) {
                for (int dx = -kernelSize; dx <= kernelSize; ++dx) {
                    int nx = x + dx;
                    int ny = y + dy;

                    // Check if the current pixel is within the image bounds
                    if (nx >= 0 && nx < image.width && ny >= 0 && ny < image.height) {
                        // Accumulate the color values
                        totalR += image(nx,ny,0);
                        totalG += image(nx,ny,1);
                        totalB += image(nx,ny,2);
                        count++;
                    }
                }
            }
            // Average the color values
            image(x,y,0) = totalR / count;
            image(x,y,1) = totalG / count;
            image(x,y,2) = totalB / count;
        }
    }

    image.saveImage("test9.png");
}



void Rotate(Image image,int rotate){


    if (rotate==270) {

        // Rotate 270 degrees
        Image tempimage270(image.height, image.width); // Swap width and height for rotated image

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                // Perform coordinate transformation for rotation
                tempimage270(j, image.width - i - 1, 0) = image(i, j, 0);
                tempimage270(j, image.width - i - 1, 1) = image(i, j, 1);
                tempimage270(j, image.width - i - 1, 2) = image(i, j, 2);
            }
        }
        tempimage270.saveImage("test3.png");
    }
    else if (rotate==180) {
        // Rotate 180 degrees
        Image tempimage180(image.width, image.height); // No need to change dimensions for 180-degree rotation

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                // Perform coordinate transformation for rotation
                tempimage180(image.width - i - 1, image.height - j - 1, 0) = image(i, j, 0);
                tempimage180(image.width - i - 1, image.height - j - 1, 1) = image(i, j, 1);
                tempimage180(image.width - i - 1, image.height - j - 1, 2) = image(i, j, 2);
            }
        }
        tempimage180.saveImage("test1.png");
    }
    else if (rotate==90){
        // Rotate 90 degrees
        Image tempimage90(image.height, image.width); // Swap width and height for rotated image

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                // Perform coordinate transformation for rotation
                tempimage90(image.height - j - 1, i, 0) = image(i, j, 0);
                tempimage90(image.height - j - 1, i, 1) = image(i, j, 1);
                tempimage90(image.height - j - 1, i, 2) = image(i, j, 2);
            }
        }
        tempimage90.saveImage("test2.png");
    }
}


int main() {


    Image image("building.jpg");

    cout << "Hello, World!" << std::endl;
    return 0;



        }
        //asda