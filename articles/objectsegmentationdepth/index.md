[BACK](https://mcarletti.github.io/)

*Last update: November 18th, 2018*

# Depth segmentation

TODO


# Code

<center>
<img src="src/depth_seed.png" alt="image" width="300"/>
<img src="src/mask.png" alt="image" width="300"/><br>
<i>The red dot is the seed from which the segmentation has started.</i>
</center>

Assuming to have CV_8UC1 image (`depth`) which values are normalized between 0 and 255, we define the parameter for the segmentation stage:

```cpp
int width = depth.cols;
int height = depth.rows;

// used by the region growing algorithm
double V1 = 20.f;
double V2 = 20.f;

// position of the seed
int U = int(width / 2);
int V = int(height / 2);
```

Then, the segmentation is done using the floodFill algorithm:

<center>
<img src="floodFill.gif" alt="image" width="150"/>
</center>

```cpp
cv::Point2i seed;
seed.x = U;
seed.y = V;

cv::Mat mask;

// extract the edged
cv::Canny(depth, mask, 0, 255);
cv::copyMakeBorder(mask, mask, 1, 1, 1, 1, cv::BORDER_REPLICATE);
unsigned char fillValue = 128.f;

// fill the areas in which the seed is located
floodFill(depth, mask, seed, cv::Scalar(128), nullptr, cv::Scalar(V1), cv::Scalar(V2), 4 | cv::FLOODFILL_MASK_ONLY | (fillValue << 8));
cv::resize(mask, mask, depth.size());
```

Enjoy :)

To compile, use the following command:

```
g++ depthsegmentation.cpp -o depthsegmentation `pkg-config --cflags --libs opencv`
```

Example:
```
./depthsegmentation depth.png
```

## Download

* [depthsegmentation.cpp](src/depthsegmentation.cpp)
* [depth.png](src/depth.png)
