[BACK](https://mcarletti.github.io/)

*Last update: October 23th, 2018*

# Compute the normals of a surface from a depth image

I was searching for an embedding in order to map a depth image (`uint16-1ch`) into an RGB image (`uint8-3ch`) and I found an [interesting discussion on StackOverflow](http://answers.opencv.org/question/82453/calculate-surface-normals-from-depth-image-using-neighboring-pixels-cross-product/) about how to extract normal information from a single depth (grayscale) image in OpenCV. I have to give credits to the authors of these methods I simply put together into a single cpp file.

<center>
<img alt="depthimage" src="src/depth.png" width="300">
<img alt="jetmapembedding" src="src/jetmapembedding.png" width="300">

<img alt="convnormals" src="src/conv_normals.png" width="300">
<img alt="crossnormals" src="src/cross_normals.png" width="300">
</center>

The key idea of these methods is to analyze the cross product of the neighborhood of a pixel.
The last method I put in the code (*jetmap*) is actually a method to embed the depth information to a different domain, in this case the jetmap colormap.

The source code is available [here](src/depth2normals.cpp) and is also reported in the following block. Instructions about compilation and execution at the end of the page.

```cpp
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    // check input
    if (argc != 3)
    {
        cout << endl;
        cout << "DEPTH2NORMALS" << endl;
        cout << "Compute the normals of a grayscale/depth image." << endl;
        cout << endl;
        cout << "Usage:" << endl;
        cout <<"\t./depth2normals FILE MODE" << endl;
        cout << endl;
        cout << "FILE: grayscale/depth image path with extension" << endl;
        cout << "MODE: method to compute the normals; must be in [conv, cross, crossfast, jetmap]" << endl;
        cout << endl;

        return -1;
    }
    
    string FILE(argv[1]);
    string MODE(argv[2]);

    // load image as grayscale and convert to 32 bits (single channel)
    Mat depth = cv::imread(FILE);
    cvtColor(depth, depth, CV_RGB2GRAY);
    depth.convertTo(depth, CV_32FC1);

    if (MODE == "conv")
    {
        // Shape, Illumination, and Reflectance from Shading
        // Jonathan T. Barron (https://jonbarron.info/), Jitendra Malik 
        // IEEE Transactions on Pattern Analysis and Machine Intelligence (TPAMI), 2015 
        // https://drive.google.com/file/d/1RvyCiDMg--jyO8lLBvopp0o271LvREoa/view

        // filters
        Mat_<float> f1 = (Mat_<float>(3, 3) << 1,  2,  1,
                                                0,  0,  0,
                                                -1, -2, -1) / 8;

        Mat_<float> f2 = (Mat_<float>(3, 3) << 1, 0, -1,
                                                2, 0, -2,
                                                1, 0, -1) / 8;

        /* Other filters that could be used:
        % f1 = [0, 0, 0;
        %       0, 1, 1;
        %       0,-1,-1]/4;
        % 
        % f2 = [0, 0, 0;
        %       0, 1,-1;
        %       0, 1,-1]/4;

        or

        % f1 = [0, 1, 0;
        %       0, 0, 0;
        %       0,-1, 0]/2;
        % 
        % f2 = [0, 0, 0;
        %       1, 0, -1;
        %       0, 0, 0]/2;
        */


        Mat f1m, f2m;
        flip(f1, f1m, 0);
        flip(f2, f2m, 1);

        Mat n1, n2;
        filter2D(depth, n1, -1, f1m, Point(-1, -1), 0, BORDER_CONSTANT);
        filter2D(depth, n2, -1, f2m, Point(-1, -1), 0, BORDER_CONSTANT);

        n1 *= -1;
        n2 *= -1;

        Mat temp = n1.mul(n1) + n2.mul(n2) + 1;
        cv::sqrt(temp, temp);

        Mat N3 = 1 / temp;
        Mat N1 = n1.mul(N3);
        Mat N2 = n2.mul(N3);

        vector<Mat> N;
        N.push_back(N1);
        N.push_back(N2);
        N.push_back(N3);

        Mat normals;
        merge(N, normals);

        imshow("convolution_based_normals", normals);
        normals *= 255;
        normals.convertTo(normals, CV_8UC3);
        imwrite("conv_normals.png", normals);
    }
    else if (MODE == "cross")
    {
        Mat normals(depth.size(), CV_32FC3);

        for(int x = 0; x < depth.cols; ++x)
        {
            for(int y = 0; y < depth.rows; ++y)
            {
                    // 3d pixels, think (x,y, depth)
                    /* * * * *
                    * * t * *
                    * l c * *
                    * * * * */

                Vec3f t(x,y-1,depth.at<float>(y-1, x));
                Vec3f l(x-1,y,depth.at<float>(y, x-1));
                Vec3f c(x,y,depth.at<float>(y, x));

                Vec3f d = (l-c).cross(t-c);

                Vec3f n = normalize(d);
                normals.at<Vec3f>(y,x) = n;
            }
        }

        imshow("explicitly cross_product normals", normals);
        normals *= 255;
        normals.convertTo(normals, CV_8UC3);
        imwrite("cross_normals.png", normals);
    }   
    else if (MODE == "crossfast")
    {
        Mat normals(depth.size(), CV_32FC3);

        for(int x = 0; x < depth.rows; ++x)
        {
            for(int y = 0; y < depth.cols; ++y)
            {
                // use float instead of double otherwise you will not get the correct result
                // check my updates in the original post. I have not figure out yet why this
                // is happening.
                float dzdx = (depth.at<float>(x+1, y) - depth.at<float>(x-1, y)) / 2.0;
                float dzdy = (depth.at<float>(x, y+1) - depth.at<float>(x, y-1)) / 2.0;

                Vec3f d(-dzdx, -dzdy, 1.0f);

                Vec3f n = normalize(d);
                normals.at<Vec3f>(x, y) = n;
            }
        }

        imshow("fast cross_product normals", normals);
        normals *= 255;
        normals.convertTo(normals, CV_8UC3);
        imwrite("crossfast_normals.png", normals);
    }
    else if (MODE == "jetmap")
    {
        // Multimodal Deep Learning for Robust RGB-D Object Recognition
        // Andreas Eitel, Jost Tobias Springenberg, Luciano Spinello, Martin Riedmiller, Wolfram Burgard
        // https://ieeexplore.ieee.org/abstract/document/7353446

        depth.convertTo(depth, CV_8UC1);
        Mat embedding(depth.size(), CV_8UC3);

        applyColorMap(depth, embedding, COLORMAP_JET);

        imshow("depth information to jet colormap", embedding);
        imwrite("jetmapembedding.png", embedding);
    } 

    waitKey(0);

    return 0;
}
```

Compile:
```
g++ depth2normals.cpp -o depth2normals `pkg-config --cflags --libs opencv`
```

Example:
```
./depth2normals depth.png cross
```
