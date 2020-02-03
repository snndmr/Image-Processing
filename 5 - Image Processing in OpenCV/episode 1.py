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
    # 178   34.5 104

    lower_blue = np.array([168, 14, 80])
    upper_blue = np.array([200, 55, 125])

    # Threshold the HSV image
    mask = cv2.inRange(hsv, lower_blue, upper_blue)

    # Bitwise-AND mask and original image
    res = cv2.bitwise_and(frame, frame, mask=mask)

    try:
        x, y = np.where(mask > 0)
        circle = cv2.circle(frame, (int(np.nanmean(y)), int(np.nanmean(x))), 40, (0, 255, 255), 5)
        cv2.imshow('frame', circle)
    except ValueError:
        print("Out of range!")

    cv2.imshow('frame', frame)
    cv2.imshow('mask', mask)
    cv2.imshow('res', res)

    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break

cv2.destroyAllWindows()
