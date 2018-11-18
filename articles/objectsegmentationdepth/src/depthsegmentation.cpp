// HOW TO COMPILE
// g++ depthsegmentation.cpp -o depthsegmentation `pkg-config --cflags --libs opencv`
//
// EXAMPLE
// ./depthsegmentation depth.png

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace cv;

void help()
{
        cout << endl;
        cout << "DEPTHSEGMENTATION" << endl;
        cout << "Segment an object from a grayscale/depth image." << endl;
        cout << endl;
        cout << "Usage:" << endl;
        cout <<"\t./depthsegmentation FILE [V1 V2] [U V]" << endl;
        cout << endl;
        cout << "FILE: grayscale/depth image path with extension" << endl;
        cout << "V1:   [optional; default: double(20)] loDiff" << endl;
        cout << "V2:   [optional; default: double(20)] upDiff" << endl;
        cout << "U:    [optional; default: int(imwidth/2)] seed horizontal value" << endl;
        cout << "V:    [optional; default: int(imheight/2)] seed vertical value" << endl;
        cout << endl;
}

int main(int argc, char* argv[])
{
    if (argc != 2 && argc != 4 && argc != 6)
    {
        std::cout << "ERROR: Invalid number of parameters" << std::endl;
        help();
        return -1;
    }
    
    string FILE(argv[1]);

    Mat depth = imread(FILE, -1);

    if (depth.channels() == 4)
    {
        Mat channels[4];
        split(depth, channels);
        merge(channels, 3, depth);
    }

    if (depth.channels() == 3)
        cvtColor(depth, depth, COLOR_BGR2GRAY);

    depth.convertTo(depth, CV_32FC1);
    normalize(depth, depth, 0, 255, NORM_MINMAX);
    depth.convertTo(depth, CV_8UC1);
    
    int width = depth.cols;
    int height = depth.rows;

    double V1 = 20.f;
    double V2 = 20.f;
    int U = int(width / 2);
    int V = int(height / 2);

    try
    {
        switch(argc)
        {
            case 2:
                break;
            case 4:
                V1 = stod(argv[2]);
                V2 = stod(argv[3]);
                break;
            case 6:
                U = stoi(argv[4]);
                V = stoi(argv[5]);
                break;
            default:
                throw invalid_argument("EXCEPTION: Invalid number of parameters");
                break;
        }

        if (U < 0 || U > height || V < 0 || V > width)
            throw invalid_argument("EXCEPTION: Invalid seed coordinates");
    }
    catch(const logic_error& ex)
    {
        std::cout << "EXCEPTION: Cannot convert parameters" << std::endl;
        std::cout << ex.what() << std::endl;
        help();
        return -2;
    }
    catch(const invalid_argument& ex)
    {
        std::cout << ex.what() << std::endl;
        help();
        return -3;
    }
    catch(...)
    {
        std::cout << "EXCEPTION: Unknown exception" << std::endl;
        return -4;
    }
    
    Point2i seed;
    seed.x = U;
    seed.y = V;

    Mat mask;
    Canny(depth, mask, 0, 255);
    copyMakeBorder(mask, mask, 1, 1, 1, 1, BORDER_REPLICATE);
    unsigned char fillValue = 128.f;
    floodFill(depth, mask, seed, Scalar(128), nullptr, Scalar(V1), Scalar(V2), 4 | cv::FLOODFILL_MASK_ONLY | (fillValue << 8));
    resize(mask, mask, depth.size());

    cvtColor(mask, mask, CV_GRAY2RGB);
    cvtColor(depth, depth, CV_GRAY2RGB);
    circle(depth, seed, 2, Scalar(0,0,255), 3);

    Mat dst;
    hconcat(depth, mask, dst);
    imshow("image - mask", dst);

    imwrite("depth_seed.png", depth);
    imwrite("mask.png", mask);

    waitKey(0);

    return 0;
}
