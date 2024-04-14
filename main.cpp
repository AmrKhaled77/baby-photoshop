




#include "Image_Class.h"
#include <vector>

using namespace  std;


struct RGB{
    int red, green, blue;

};
string GlopalFilePath;

void  start(bool check);

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
        if (cin.fail()||choice<0||choice>2)
        {
            cout << "Please enter a valid choice ," << endl;
            error = 1;
            cin.clear();
            cin.ignore(80, '\n');
        }
    } while (error == 1);


    switch (choice) {
        case 1:
            try { image.saveImage(filePath); }
            catch (const exception& e)
            {  saveImage( image, filePath); }

            cout<<" done and file saved successfully"<<endl;
            system(filePath.c_str());
            GlopalFilePath=filePath;
            //start();
            break;
        case 2:
            string newPth;
            cout<<" please enter  new path  consider the extension  (.PNG , .JPEG, .bmp, .JPG, .tga )  : "<<endl;
            cin>>newPth;
            GlopalFilePath=newPth;
            try { image.saveImage(newPth); }
            catch (const std::exception& e)
            {
                cout<<"please enter valid image path"<<endl;
                saveImage( image, filePath); }

            cout<<" done and file saved successfully"<<endl;
            system(newPth.c_str());
            //start();
            break;

    }
    cout<<"(1)===> Continue in same filepath  "<<endl;
    cout<<"(2)===> Upload new photo "<<endl;
    cout<<"(0)===> exit "<<endl;
    do
    {
        error = 0;
        cout << " : ";
        cin >> choice; // Get the number of swaps from user
        if (cin.fail()||choice<0||choice>2)
        {
            cout << "Please enter a valid choice ," << endl;
            error = 1;
            cin.clear();
            cin.ignore(80, '\n');
        }
    } while (error == 1);
    if (choice==0) {
        cout<<"app end";
        exit(0);
    }
    if(choice==1){
        start(1);
    }
    else if(choice==2){
        start(0);
    }
}

void invert(Image image,string filePath ){
    int red,green,blue;

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

void Darken(Image image , string filepath)
{
    Image final(image.width,image.height);
    for(int i =0; i<image.width;i++)
    {
        for (int j=0;j<image.height;j++)
        {
            for(int k =0;k<3;k++)
            {
                int finalpixel=image(i,j,k)*0.5;
                finalpixel = min(max(finalpixel, 0), 255);
                final(i,j,k)=finalpixel;

            }
        }
    }
    saveImage(final,filepath);
}
void Lighten(Image image , string filepath)
{
    Image final(image.width,image.height);
    for(int i =0; i<image.width;i++)
    {
        for (int j=0;j<image.height;j++)
        {
            for(int k =0;k<3;k++)
            {
                int finalpixel=image(i,j,k)*1.5;
                finalpixel = min(max(finalpixel, 0), 255);
                final(i,j,k)=finalpixel;

            }
        }
    }
    saveImage(final,filepath);
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

void addFrame(Image image,string filePath,int color ,int fancy) {
    int frameWidth=image.width/97;
    int borderWidth=image.width/97;
    int cornerSize=60;

    vector<RGB> colors={
            {255, 0, 0},     // Red
            {0, 255, 0},     // Green
            {0, 0, 255},     // Blue
            {255, 255, 0},   // Yellow
            {0, 255, 255},   // Cyan
            {255, 165, 0},   // Orange
            {128, 0, 128},   // Purple
            {255, 192, 203}, // Pink
            {128, 128, 128}, // Gray
            {0, 0, 0}        // Black


    };
    // Add the frame

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            if (y < frameWidth || y >= image.height - frameWidth ||
                x < frameWidth || x >= image.width - frameWidth) {
                image(x, y, 0)=colors[color].red;
                image(x, y, 1)=colors[color].green;
                image(x, y, 2)=colors[color].blue;
            }
        }
    }

    if(fancy){
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

void detectedges(Image image, string filePath) {

    vector<vector<int>> neighborsMap(image.height, vector<int>(image.width, 0));
    for(int i = 1; i < image.width-1 ; i++) {
        for(int j = 1; j < image.height-1 ; j++) {

            int x = image(i + 1, j, 0) - image(i - 1, j, 0);
            int y = image(i, j + 1, 0) - image(i, j - 1, 0);
            neighborsMap[i][j] = sqrt(x * x + y * y);
        }
    }


    int threshold = 85;
    for(int i = 1; i < image.width - 1; i++) {
        for(int j = 1; j < image.height - 1; j++) {
            for(int k=0;k<3;k++){
                if (neighborsMap[i][j] > threshold) {

                    image(i, j, k) = 0;
                } else {

                    image(i, j, k) = 255;

                }
            }
        }
    }
    saveImage(image, filePath);
}


void verticalBlur(Image image,string filePath )
{


    int blur_concentration = 12;


    Image blurredImage(image.width, image.height);


    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            int red = 0, green = 0, blue = 0, count = 0;
            for (int i = max(0, y - blur_concentration); i < min(image.height, y + blur_concentration + 1); ++i) {
                red += image(x, i, 0);
                green += image(x, i, 1);
                blue += image(x, i, 2);
                ++count;
            }
            blurredImage(x, y, 0) = red / count;
            blurredImage(x, y, 1) = green / count;
            blurredImage(x, y, 2) = blue / count;
        }
    }


    saveImage(blurredImage,filePath);
}

