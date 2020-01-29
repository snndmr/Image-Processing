import cv2
from matplotlib import pyplot as plt

img = cv2.imread('img.jpg', 1)
plt.imshow(img, cmap='bone', interpolation='hermite')

# To hide tick values on X and Y axis
plt.xticks([]), plt.yticks([])
plt.show()
