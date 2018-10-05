import cv2

if __name__ == '__main__':

	# load image
	filename = '../../../shared/images/lena_color_512.tif'
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
