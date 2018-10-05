# Edge detection

Edge detection includes a variety of mathematical methods that aim at identifying points in a digital image at which the image brightness changes sharply or, more formally, has discontinuities. The points at which image brightness changes sharply are typically organized into a set of curved line segments termed edges.

The purpose of detecting sharp changes in image brightness is to capture important events and changes in properties of the world.

There are many methods for edge detection. This article treats the *Canny edge detector*.


## Canny edge detector

The Canny edge detector is an edge detection operator that uses a multi-stage algorithm to detect a wide range of edges in images. It was developed by John F. Canny in 1986. Canny also produced a computational theory of edge detection explaining why the technique works.

The Process of Canny edge detection algorithm can be broken down to 5 different steps:

1. Apply Gaussian filter to smooth the image in order to remove the noise
1. Find the intensity gradients of the image
1. Apply non-maximum suppression to get rid of spurious response to edge detection
1. Apply double threshold to determine potential edges
1. Track edge by hysteresis: Finalize the detection of edges by suppressing all the other edges that are weak and not connected to strong edges.

Source: Wikipedia