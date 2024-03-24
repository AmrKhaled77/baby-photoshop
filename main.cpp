#include "Image_Class.h"

using namespace  std;
void vaildtionOnSave(){


}

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

            cout<<" done and file saved successfully";
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

            cout<<" done and file saved successfully";
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
    int blur_concentrtion=10;

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




string start(){
    string filePath;
    cout<<" welcome"<<endl;
    cout<<" please enter file path : ";
    cin>>filePath;


    try { Image image(filePath); }
    catch (const std::exception& e)
    { filePath=start(); }
    return  filePath;


}
int main() {

    string filePath=start();


    while (true){



        int choose;
        cout<<"please select what you want to do  "<<endl;
        cout<<"(1)===> Grayscale Conversion "<<endl;
        cout<<"(2)===> Black and White "<<endl;
        cout<<"(3)===> Rotate Image "<<endl;
        cout<<"(4)===> Adding a Frame to the Picture "<<endl;
        cout<<"(5)===> Blur Images "<<endl;
        cout<<"(6)===>Invert Image "<<endl;
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
                grayscale( Image(filePath),filePath);

                break;
            case 2:
                invert( Image(filePath),filePath);
                break;
            case 3:
                int error;
                int rotate;
                do
                {
                    error = 0;
                    cout << " 90,180 or 270 degree : ";
                    cin >> rotate; // Get the number of swaps from user
                    if (cin.fail())
                    {
                        cout << "Please enter a valid choice ," << endl;
                        error = 1;
                        cin.clear();
                        cin.ignore(80, '\n');
                    }
                } while (error == 1);
                Rotate( Image(filePath),rotate,filePath);
                break;
            case 4:
                makeFrame( Image(filePath), filePath);
                break;
            case 5:
                makeBlure( Image(filePath),filePath);
                break;
            case 6:
                invert( Image(filePath),filePath);

                break;

            default:
                cout << "please enter valid input"; // no error
                break;



        }
    }

    return 0;



        }
