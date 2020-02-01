import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while cap.isOpened():
    _, frame = cap.read()

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # H_OpenCV = H_normal / 2
    # S_OpenCV = S_normal * 2.55
    # V_OpenCV = V_normal * 2.55
    # (H – 10, S – 20, V – 20) to(H + 10, S + 20, V + 20)

    # 100, 255, 202
    # 99, 218, 239
    lower_blue = np.array([90, 180, 180])
    upper_blue = np.array([110, 255, 255])

    # Threshold the HSV image
    mask = cv2.inRange(hsv, lower_blue, upper_blue)

    # Bitwise-AND mask and original image
    res = cv2.bitwise_and(frame, frame, mask=mask)

    try:
        x, y = np.where(mask == 255)
        circle = cv2.circle(res, (int(np.nanmean(y)), int(np.nanmean(x))), 100, (0, 255, 255), 5)
        cv2.imshow('res', circle)
    except ValueError:
        print("Out of range!")

    cv2.imshow('frame', frame)
    cv2.imshow('mask', mask)
    cv2.imshow('res', res)

    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break

cv2.destroyAllWindows()