void Blur(Image image,string filePath )
{


    int blur_concentration=12;


    Image blurredImage(image.width, image.height);

    for (int y = 0; y < image.height; ++y)
    {
        for (int x = 0; x < image.width; ++x) {
            int red = 0, green = 0, blue = 0, count = 0;
            for (int i = std::max(0, x - blur_concentration); i < std::min(image.width, x + blur_concentration + 1); ++i) {
                red += image(i, y, 0);
                green += image(i, y, 1);
                blue += image(i, y, 2);
                ++count;
            }
            blurredImage(x, y, 0) = red / count;
            blurredImage(x, y, 1) = green / count;
            blurredImage(x, y, 2) = blue / count;
        }
    }



    verticalBlur( blurredImage, filePath );

}

void Flip_Horiz(Image photo,string filePath)
{

    Image rotated_h(photo.width,photo.height);


    for(int i = 0; i < photo.width; ++i)
    {
        for(int j = 0; j < photo.height; ++j)
        {

            for(int k = 0; k < photo.channels; ++k)
            {
                rotated_h( i, j, k) = photo(photo.width-1-i, j, k);
            }
        }
    }

    saveImage(rotated_h,filePath);

}


void Flip_ver(Image photo,string filePath)
{

    Image rotated_ver(photo.width,photo.height);


    for(int i = 0; i < photo.width; ++i)
    {
        for(int j = 0; j < photo.height; ++j)
        {

            for(int k = 0; k < photo.channels; ++k)
            {
                rotated_ver( i, j, k) = photo(i, photo.height-1-j, k);
            }
        }
    }

    saveImage(rotated_ver,filePath);

}


void resize(Image photo,string filepath)
{
    int x,y;
    double m;
    double n;
    cout<<"Enter the new dimensions: ";
    cin>>x>>y;
    Image neew(x,y);

    m=(photo.width/x);
    n=(photo.height/y);

    for(int i=0;i<neew.width;++i)
    {
        for(int j=0;j<neew.height;++j)
        {
            for(int k=0;k<neew.channels;++k)
            {
                neew(i,j,k)= photo(round(i*m),round(j*n),k);
            }
        }
    }

    saveImage(neew,filepath);

}

void crop(Image image,string filepath)
{
    int x,y;
    cout<<"Enter the starting points:";
    cin>>x>>y;

    int l,o;
    cout<<"Enter the new dimensions: ";
    cin>>l>>o;
    Image cropped(l,o);

    for(int i=x;i<l+x;++i)
    {
        for(int j=y;j<o+y;++j)
        {
            for(int k=0;k<image.channels;++k)
            {
                cropped(i-x,j-y,k)=image(i,j,k);
            }
        }

    }

    saveImage(cropped,filepath);


}

void adjust_warm(Image image, string filePath) {
    const int redIncrease = 35;
    const int greenIncrease = 50;

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {

            int newRed = min(image(i, j, 0) + redIncrease, 255);
            int newGreen = min(image(i, j, 1) + (greenIncrease), 255);
            // Apply the new red and green values to the image
            image(i, j, 0) = newRed;
            image(i, j, 1) = newGreen;
        }
    }
    saveImage(image, filePath);
}
void purp(Image image, string filePath)
{



    for(int i =0; i < image.width; ++i)
    {
        for(int j=0; j < image.height; ++j)
        {
            for(int k=0; k < image.channels; ++k)
            {
                // image(i,j,0)= image(i,j,0)*2;
                image(i, j, 1)= image(i, j, 1) * 0.9;
                // image(i,j,2)=image(i,j,2)*1.9;
            }
        }
    }

    saveImage(image, filePath);
}
void infrared(Image image,string filePath) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            // Get the pixel value at (x, y)




            image(x, y, 0) = 230;
            image(x, y, 1) = 255 - (image(x, y, (1)));
            image(x, y, 2) = 255 - (image(x, y, (2)));


        }
    }
    saveImage(image,filePath);
}



