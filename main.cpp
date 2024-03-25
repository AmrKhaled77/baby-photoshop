#include "Image_Class.h"

using namespace  std;
void  start();

void saveImage(Image image,string filePath){
    int choice;
    cout<<"(1)===> save in the same file  "<<endl;
    cout<<"(2)===> save in new file "<<endl;
    int error;
    do
    {
        error = 0;
        cout << " : ";
        cin >> choice; // Get the number of swaps from user
        if (cin.fail())
        {
            cout << "Please enter a valid choice ," << endl;
            error = 1;
            cin.clear();
            cin.ignore(80, '\n');
        }
    } while (error == 1);


    switch (choice) {
        case 1:
            try { image.saveImage(filePath);; }
            catch (const std::exception& e)
            {  saveImage( image, filePath); }

            cout<<" done and file saved successfully"<<endl;
            start();
            break;
        case 2:
            string newPth;
            cout<<" please enter  new path  consider the extension  (.PNG , .JPEG, .TIFF, .JPG )  : "<<endl;
            cin>>newPth;
            try { image.saveImage(newPth); }
            catch (const std::exception& e)
            {
                cout<<"please enter valid image path"<<endl;
                saveImage( image, filePath); }

            cout<<" done and file saved successfully"<<endl;
            start();
            break;

    }
}

void invert(Image image,string filePath ){
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
    saveImage(image,filePath);
}

void addDecoratedFrame(Image image,string filePath) {
    int frameWidth=40;
    int borderWidth=20;
    int cornerSize=60;
    // Add the frame

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            if (y < frameWidth || y >= image.height - frameWidth ||
                x < frameWidth || x >= image.width - frameWidth) {
                image(x, y, 0)=0;
                image(x, y, 1)=0;
                image(x, y, 2)=200;
            }
        }
    }

    // Add the border
    for (int y = frameWidth; y < image.height - frameWidth; ++y) {
        for (int x = frameWidth; x < image.width - frameWidth; ++x) {
            if (y < frameWidth + borderWidth || y >= image.height - frameWidth - borderWidth ||
                x < frameWidth + borderWidth || x >= image.width - frameWidth - borderWidth) {
                image(x, y, 0)=255;
                image(x, y, 1)=255;
                image(x, y, 2)=255;
            }
        }

    }

    int hollowSize=50;
    for (int y = 0; y < cornerSize; ++y) {
        for (int x = 0; x < cornerSize; ++x) {


            image(x, y, 0)=255;
            image(x, y, 1)=255;
            image(x, y, 2)=255;

            image(image.width - x - 1, y, 0)=255;
            image(image.width - x - 1, y,1)=255;
            image(image.width - x - 1, y, 2)=255;

            image(x, image.height - y - 1,0)=255;
            image(x, image.height - y - 1, 1)=255;
            image(x, image.height - y - 1, 2)=255;

            image(image.width - x - 1,image.height - y - 1, 0)=255;
            image(image.width - x - 1,image.height - y - 1,  1)=255;
            image(image.width - x - 1,image.height - y - 1, 2)=255;





        }
    }
    saveImage(image,filePath);
}

void makeFrame(Image image,string filePath){
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
    saveImage(image,filePath);


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

void makeBlure(Image image,string filePath){
    int blur_concentrtion=9;

    // Iterate over each pixel in the image
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            int red = 0,
            green = 0,
            blue = 0
            , count = 0;

            for (int width = -blur_concentrtion; width <= blur_concentrtion; ++width) {
                for (int hight = -blur_concentrtion; hight <= blur_concentrtion; ++hight) {
                    int nx = x + hight;
                    int ny = y + width;

                    // Check if the current pixel is within the image bounds
                    if (nx >= 0 && nx < image.width && ny >= 0 && ny < image.height) {
                        // Accumulate the color values
                        red += image(nx, ny, 0);
                        green += image(nx, ny, 1);
                        blue += image(nx, ny, 2);
                        count++;
                    }
                }
            }
            // Average the color values
            image(x,y,0) = red / count;
            image(x,y,1) = green / count;
            image(x,y,2) = blue / count;
        }
    }

    saveImage(image,filePath);
}

void Rotate(Image image,int rotate,string filePath){


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
        saveImage(tempimage270,filePath);
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
        saveImage(tempimage180,filePath);
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
        saveImage(tempimage90,filePath);
    }
}

