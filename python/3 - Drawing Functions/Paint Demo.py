import cv2
import numpy as np

isPaint = False
RGB = [255, 255, 255]


def nothing(x):
    pass


# mouse callback function
def draw_circle(event, x, y, flags, param):
    global isPaint
    global RGB

    if isPaint:
        cv2.circle(img, (x, y), size, (RGB[0], RGB[1], RGB[2]), typeCircle)

    if event == cv2.EVENT_LBUTTONDOWN:
        isPaint = True
    elif event == cv2.EVENT_LBUTTONUP:
        isPaint = False


# Create a black image, a window and bind the function to window
img = np.zeros((480, 640, 3), np.uint8)
cv2.namedWindow('Paint')
cv2.setMouseCallback('Paint', draw_circle)

# Creating settings frame
settings = np.zeros((1, 320, 3), np.uint8)
cv2.namedWindow('Settings')

# To change color # Slider
cv2.createTrackbar('R', 'Settings', 255, 255, nothing)
cv2.createTrackbar('G', 'Settings', 255, 255, nothing)
cv2.createTrackbar('B', 'Settings', 255, 255, nothing)

# To change size # Slider
cv2.createTrackbar('Size', 'Settings', 75, 150, nothing)

# Switch
cv2.createTrackbar('Type', 'Settings', 0, 1, nothing)

while True:
    cv2.imshow('Settings', settings)
    cv2.imshow('Paint', img)

    RGB[0] = cv2.getTrackbarPos('R', 'Settings')
    RGB[1] = cv2.getTrackbarPos('G', 'Settings')
    RGB[2] = cv2.getTrackbarPos('B', 'Settings')

    size = cv2.getTrackbarPos('Size', 'Settings')
    typeCircle = cv2.getTrackbarPos('Type', 'Settings') - 1

    pressedKey = cv2.waitKey(1) & 0xFF
    if pressedKey == 27:
        break
cv2.destroyAllWindows()
