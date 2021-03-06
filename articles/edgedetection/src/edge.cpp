// g++ edge.cpp -o edge `pkg-config --cflags --libs opencv`

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