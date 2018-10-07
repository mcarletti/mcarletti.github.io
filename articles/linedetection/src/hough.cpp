// g++ edge.cpp -o edge `pkg-config --cflags --libs opencv`

#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <cassert>

int main(void)
{
	// load image
	std::string filename = "house.png";
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

	// estimate lines with hoygh transform
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(edges, lines, 1, 3.14 / 180, 80);

	// draw lines on a copy of the original image
	if (!lines.empty())
	{
		image = image_orig.clone();
		for (unsigned int i = 0; i < lines.size(); ++i)
		{
			float rho = lines[i][0];
			float theta = lines[i][1];
			cv::Point pt1, pt2;
			double a = std::cos(theta), b = std::sin(theta);
			double x0 = a*rho, y0 = b*rho;
			pt1.x = int(x0 + 1000*(-b));
			pt1.y = int(y0 + 1000*(a));
			pt2.x = int(x0 - 1000*(-b));
			pt2.y = int(y0 - 1000*(a));
			cv::line(image, pt1, pt2, cv::Scalar(255,0,0), 2, cv::LINE_AA);
		}
	}

	// visualize image
	cv::imshow("image", image);
	cv::imshow("edges", edges);
	cv::waitKey(0);

	cv::destroyAllWindows();

    // save image
	cv::imwrite("lines.png", image);
    cv::imwrite("edges.png", edges);

	return 0;
}