void start(bool check=0){

    if(check==0){

        cout<<"Welcome"<<endl;
        cout<<"Enter file path:";
        cin >> GlopalFilePath;

        try { Image image(GlopalFilePath); }
        catch (const std::exception& e)
        { start(); }
    }

    while (true){




        int choose;
        string image2="";
        cout<<"please select what you want to do  "<<endl;
        cout<<"(1)===>Invert Image "<<endl;
        cout<<"(2)===> Rotate Image "<<endl;
        cout<<"(3)===> Blur Images "<<endl;
        cout<<"(4)===> Adding a Frame to the Picture "<<endl;
        cout<<"(5)===> Black and White "<<endl;
        cout<<"(6)===> Grayscale Conversion "<<endl;
        cout<<"(7)===>Merg "<<endl;
        cout<<"(8)===> Darken or Lighten" <<endl;
        cout<<"(9)===> detect image edges" <<endl;
        cout<<"(10)===>Flip image " <<endl;
        cout<<"(11)===> resize  image " <<endl;
        cout<<"(12)===> Crop image " <<endl;
        cout<<"(13)===> Adjust warmth"<<endl;
        cout<<"(14)===> Purple "<<endl;
        cout<<"(15)===> Infrared "<<endl;
        cout<<"(0)===> exit "<<endl;

        int error;
        do
        {
            error = 0;
            cout << " : ";
            cin >> choose;
            if (cin.fail()||choose<0||choose>15)
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
                invert(Image(GlopalFilePath), GlopalFilePath);


                break;
            case 2:
                int error;
                int rotate;
                do
                {
                    error = 0;
                    cout << " 90,180 or 270 degree : ";
                    cin >> rotate;
                    if (cin.fail()||(rotate!=90&&rotate!=270&&rotate!=180))
                    {
                        cout << "Please enter a valid choice ," << endl;
                        error = 1;
                        cin.clear();
                        cin.ignore(80, '\n');
                    }
                } while (error == 1);
                cout<<"please wait while your image is processing ......"<<endl;
                Rotate(Image(GlopalFilePath), rotate, GlopalFilePath);

                break;
            case 3:

                cout<<"please wait while your image is processing ......"<<endl;
                Blur(Image(GlopalFilePath), GlopalFilePath);


                break;
            case 4:
                int ERorr;
                int fancy;
                do
                {
                    ERorr = 0;
                    cout<<"please choose what you want : \n"
                          "(1)===> regular \n(2)===> fancy\n";

                    cin >> fancy;
                    if (cin.fail()||fancy<0||fancy>2)
                    {
                        cout << "Please enter a valid choice ," << endl;
                        ERorr = 1;
                        cin.clear();
                        cin.ignore(80, '\n');
                    }
                } while (ERorr == 1);


                int Error;
                int color;
                do
                {
                    Error = 0;
                    cout<<"please choose color you want : \n"
                          "(1)===> Red \n(2)===> Green\n(3)===>Blue \n(4)===> Yellow\n(5)===>Cyan \n"
                          "(6)===> Orange\n(7)===> Purple\n(8)===> Pink\n(9)===> Gray\n(10)===> Black\n";

                    cin >> color;
                    if (cin.fail()||color<0||color>10)
                    {
                        cout << "Please enter a valid choice ," << endl;
                        Error = 1;
                        cin.clear();
                        cin.ignore(80, '\n');
                    }
                } while (error == 1);


                cout<<"please wait while your image is processing ......"<<endl;
                addFrame(Image(GlopalFilePath), GlopalFilePath, color - 1, fancy - 1);

                break;
            case 5:
                cout<<"please wait while your image is processing ......"<<endl;
                b_w(Image(GlopalFilePath), GlopalFilePath);
                break;
            case 6:

                cout<<"please wait while your image is processing ......"<<endl;
                grayscale(Image(GlopalFilePath), GlopalFilePath);
                break;
            case 7:

                cout<<"please enter path of second image : "<<endl;

                cin>>image2;
                cout<<"please wait while your image is processing ......"<<endl;
                Merg(Image(GlopalFilePath), Image(image2), GlopalFilePath);

                break;
            case 8:
                int choice;
                cout<<"(1)Darken \n(2)Lighten"<<endl;
                cin >>choice;

                cout<<"please wait while your image is processing ......"<<endl;
                if(choice==1){
                    Darken(Image(GlopalFilePath), GlopalFilePath);
                }
                else{
                    Lighten(Image(GlopalFilePath), GlopalFilePath);
                }
                break;
            case 9:
                cout<<"please wait while your image is processing ......"<<endl;
                detectedges(Image(GlopalFilePath), GlopalFilePath);
                break;

            case 10:
                int num;
                cout<<"(1)Flip horizontal"<<endl;
                cout<<"(2)Flip virtecal"<<endl;
                cin>>num;
                if(num==1)
                {
                    cout<<"please wait while your image is processing ......"<<endl;
                    Flip_Horiz(Image(GlopalFilePath), GlopalFilePath);

                }
                else
                {
                    cout<<"please wait while your image is processing ......"<<endl;
                    Flip_ver(Image(GlopalFilePath), GlopalFilePath);
                }
                break;





            case 11:
                cout<<"please wait while your image is processing ......"<<endl;
                resize(Image(GlopalFilePath), GlopalFilePath);
                break;


            case 12:
                cout<<"please wait while your image is processing ......"<<endl;
                crop(Image(GlopalFilePath), GlopalFilePath);
                break;
            case 13:
                cout<<"please wait while your image is processing ......"<<endl;
                adjust_warm(Image(GlopalFilePath), GlopalFilePath);
                break;
            case 14:
                cout<<"please wait while your image is processing ......"<<endl;
                purp(Image(GlopalFilePath), GlopalFilePath);
            case 15:
                cout<<"please wait while your image is processing ......"<<endl;
                infrared(Image(GlopalFilePath), GlopalFilePath);



            default:
                cout << "please enter valid input"; // no error
                break;



        }
    }

}

int main()
{

    start();

    return 0;


}