import cv2
import numpy as np

isPaint = False
size = 50
typeCircle = -1


# mouse callback function
def draw_circle(event, x, y, flags, param):
    global isPaint
    if isPaint:
        cv2.circle(img, (x, y), size, (255, (x + 100) % 255, (y + 100) % 255), typeCircle)

    if event == cv2.EVENT_LBUTTONDOWN:
        isPaint = True
    elif event == cv2.EVENT_LBUTTONUP:
        isPaint = False


# Create a black image, a window and bind the function to window
windowName = 'To increase radius : - | +, To change type of circle : 1 : Filled | 2 : Circle'
img = np.zeros((1080, 1920, 3), np.uint8)
cv2.namedWindow(windowName)
cv2.setMouseCallback(windowName, draw_circle)

while True:
    cv2.imshow(windowName, img)
    pressedKey = cv2.waitKey(1) & 0xFF
    if pressedKey == ord('-') and size > 0:
        size -= 5
    elif pressedKey == ord('+') and size < 150:
        size += 5
    elif pressedKey == ord('1'):
        typeCircle = -1
    elif pressedKey == ord('2'):
        typeCircle = 0
    elif pressedKey == 27:
        break
cv2.destroyAllWindows()
