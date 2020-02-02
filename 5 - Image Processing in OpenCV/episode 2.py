import cv2
from matplotlib import pyplot as plt

# img = cv2.imread('gradient.jpg', 0)
# a, thresh1 = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)
# b, thresh2 = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY_INV)
# c, thresh3 = cv2.threshold(img, 127, 255, cv2.THRESH_TRUNC)
# d, thresh4 = cv2.threshold(img, 127, 255, cv2.THRESH_TOZERO)
# e, thresh5 = cv2.threshold(img, 127, 255, cv2.THRESH_TOZERO_INV)
#
# titles = ['Original Image', 'BINARY', 'BINARY_INV', 'TRUNC', 'TOZERO', 'TOZERO_INV']
# images = [img, thresh1, thresh2, thresh3, thresh4, thresh5]
#
# for i in range(6):
#     plt.subplot(2, 3, i + 1), plt.imshow(images[i], 'gray')
#     plt.title(titles[i])
#     plt.xticks([]), plt.yticks([])
#
# plt.show()

import cv2
from matplotlib import pyplot as plt

img = cv2.imread('bird.jpg', 0)
img = cv2.medianBlur(img, 5)

ret, th1 = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)
th2 = cv2.adaptiveThreshold(img, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 2)
th3 = cv2.adaptiveThreshold(img, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 2)

titles = ['Original Image', 'Global Thresholding (v = 127)', 'Adaptive Mean Thresholding',
          'Adaptive Gaussian Thresholding']
images = [img, th1, th2, th3]

for i in range(4):
    plt.subplot(2, 2, i + 1), plt.imshow(images[i], 'gray')
    plt.title(titles[i])
    plt.xticks([]), plt.yticks([])
plt.show()
