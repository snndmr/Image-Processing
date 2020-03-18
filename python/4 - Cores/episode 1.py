import cv2
from matplotlib import pyplot as plt
import numpy as np

img = cv2.imread("img.jpg")
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# px = img[100, 100]
# print(px)

# blue = img[100, 100, 0]
# print(blue)

# home = img[100:275, 550:975]
# img[400:575, 350:775] = home
#
# plt.imshow(img, cmap='bone', interpolation='hermite')
# plt.show()

img[img > 155] = 0
plt.imshow(img, cmap='bone', interpolation='hermite')
plt.show()
