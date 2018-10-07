import cv2
import math

if __name__ == '__main__':

	# load image
	filename = 'house.png'
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

	# estimate lines with hoygh transform
	lines = cv2.HoughLines(edges, 1, 3.14 / 180, 80)

	# draw lines on a copy of the original image
	if lines is not None:
		image = image_orig.copy()
		for line in lines:
			rho = line[0][0]
			theta = line[0][1]
			a = math.cos(theta)
			b = math.sin(theta)
			x0 = a * rho
			y0 = b * rho
			pt1 = (int(x0 + 1000*(-b)), int(y0 + 1000*(a)))
			pt2 = (int(x0 - 1000*(-b)), int(y0 - 1000*(a)))
			cv2.line(image, pt1, pt2, (255,0,0), 2, cv2.LINE_AA)

	# visualize image
	cv2.imshow('image', image)
	cv2.imshow('edges', edges)
	cv2.waitKey(0)

	cv2.destroyAllWindows()

	# save images
	cv2.imwrite('lines.png', image)
	cv2.imwrite('edges.png', edges)
