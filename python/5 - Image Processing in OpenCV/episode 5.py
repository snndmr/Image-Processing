import cv2
import numpy as np
import matplotlib.pyplot as plt

imgOne = cv2.imread('j.png', 0)
imgOne = cv2.cvtColor(imgOne, cv2.COLOR_BGR2RGB)

# Kernel
kernel = np.ones((5, 5), np.uint8)

# Erosion
# It is useful for removing small white noises
erosion = cv2.erode(imgOne, kernel, iterations=1)

# Dilation
# It is also useful in joining broken parts of an object.
dilation = cv2.dilate(imgOne, kernel, iterations=1)

imgTwo = cv2.imread('jnoise.png', 0)
imgTwo = cv2.cvtColor(imgTwo, cv2.COLOR_BGR2RGB)

# Opening
# Erosion followed by dilation. It is useful in removing noise
opening = cv2.morphologyEx(imgTwo, cv2.MORPH_OPEN, kernel)

imgThr = cv2.imread('jholes.png', 0)
imgThr = cv2.cvtColor(imgThr, cv2.COLOR_BGR2RGB)

# Closing
# It is useful in closing small holes inside the foreground objects
closing = cv2.morphologyEx(imgThr, cv2.MORPH_CLOSE, kernel)

# Morphological Gradient
# The result will look like the outline of the object.
gradient = cv2.morphologyEx(imgOne, cv2.MORPH_GRADIENT, kernel)

# Top Hat
tophat = cv2.morphologyEx(imgOne, cv2.MORPH_TOPHAT, kernel)

# Black Hat
blackhat = cv2.morphologyEx(imgOne, cv2.MORPH_BLACKHAT, kernel)

plt.subplot2grid((4, 4), (0, 0)), plt.title("Original"), plt.imshow(imgOne), plt.xticks([]), plt.yticks([])
plt.subplot2grid((4, 4), (0, 1)), plt.title("Erosion"), plt.imshow(erosion), plt.xticks([]), plt.yticks([])
plt.subplot2grid((4, 4), (0, 2)), plt.title("Dilation"), plt.imshow(dilation), plt.xticks([]), plt.yticks([])
plt.subplot2grid((4, 4), (1, 0)), plt.title("Original"), plt.imshow(imgTwo), plt.xticks([]), plt.yticks([])
plt.subplot2grid((4, 4), (1, 1)), plt.title("Opening"), plt.imshow(opening), plt.xticks([]), plt.yticks([])
plt.subplot2grid((4, 4), (2, 0)), plt.title("Original"), plt.imshow(imgThr), plt.xticks([]), plt.yticks([])
plt.subplot2grid((4, 4), (2, 1)), plt.title("Closing"), plt.imshow(closing), plt.xticks([]), plt.yticks([])
plt.subplot2grid((4, 4), (3, 0)), plt.title("Original"), plt.imshow(imgOne), plt.xticks([]), plt.yticks([])
plt.subplot2grid((4, 4), (3, 1)), plt.title("Morphological Gr."), plt.imshow(gradient), plt.xticks([]), plt.yticks([])
plt.subplot2grid((4, 4), (3, 2)), plt.title("Tophat"), plt.imshow(tophat), plt.xticks([]), plt.yticks([])
plt.subplot2grid((4, 4), (3, 3)), plt.title("Blackhat"), plt.imshow(blackhat), plt.xticks([]), plt.yticks([])
plt.show()
