import numpy as np
import cv2

# Create a black image
img = np.zeros((512, 512, 3), np.uint8)  # 512 Array, W : 3 | H : 512

# Draw a diagonal blue line with thickness of 5 px
line = cv2.line(img, (0, 0), (511, 511), (255, 0, 0), 5)

# To draw a rectangle
rect = cv2.rectangle(img, (128, 128), (384, 384), (0, 255, 0), 5)  # -1 : Fill, 0 : Rect, 0+ : Thickness

# To draw a circle
circle = cv2.circle(img, (256, 256), 50, (0, 0, 255), -1)  # -1 : Fill, 0 : Circle, 0+ : Thickness

# To draw a ellipse
ellipse = cv2.ellipse(img, (256, 256), (200, 100), 0, 45, 225, (0, 255, 255), 4, cv2.CV_8UC1)

# To write something
font = cv2.FONT_HERSHEY_SIMPLEX
# img, pos, font, font size, color, thickness, type
cv2.putText(img, 'Hi!', (220, 280), font, 2, (255, 255, 255), 2, cv2.LINE_AA)

cv2.imshow('img', img)
cv2.imshow('img', line)
cv2.imshow('img', rect)
cv2.imshow('img', circle)
cv2.imshow('img', ellipse)

cv2.waitKey(0)
cv2.destroyAllWindows()