void Merg(Image image,Image image2,string filePath ){
    int newHight,newWidh;
    image.height>image2.height?newHight=image2.height:newHight=image.height;
    image.height>image2.height?newWidh=image2.width:newWidh=image.width;
    Image final(newWidh,newHight);
    for (int i = 0; i <image.width ; ++i) {
        for (int j = 0; j <image.height ; ++j) {

            for (int k = 0; k <3 ; ++k) {
                if(j%2==0){
                    final(i,j,k)=image(i,j,k);


                } else{
                    final(i,j,k)=image2(i,j,k);
                }
            }

        }

    }
    saveImage(final,filePath);
}

void b_w( Image imafge,string filePath)
{

    for(int i = 0; i<imafge.width;++i)
    {
        for(int o=0;o<imafge.height;++o)
        {
            unsigned int avg = 0;
            for(int t=0;t<3;++t)
            {
                avg+=imafge(i,o,t);
            }
            avg/=3;
            for(int t=0;t<3;++t)
            {
                if(avg>127)
                {
                    imafge(i,o,t)=255;
                }
                else
                {
                    imafge(i,o,t)=0;
                }

            }

        }

    }

    saveImage(imafge,filePath);

}

void addFrame(Image image, string filePath) {
    int frameWidth=40;
    // Add the top and bottom frame
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            if (y < frameWidth || y >= image.height - frameWidth) {
                image(x, y, 0)=0;
                image(x, y, 1)=0;
                image(x, y, 2)=200;
            }
        }
    }

    // Add the left and right frame
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            if (x < frameWidth || x >= image.width - frameWidth) {
                image(x, y, 0)=0;
                image(x, y, 1)=0;
                image(x, y, 2)=200;
            }
        }
    }
    saveImage(image,filePath);
}



void grayscale(Image image,string filePath)
{


    for(int i =0 ; i<image.width ;i++)
    {
        for(int j =0 ; j<image.height ;j++)
        {
            unsigned int avarege;
            for(int k=0;k<image.channels;k++)
            {
                avarege+= image(i,j,k);
            }
            avarege=avarege/3;
            image(i,j,0)=avarege;
            image(i,j,1)=avarege;
            image(i,j,2)=avarege;
        }
    }

    saveImage(image,filePath);
}




void start(){
    string filePath;
    cout<<" welcome"<<endl;
    cout<<" please enter file path : ";
    cin>>filePath;


    try { Image image(filePath); }
    catch (const std::exception& e)
    { start(); }
    while (true){



        int choose;
        string image2="";
        cout<<"please select what you want to do  "<<endl;
        cout<<"(1)===> Grayscale Conversion "<<endl;
        cout<<"(2)===> Black and White "<<endl;
        cout<<"(3)===> Rotate Image "<<endl;
        cout<<"(4)===> Adding a Frame to the Picture "<<endl;
        cout<<"(5)===> Blur Images "<<endl;
        cout<<"(6)===>Invert Image "<<endl;
        cout<<"(7)===>Merg "<<endl;
        cout<<"(0)===> exit "<<endl;

        int error;
        do
        {
            error = 0;
            cout << " : ";
            cin >> choose; // Get the number of swaps from user
            if (cin.fail())
            {
                cout << "Please enter a valid choice ," << endl;
                error = 1;
                cin.clear();
                cin.ignore(80, '\n');
            }
        } while (error == 1);

        if(choose==0){
            cout<<"app end";
            break;
        }

        switch (choose) {
            case 0:
                break;
            case 1:
                cout<<"please wait while your image is processing ......"<<endl;
                grayscale( Image(filePath),filePath);

                break;
            case 2:
                cout<<"please wait while your image is processing ......"<<endl;
                b_w( Image(filePath),filePath);
                break;
            case 3:

                int error;
                int rotate;
                do
                {
                    error = 0;
                    cout << " 90,180 or 270 degree : ";
                    cin >> rotate;
                    if (cin.fail())
                    {
                        cout << "Please enter a valid choice ," << endl;
                        error = 1;
                        cin.clear();
                        cin.ignore(80, '\n');
                    }
                } while (error == 1);
                cout<<"please wait while your image is processing ......"<<endl;
                Rotate( Image(filePath),rotate,filePath);
                break;
            case 4:
                cout<<"please wait while your image is processing ......"<<endl;
                addDecoratedFrame( Image(filePath), filePath);
                break;
            case 5:
                cout<<"please wait while your image is processing ......"<<endl;
                makeBlure( Image(filePath),filePath);
                break;
            case 6:
                cout<<"please wait while your image is processing ......"<<endl;
                invert( Image(filePath),filePath);

                break;
            case 7:

                cout<<"please enter path ot second image : "<<endl;

                cin>>image2;
                cout<<"please wait while your image is processing ......"<<endl;
                Merg( Image(filePath),Image(image2),filePath);

                break;

            default:
                cout << "please enter valid input"; // no error
                break;



        }
    }



}
int main() {

  start();



    return 0;



        }
