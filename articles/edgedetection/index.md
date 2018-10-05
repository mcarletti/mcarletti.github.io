# Edge detection

Edge detection includes a variety of mathematical methods that aim at identifying points in a digital image at which the image brightness changes sharply or, more formally, has discontinuities. The points at which image brightness changes sharply are typically organized into a set of curved line segments termed edges.

The purpose of detecting sharp changes in image brightness is to capture important events and changes in properties of the world.

There are many methods for edge detection. This article treats the *Canny edge detector* and shows how to use the OpenCV implementation both in Python and C++.

## Canny edge detector

The Canny edge detector is an edge detection operator that uses a multi-stage algorithm to detect a wide range of edges in images. It was developed by John F. Canny in 1986. Canny also produced a computational theory of edge detection explaining why the technique works.

The Process of Canny edge detection algorithm can be broken down to 5 different steps:

1. Apply Gaussian filter to smooth the image in order to remove the noise
1. Find the intensity gradients of the image
1. Apply non-maximum suppression to get rid of spurious response to edge detection
1. Apply double threshold to determine potential edges
1. Track edge by hysteresis: Finalize the detection of edges by suppressing all the other edges that are weak and not connected to strong edges.

Source: Wikipedia


# Code

<center>
<img src="src/lena_color_512.png" alt="image" width="300"/>
<img src="src/edges.png" alt="edges" width="300"/>
</center>


### Python

```python
import cv2

if __name__ == '__main__':

    # load image
    filename = 'lena_color_512.tif'
    image_orig = cv2.imread(filename)
    if image_orig is None:
        print('Cannot find or load image:', filename)
        quit(-1)

    image = image_orig.copy()

    # convert image to grayscale
    if len(image.shape) > 2 and image.shape[-1] >= 3:
        image = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)

    # apply canny edge detector
    edges = cv2.Canny(image, 92, 128)

    # visualize image
    cv2.imshow('image', image_orig)
    cv2.imshow('edges', edges)
    cv2.waitKey(0)

    cv2.destroyAllWindows()

    # save image
    cv2.imwrite('edges.png', edges)
```

### C++

```cpp
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <cassert>

int main(void)
{
    // load image
    std::string filename = "lena_color_512.png";
    cv::Mat image_orig = cv::imread(filename);
    if (image_orig.empty())
    {
        std::cout << "Cannot find or load image: " << filename << std::endl;
        return -1;
    }

    cv::Mat image = image_orig.clone();

    // convert image to grayscale
    if (image.channels() > 1)
        cv::cvtColor(image_orig, image, cv::COLOR_RGB2GRAY);

    // apply canny edge detector
    cv::Mat edges;
    cv::Canny(image, edges, 92, 128);

    // visualize image
    cv::imshow("image", image_orig);
    cv::imshow("edges", edges);
    cv::waitKey(0);

    cv::destroyAllWindows();

    // save image
    cv::imwrite("edges.png", edges);

    return 0;
}
```

To compile, use the following command:

```
g++ edge.cpp -o edge `pkg-config --cflags --libs opencv`
```