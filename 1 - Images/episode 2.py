import cv2
from matplotlib import pyplot as plt

img = cv2.imread('img.jpg', 1)

# OpenCV follows BGR order, while matplotlib likely follows RGB order.
# So, we need conversion between BGR and RGB.
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)  # img = img[:, :, ::-1]

plt.imshow(img, cmap='bone', interpolation='hermite')

# To hide tick values on X and Y axis
plt.xticks([]), plt.yticks([])
plt.show()
