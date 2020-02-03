import cv2
import numpy as np

cap = cv2.VideoCapture(0)

points = list()
pts = np.zeros(0)


def select_area(event, x, y, flags, param):
    global pts

    if event == cv2.EVENT_LBUTTONDOWN:
        points.append([x, y])
        pts = np.array(points, np.int32)
    elif event == cv2.EVENT_RBUTTONDOWN:
        points.append([x, y])
        pts = np.array(points, np.int32)
        points.clear()
    elif event == cv2.EVENT_MBUTTONDOWN:
        points.clear()
        pts = np.array(points, np.int32)


while cap.isOpened():
    _, frame = cap.read()

    cv2.setMouseCallback('Color Tracker', select_area)

    polygon = cv2.polylines(frame, [pts], True, (0, 255, 255), 0)
    if pts.size > 0:
        print(cv2.sumElems(pts))
    cv2.imshow('Color Tracker', polygon)
    cv2.imshow('Color Tracker', frame)

    k = cv2.waitKey(2) & 0xFF
    if k == 27:
        break

cv2.destroyAllWindows()
