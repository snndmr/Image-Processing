import cv2

#  1 : Loads a color image. Any transparency of image will be neglected. It is the default flag.
#  0 : Loads image in grayscale mode
# -1 : Loads image as such including alpha channel
img = cv2.imread('img.jpg', 1)

# To display an image in a window. The window automatically fits to the image size.
cv2.imshow('img', img)
# If you press any key in that time, the program continues. If 0 is passed, it waits indefinitely for a key stroke.
cv2.waitKey(0)
# To destroy all windows.
cv2.destroyAllWindows()

# To save an image
cv2.imwrite('img.png', img)
