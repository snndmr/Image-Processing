import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('bird.jpg')

sBlur = 11
# # 2D Convolution ( Image Filtering )
# kernel = np.ones((sBlur, sBlur), np.float32) / sBlur ** 2
# res = cv2.filter2D(img, -1, kernel)

# Averaging
blur = cv2.blur(img, (sBlur, sBlur))

# Gaussian
blurGaussian = cv2.GaussianBlur(img, (sBlur, sBlur), 0)

# Median
median = cv2.medianBlur(img, sBlur)

# Bilateral
blurBilateral = cv2.bilateralFilter(img, 9, 75, 75)

plt.subplot(332), plt.imshow(img), plt.title('Original'), plt.xticks([]), plt.yticks([])
# plt.subplot(132), plt.imshow(res), plt.title('Averaging'), plt.xticks([]), plt.yticks([])
plt.subplot(334), plt.imshow(blur), plt.title('Blurred'), plt.xticks([]), plt.yticks([])
plt.subplot(336), plt.imshow(blurGaussian), plt.title('Gaussian Blur'), plt.xticks([]), plt.yticks([])
plt.subplot(337), plt.imshow(median), plt.title('Median Blur'), plt.xticks([]), plt.yticks([])
plt.subplot(339), plt.imshow(blurBilateral), plt.title('Bilateral Blur'), plt.xticks([]), plt.yticks([])
plt.show()
