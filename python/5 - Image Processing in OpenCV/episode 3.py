import cv2
import numpy as np

img = cv2.imread('bird.jpg')

# Scaling
res = cv2.resize(img, None, fx=.5, fy=.5, interpolation=cv2.INTER_CUBIC)

# Translation
rows, cols, size = res.shape
M = np.float32([[1, 0, 25], [0, 1, 12.5]])
dst = cv2.warpAffine(img, M, (cols, rows))

# Rotation
rows, cols, _ = dst.shape
M = cv2.getRotationMatrix2D((cols / 2, rows / 2), 90, 1)
rt = cv2.warpAffine(img, M, (cols, rows))

cv2.imshow('img', rt)
cv2.waitKey(0)
cv2.destroyAllWindows()
